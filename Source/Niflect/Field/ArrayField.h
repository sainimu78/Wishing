#pragma once
#include "Niflect/Field/TemplateField.h"
#include "Niflect/Property/FieldProperty.h"
#include "Niflect/Util/TypeUtil.h"

namespace Niflect
{
	class IArrayDelegate
	{
	public:
		virtual AddrType GetElementBaseAddr(const AddrType& base, const ArrayIndex& idx) const = 0;
		virtual ArrayIndex GetElementsCount(const AddrType& base) const = 0;
		virtual void SetElementsCount(const AddrType& base, const ArrayIndex& count) const = 0;
	};
	using CSharedArrayDelegate = TSharedPtr<IArrayDelegate>;

	class CArrayField : public CContainerField
	{
	public:
		void InitDelegate(const CSharedArrayDelegate& delegate)
		{
			m_delegate = delegate;
		}

	public:
		virtual bool FieldSaveToRwNode(const AddrType& base, CRwNode& rw) const override
		{
			auto count = m_delegate->GetElementsCount(base);
			if (count > 0)
			{
				auto& rwArray = rw->ToArray();
				for (ArrayIndex idx1 = 0; idx1 < count; ++idx1)
				{
					auto& rwItem = rwArray->AddItemNode();
					auto elemBase = m_delegate->GetElementBaseAddr(base, idx1);
					this->GetElementField()->SaveToRwNode(elemBase, rwItem);
				}
			}
			return true;
		}
		virtual bool FieldLoadFromRwNode(AddrType& base, const CRwNode& rw) const override
		{
			auto& rwArray = rw->ToArray();
			auto count = GetRwItemsCount(rwArray);
			m_delegate->SetElementsCount(base, count);
			for (ArrayIndex idx1 = 0; idx1 < count; ++idx1)
			{
				auto& rwItem = rwArray->GetItemNode(idx1);
				auto elemBase = m_delegate->GetElementBaseAddr(base, idx1);
				this->GetElementField()->LoadFromRwNode(elemBase, rwItem);
			}
			return true;
		}

	public:
		virtual bool FieldInitProperty(const AddrType& base, CProperty* prop, const CCreatingPropertyTreeContext& context) const override
		{
			prop->InitMeta(this->GetName(), base, context.m_requiredPathBasedSerializer, false);
			
			auto count = m_delegate->GetElementsCount(base);
			for (uint32 idx = 0; idx < count; ++idx)
			{
				auto elemBase = m_delegate->GetElementBaseAddr(base, idx);
				auto elemProp = this->GetElementField()->CreatePropertyTree(elemBase);
				elemProp->InitParent(prop);
				prop->AddChild(elemProp);
			}
			return true;
		}

	private:
		CField* GetElementField() const
		{
			return this->GetArgumentField(0);
		}

	public:
		static CArrayField* Cast(CField* base)
		{
			ASSERT(dynamic_cast<CArrayField*>(base) != NULL);
			return static_cast<CArrayField*>(base);
		}

	private:
		CSharedArrayDelegate m_delegate;
	};
	
	template <typename TArrayType>
	class TArrayDelegateStlCompliant : public IArrayDelegate
	{
	public:
		virtual AddrType GetElementBaseAddr(const AddrType& base, const ArrayIndex& idx) const override
		{
			auto& array = *static_cast<TArrayType*>(base);
			return &array[idx];
		}
		virtual ArrayIndex GetElementsCount(const AddrType& base) const override
		{
			auto& array = *static_cast<TArrayType*>(base);
			return static_cast<ArrayIndex>(array.size());
		}
		virtual void SetElementsCount(const AddrType& base, const ArrayIndex& count) const override
		{
			auto& array = *static_cast<TArrayType*>(base);
			array.resize(count);
		}
	};
	
	template <typename TType>
	struct SFieldCreator<CArrayField, TType>
	{
		static TSharedPtr<CArrayField> Create()
		{
			auto shared1 = Niflect::MakeShared<CArrayField>();
			auto field1 = shared1.Get();
			field1->InitDelegate(MakeShared<TArrayDelegateStlCompliant<TType> >());
			return shared1;
		}
	};


	//下为备份, 现放弃支持Array Element专用的accessor, 现对于Array型, 仅支持Addr based accessor
	//原因见InitMemberMeta_ReservedForMethodBasedAccessor注释

