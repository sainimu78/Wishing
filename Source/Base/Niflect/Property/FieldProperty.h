#pragma once
#include "Niflect/Property/NiflectProperty.h"
#include "Niflect/Field/NiflectField.h"

namespace Niflect
{
	class IPropertyPathSerializer
	{
	public:
		virtual bool SaveRecurs(const TArrayNif<const CProperty*>& vecProp, uint32& frontIndex, const AddrType& base, CRwNode& rw) const = 0;
	};

	using CSharedPropertyPathSerializer = TSharedPtr<IPropertyPathSerializer>;

	class CFieldProperty : public CProperty
	{
	public:
		CFieldProperty(const CField* field, const CSharedPropertyPathSerializer& serPathBased)
			: m_field(field)
			, m_serPathBased(serPathBased)
		{
		}
	public:
		virtual bool SaveToRwNode(const AddrType& base, CRwNode& rw) const override
		{
			return m_field->FieldSaveToRwNode(base, rw);
		}
		virtual bool LoadFromRwNode(AddrType& base, const CRwNode& rw) const override
		{
			return m_field->FieldLoadFromRwNode(base, rw);
		}
		virtual bool SaveByPropertyPathRecurs(const TArrayNif<const CProperty*>& vecProp, uint32& frontIndex, const AddrType& base, CRwNode& rw) const override
		{
			return m_serPathBased->SaveRecurs(vecProp, frontIndex, base, rw);
		}

	private:
		const CField* m_field;
		CSharedPropertyPathSerializer m_serPathBased;
	};
	
	class CPropertyPathSerializerAddr : public IPropertyPathSerializer
	{
	public:
		CPropertyPathSerializerAddr(const CAddrOffset& addrOffset)
			: m_addrOffset(addrOffset)
		{
		}
		
	public:
		virtual bool SaveRecurs(const TArrayNif<const CProperty*>& vecProp, uint32& frontIndex, const AddrType& base, CRwNode& rw) const override
		{
			auto& prop = vecProp[frontIndex];
			auto obj = m_addrOffset.GetAddr(base);
			frontIndex++;
			if (vecProp.size() <= frontIndex)
			{
				//m_field->FieldSaveToRwNode(obj, rw);
				return prop->SaveToRwNode(obj, rw);
			}
			return vecProp[frontIndex]->SaveByPropertyPathRecurs(vecProp, frontIndex, obj, rw);
		}

	private:
		const CAddrOffset& m_addrOffset;
	};
	
	inline CAccessorAddrCreatePropertyTree::CAccessorAddrCreatePropertyTree(const CAddrOffset& addrOffset)
		: m_addrOffset(addrOffset)
	{
	}
	inline CSharedProperty CAccessorAddrCreatePropertyTree::Do(CField* field, const AddrType& base, const CCreatingPropertyTreeContext& context) const
	{
		auto prop = MakeShared<CFieldProperty>(field, MakeShared<CPropertyPathSerializerAddr>(m_addrOffset));
		auto obj = m_addrOffset.GetAddr(base);
		field->FieldInitProperty(obj, prop.Get(), context);
		return prop;
	}
	
	template <typename TCB>
	class TPropertyPathSerializerMemberFunction : public IPropertyPathSerializer
	{
	public:
		TPropertyPathSerializerMemberFunction(const TCB& Func)
			: m_Func(Func)
		{
		}
		
	public:
		virtual bool SaveRecurs(const TArrayNif<const CProperty*>& vecProp, uint32& frontIndex, const AddrType& base, CRwNode& rw) const override
		{
			auto& prop = vecProp[frontIndex];
			const auto& instance = m_Func.Invoke(base);
			AddrType addr = const_cast<AddrType>(static_cast<const void*>(&instance));
			frontIndex++;
			if (vecProp.size() <= frontIndex)
			{
				//m_field->FieldSaveToRwNode(addr, rw);
				return prop->SaveToRwNode(addr, rw);
			}
			return vecProp[frontIndex]->SaveByPropertyPathRecurs(vecProp, frontIndex, addr, rw);
		}

	private:
		TCB m_Func;
	};