	class IArrayAccessorGetElementsCount
	{
	public:
		virtual uint32 Do(const AddrType& base) const = 0;
	};
	using CSharedArrayAccessorGetElementsCount = TSharedPtr<IArrayAccessorGetElementsCount>;

	class IArrayAccessorSetElementsCount
	{
	public:
		virtual void Do(const AddrType& base, uint32 count) const = 0;
	};
	using CSharedArrayAccessorSetElementsCount = TSharedPtr<IArrayAccessorSetElementsCount>;
	
	class IArrayAccessorSaveElementToRwNode
	{
	public:
		virtual bool Do(CField* elemField, const AddrType& base, uint32 idx, CRwNode& rw) const = 0;
	};
	using CSharedArrayAccessorSaveElementToRwNode = TSharedPtr<IArrayAccessorSaveElementToRwNode>;

	class IArrayAccessorLoadElementFromRwNode
	{
	public:
		virtual bool Do(CField* elemField, AddrType& base, uint32 idx, const CRwNode& rw) const = 0;
	};
	using CSharedArrayAccessorLoadElementFromRwNode = TSharedPtr<IArrayAccessorLoadElementFromRwNode>;

	class IArrayAccessorCreateElementPropertyTree
	{
	public:
		virtual CSharedProperty Do(CField* elemField, const AddrType& base, uint32 idx, const CCreatingPropertyTreeContext& context) const = 0;
	};
	using CSharedArrayAccessorCreateElementPropertyTree = TSharedPtr<IArrayAccessorCreateElementPropertyTree>;

	class Reserved_AccessorDelegatesBased_CArrayField : public CContainerField
	{
		typedef CContainerField inherited;
	public:
		void SetGetElementsCount(const CSharedArrayAccessorGetElementsCount& accessor)
		{
			m_getElementsCount = accessor;
		}
		void SetSetElementsCount(const CSharedArrayAccessorSetElementsCount& accessor)
		{
			m_setElementsCount = accessor;
		}
		void SetSaveElementToRwNode(const CSharedArrayAccessorSaveElementToRwNode& accessor)
		{
			m_saveElementToRwNode = accessor;
		}
		void SetLoadElementFromRwNode(const CSharedArrayAccessorLoadElementFromRwNode& accessor)
		{
			m_loadElementFromRwNode = accessor;
		}
		void SetCreateElementPropertyTree(const CSharedArrayAccessorCreateElementPropertyTree& accessor)
		{
			m_createElementPropertyTree = accessor;
		}

	protected:
		virtual bool FieldSaveToRwNode(const AddrType& base, CRwNode& rw) const override
		{
			auto count = m_getElementsCount->Do(base);
			if (count > 0)
			{
				auto& rwArray = rw->ToArray();
				for (ArrayIndex idx1 = 0; idx1 < count; ++idx1)
				{
					auto& rwItem = rwArray->AddItemNode();
					m_saveElementToRwNode->Do(this->GetElementField(), base, idx1, rwItem);
				}
			}
			return true;
		}
		virtual bool FieldLoadFromRwNode(AddrType& base, const CRwNode& rw) const override
		{
			auto& rwArray = rw->ToArray();
			auto count = GetRwItemsCount(rwArray);
			m_setElementsCount->Do(base, count);
			for (ArrayIndex idx1 = 0; idx1 < count; ++idx1)
			{
				auto& rwItem = rwArray->GetItemNode(idx1);
				m_loadElementFromRwNode->Do(this->GetElementField(), base, idx1, rwItem);
			}
			return true;
		}
		virtual bool FieldInitProperty(const AddrType& base, CProperty* prop, const CCreatingPropertyTreeContext& context) const override
		{
			prop->InitMeta(this->GetName(), base, context.m_requiredPathBasedSerializer, false);

			auto count = m_getElementsCount->Do(base);
			for (uint32 idx = 0; idx < count; ++idx)
			{
				auto elemProp = m_createElementPropertyTree->Do(this->GetElementField(), base, idx, context);
				elemProp->InitParent(prop);
				prop->AddChild(elemProp);
			}
			return true;
		}

	private:
		CField* GetElementField() const
		{
			return this->GetArgumentField(0);
		}

	private:
		CSharedArrayAccessorGetElementsCount m_getElementsCount;
		CSharedArrayAccessorSetElementsCount m_setElementsCount;
		CSharedArrayAccessorSaveElementToRwNode m_saveElementToRwNode;
		CSharedArrayAccessorLoadElementFromRwNode m_loadElementFromRwNode;
		CSharedArrayAccessorCreateElementPropertyTree m_createElementPropertyTree;
	};
	
	template <typename TArrayType>
	class TArrayAccessorAddrGetElementsCount : public IArrayAccessorGetElementsCount
	{		
	public:
		virtual uint32 Do(const AddrType& base) const override
		{
			auto& array = *static_cast<TArrayType*>(base);
			return static_cast<uint32>(array.size());
		}
	};
	
	template <typename TArrayType>
	class TArrayAccessorAddrSetElementsCount : public IArrayAccessorSetElementsCount
	{		
	public:
		virtual void Do(const AddrType& base, uint32 count) const override
		{
			auto& array = *static_cast<TArrayType*>(base);
			array.resize(count);
		}
	};
	
	template <typename TArrayType>
	class TArrayAccessorAddrSaveElementToRwNode : public IArrayAccessorSaveElementToRwNode
	{		
	public:
		virtual bool Do(CField* elemField, const AddrType& base, uint32 idx, CRwNode& rw) const override
		{
			auto& array = *static_cast<TArrayType*>(base);
			auto& instance = array[idx];
			return elemField->SaveToRwNode(&instance, rw);
		}
	};
	
	template <typename TArrayType>
	class TArrayAccessorAddrLoadElementFromRwNode : public IArrayAccessorLoadElementFromRwNode
	{
	public:
		virtual bool Do(CField* elemField, AddrType& base, uint32 idx, const CRwNode& rw) const override
		{
			auto& array = *static_cast<TArrayType*>(base);
			auto& instance = array[idx];
			AddrType addr = static_cast<AddrType>(&instance);
			return elemField->LoadFromRwNode(addr, rw);
		}
	};
	
	template <typename TArrayType>
	class TArrayPropertyPathSerializerAddr : public IPropertyPathSerializer
	{
	public:
		TArrayPropertyPathSerializerAddr(uint32 idx)
			: m_idx(idx)
		{
		}
		
	public:
		virtual bool SaveRecurs(const TArrayNif<const CProperty*>& vecProp, uint32& frontIndex, const AddrType& base, CRwNode& rw) const override
		{
			auto& prop = vecProp[frontIndex];
			auto& array = *static_cast<TArrayType*>(base);
			auto& instance = array[m_idx];
			AddrType addr = static_cast<AddrType>(&instance);
			frontIndex++;
			if (vecProp.size() <= frontIndex)
			{
				//m_field->FieldSaveToRwNode(addr, rw);
				return prop->SaveToRwNode(addr, rw);
			}
			return vecProp[frontIndex]->SaveByPropertyPathRecurs(vecProp, frontIndex, addr, rw);
		}

	private:
		uint32 m_idx;
	};

	template <typename TArrayType>
	class TArrayAccessorAddrCreateElementPropertyTree : public IArrayAccessorCreateElementPropertyTree
	{
	public:
		virtual CSharedProperty Do(CField* elemField, const AddrType& base, uint32 idx, const CCreatingPropertyTreeContext& context) const override
		{
			auto prop = MakeShared<CFieldProperty>(elemField, MakeShared<TArrayPropertyPathSerializerAddr<TArrayType> >(idx));
			auto& array = *static_cast<TArrayType*>(base);
			auto& instance = array[idx];
			AddrType addr = static_cast<AddrType>(&instance);
			elemField->FieldInitProperty(addr, prop.Get(), context);
			return prop;
		}
	};
	
	template <typename TCB>
	class TArrayAccessorMemberFunctionGetElementsCount : public IArrayAccessorGetElementsCount
	{
	public:
		TArrayAccessorMemberFunctionGetElementsCount(const TCB& Func)
			: m_Func(Func)
		{
		}
		
	public:
		virtual uint32 Do(const AddrType& base) const override
		{
			return m_Func.Invoke(base);
		}

	private:
		TCB m_Func;
	};
	
	template <typename TCB>
	class TArrayAccessorMemberFunctionSetElementsCount : public IArrayAccessorSetElementsCount
	{
	public:
		TArrayAccessorMemberFunctionSetElementsCount(const TCB& Func)
			: m_Func(Func)
		{
		}
		
	public:
		virtual void Do(const AddrType& base, uint32 count) const override
		{
			m_Func.Invoke(base, count);
		}

	private:
		TCB m_Func;
	};
	