	template <typename TCB>
	class TAccessorMemberFunctionCreatePropertyTree : public IAccessorCreatePropertyTree
	{
	public:
		TAccessorMemberFunctionCreatePropertyTree(const TCB& Func)
			: m_Func(Func)
		{
		}
		
	public:
		virtual CSharedProperty Do(CField* field, const AddrType& base, const CCreatingPropertyTreeContext& context) const override
		{
			auto prop = MakeShared<CFieldProperty>(field, MakeShared<TPropertyPathSerializerMemberFunction<TCB> >(m_Func));
			CCreatingPropertyTreeContext branchContext(context);
			branchContext.SetRequiredPathBasedSerializer(true);
			const auto& instance = m_Func.Invoke(base);
			AddrType addr = const_cast<AddrType>(static_cast<const void*>(&instance));
			field->FieldInitProperty(addr, prop.Get(), branchContext);
			return prop;
		}

	private:
		TCB m_Func;
	};
	
	inline CAccessorAddrGetter::CAccessorAddrGetter(const CAddrOffset& addrOffset)
		: m_addrOffset(addrOffset)
	{
	}

	inline bool CAccessorAddrGetter::SaveToRwNode(const CField* field, const AddrType& base, CRwNode& rw) const
	{
		auto obj = m_addrOffset.GetAddr(base);
		return field->FieldSaveToRwNode(obj, rw);
	}
	inline CSharedProperty CAccessorAddrGetter::CreatePropertyTree(const CField* field, const AddrType& base, const CCreatingPropertyTreeContext& context) const
	{
		auto prop = MakeShared<CFieldProperty>(field, MakeShared<CPropertyPathSerializerAddr>(m_addrOffset));
		auto obj = m_addrOffset.GetAddr(base);
		field->FieldInitProperty(obj, prop.Get(), context);
		return prop;
	}
	
	inline CAccessorAddrSetter::CAccessorAddrSetter(const CAddrOffset& addrOffset)
		: m_addrOffset(addrOffset)
	{
	}
	inline bool CAccessorAddrSetter::LoadFromRwNode(const CField* field, AddrType& base, const CRwNode& rw) const
	{
		auto obj = m_addrOffset.GetAddr(base);
		return field->FieldLoadFromRwNode(obj, rw);
	}
	
	template <typename TCB>
	class TAccessorMethodGetter : public IAccessorGetter
	{
	public:
		TAccessorMethodGetter(const TCB& Func)
			: m_Func(Func)
		{
		}
		
	public:
		virtual bool SaveToRwNode(const CField* field, const AddrType& base, CRwNode& rw) const override
		{
			const auto& instance = m_Func.Invoke(base);
			AddrType addr = const_cast<AddrType>(static_cast<const void*>(&instance));
			return field->FieldSaveToRwNode(addr, rw);
		}
		virtual CSharedProperty CreatePropertyTree(const CField* field, const AddrType& base, const CCreatingPropertyTreeContext& context) const override
		{
			auto prop = MakeShared<CFieldProperty>(field, MakeShared<TPropertyPathSerializerMemberFunction<TCB> >(m_Func));
			CCreatingPropertyTreeContext branchContext(context);
			branchContext.SetRequiredPathBasedSerializer(true);
			const auto& instance = m_Func.Invoke(base);
			AddrType addr = const_cast<AddrType>(static_cast<const void*>(&instance));
			field->FieldInitProperty(addr, prop.Get(), branchContext);
			return prop;
		}

	private:
		TCB m_Func;
	};

	template <typename TCB, typename TValue>
	class TAccessorMethodSetter : public IAccessorSetter
	{
	public:
		TAccessorMethodSetter(const TCB& Func)
			: m_Func(Func)
		{
		}
		
	public:
		virtual bool LoadFromRwNode(const CField* field, AddrType& base, const CRwNode& rw) const override
		{
			TValue instance;
			AddrType addr = static_cast<AddrType>(&instance);
			auto ret = field->FieldLoadFromRwNode(addr, rw);
			m_Func.Invoke(base, instance);
			return ret;
		}

	private:
		TCB m_Func;
	};
}