	template <typename TCB>
	class TArrayAccessorMemberFunctionSaveElementToRwNode : public IArrayAccessorSaveElementToRwNode
	{
	public:
		TArrayAccessorMemberFunctionSaveElementToRwNode(const TCB& Func)
			: m_Func(Func)
		{
		}
		
	public:
		virtual bool Do(CField* elemField, const AddrType& base, uint32 idx, CRwNode& rw) const override
		{
			const auto& instance = m_Func.Invoke(base, idx);
			AddrType addr = const_cast<AddrType>(static_cast<const void*>(&instance));
			return elemField->SaveToRwNode(addr, rw);
		}

	private:
		TCB m_Func;
	};
	
	template <typename TValue, typename TCB>
	class TArrayAccessorMemberFunctionLoadElementFromRwNode : public IArrayAccessorLoadElementFromRwNode
	{
	public:
		TArrayAccessorMemberFunctionLoadElementFromRwNode(const TCB& Func)
			: m_Func(Func)
		{
		}
		
	public:
		virtual bool Do(CField* elemField, AddrType& base, uint32 idx, const CRwNode& rw) const override
		{
			TValue instance;
			AddrType addr = &instance;
			auto ret = elemField->LoadFromRwNode(addr, rw);
			m_Func.Invoke(base, instance, idx);
			return ret;
		}

	private:
		TCB m_Func;
	};
	
	template <typename TCB>
	class TArrayPropertyPathSerializerMemberFunction : public IPropertyPathSerializer
	{
	public:
		TArrayPropertyPathSerializerMemberFunction(const TCB& Func, uint32 idx)
			: m_Func(Func)
			, m_idx(idx)
		{
		}
		
	public:
		virtual bool SaveRecurs(const TArrayNif<const CProperty*>& vecProp, uint32& frontIndex, const AddrType& base, CRwNode& rw) const override
		{
			auto& prop = vecProp[frontIndex];
			const auto& instance = m_Func.Invoke(base, m_idx);
			AddrType addr = const_cast<AddrType>(static_cast<const void*>(&instance));
			frontIndex++;
			if (vecProp.size() <= frontIndex)
			{
				return prop->SaveToRwNode(addr, rw);
			}
			return vecProp[frontIndex]->SaveByPropertyPathRecurs(vecProp, frontIndex, addr, rw);
		}

	private:
		TCB m_Func;
		uint32 m_idx;
	};
	
	template <typename TCB>
	class TArrayAccessorMemberFunctionCreateElementPropertyTree : public IArrayAccessorCreateElementPropertyTree
	{
	public:
		TArrayAccessorMemberFunctionCreateElementPropertyTree(const TCB& Func)
			: m_Func(Func)
		{
		}
		
	public:
		virtual CSharedProperty Do(CField* elemField, const AddrType& base, uint32 idx, const CCreatingPropertyTreeContext& context) const override
		{
			auto prop = MakeShared<CFieldProperty>(elemField, MakeShared<TArrayPropertyPathSerializerMemberFunction<TCB> >(m_Func, idx));
			CCreatingPropertyTreeContext branchContext(context);
			branchContext.SetRequiredPathBasedSerializer(true);
			const auto& instance = m_Func.Invoke(base, idx);
			AddrType addr = const_cast<AddrType>(static_cast<const void*>(&instance));
			elemField->FieldInitProperty(addr, prop.Get(), branchContext);
			return prop;
		}

	private:
		TCB m_Func;
	};

	template <typename TType>
	struct SFieldCreator<Reserved_AccessorDelegatesBased_CArrayField, TType>
	{
		static TSharedPtr<Reserved_AccessorDelegatesBased_CArrayField> Create()
		{
			auto shared1 = Niflect::MakeShared<Reserved_AccessorDelegatesBased_CArrayField>();
			auto field1 = shared1.Get();
			field1->SetGetElementsCount(MakeShared<TArrayAccessorAddrGetElementsCount<TType> >());
			field1->SetSetElementsCount(MakeShared<TArrayAccessorAddrSetElementsCount<TType> >());
			field1->SetSaveElementToRwNode(MakeShared<TArrayAccessorAddrSaveElementToRwNode<TType> >());
			field1->SetLoadElementFromRwNode(MakeShared<TArrayAccessorAddrLoadElementFromRwNode<TType> >());
			field1->SetCreateElementPropertyTree(MakeShared<TArrayAccessorAddrCreateElementPropertyTree<TType> >());
			return shared1;
		}
	};
}