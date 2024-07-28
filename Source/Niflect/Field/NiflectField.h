#pragma once
#include "Niflect/Property/NiflectProperty.h"
#include "Niflect/Base/NiflectAddr.h"
#include "Niflect/Util/TypeUtil.h"

namespace Niflect
{
	using namespace TreeReadWrite2;
	
	template <typename T>
	static CNiflectType* StaticGetType();

	class CNiflectType;
	
	class CField;

	using CSharedField = TSharedPtr<CField>;
	
	class IAccessorSaveToRwNode
	{
	public:
		virtual bool Do(const CField* field, const AddrType& base, CRwNode& rw) const = 0;
	};
	using CSharedAccessorSaveToRwNode = TSharedPtr<IAccessorSaveToRwNode>;

	class IAccessorLoadFromRwNode
	{
	public:
		virtual bool Do(const CField* field, AddrType& base, const CRwNode& rw) const = 0;
	};
	using CSharedAccessorLoadFromRwNode = TSharedPtr<IAccessorLoadFromRwNode>;
	
	class CCreatingPropertyTreeContext
	{
	public:
		CCreatingPropertyTreeContext()
			: m_requiredPathBasedSerializer(false)
		{
		}
		void SetRequiredPathBasedSerializer(bool requiredPathBasedSerializer)
		{
			m_requiredPathBasedSerializer = requiredPathBasedSerializer;
		}
		bool m_requiredPathBasedSerializer;
	};

	class IAccessorCreatePropertyTree
	{
	public:
		virtual CSharedProperty Do(CField* field, const AddrType& base, const CCreatingPropertyTreeContext& context) const = 0;
	};
	using CSharedAccessorCreatePropertyTree = TSharedPtr<IAccessorCreatePropertyTree>;
	
	class IAccessorGetter
	{
	public:
		virtual bool SaveToRwNode(const CField* field, const AddrType& base, CRwNode& rw) const = 0;
		virtual CSharedProperty CreatePropertyTree(const CField* field, const AddrType& base, const CCreatingPropertyTreeContext& context) const = 0;
	};
	using CSharedAccessorGetter = TSharedPtr<IAccessorGetter>;
	
	class IAccessorSetter
	{
	public:
		virtual bool LoadFromRwNode(const CField* field, AddrType& base, const CRwNode& rw) const = 0;
	};
	using CSharedAccessorSetter = TSharedPtr<IAccessorSetter>;

	template<typename TOwner, typename Ret, typename ...Args>
	class TAccessorMethodHasConst
	{
		using function_type = Ret (TOwner::*)(Args...) const;

	public:
		TAccessorMethodHasConst(const function_type &f) : m_func(f) {}

		Ret Invoke(void* owner, Args... args) const
		{
			return (static_cast<TOwner*>(owner)->*m_func)(std::forward<Args>(args)...);
		}

	private:
		function_type m_func;
	};
	template<typename TOwner, typename Ret, typename ...Args>
	class TAccessorMethodNonConst
	{
		using function_type = Ret (TOwner::*)(Args...);

	public:
		TAccessorMethodNonConst(const function_type &f) : m_func(f) {}

		Ret Invoke(void* owner, Args... args) const
		{
			return (static_cast<TOwner*>(owner)->*m_func)(std::forward<Args>(args)...);
		}

	private:
		function_type m_func;
	};
	
	class CAccessorAddrSaveToRwNode : public IAccessorSaveToRwNode
	{
	public:
		CAccessorAddrSaveToRwNode(const CAddrOffset& addrOffset);
		
	public:
		virtual bool Do(const CField* field, const AddrType& base, CRwNode& rw) const override;

	private:
		const CAddrOffset& m_addrOffset;
	};
	
	class CAccessorAddrLoadFromRwNode : public IAccessorLoadFromRwNode
	{
	public:
		CAccessorAddrLoadFromRwNode(const CAddrOffset& addrOffset);
		
	public:
		virtual bool Do(const CField* field, AddrType& base, const CRwNode& rw) const override;

	private:
		const CAddrOffset& m_addrOffset;
	};
	
	class CAccessorAddrCreatePropertyTree : public IAccessorCreatePropertyTree
	{
	public:
		CAccessorAddrCreatePropertyTree(const CAddrOffset& addrOffset);
		
	public:
		virtual CSharedProperty Do(CField* field, const AddrType& base, const CCreatingPropertyTreeContext& context) const override;

	private:
		const CAddrOffset& m_addrOffset;
	};
	
	class CAccessorAddrGetter : public IAccessorGetter
	{
	public:
		CAccessorAddrGetter(const CAddrOffset& addrOffset);
		
	public:
		virtual bool SaveToRwNode(const CField* field, const AddrType& base, CRwNode& rw) const override;
		virtual CSharedProperty CreatePropertyTree(const CField* field, const AddrType& base, const CCreatingPropertyTreeContext& context) const override;

	private:
		const CAddrOffset& m_addrOffset;
	};
	
	class CAccessorAddrSetter : public IAccessorSetter
	{
	public:
		CAccessorAddrSetter(const CAddrOffset& addrOffset);
		
	public:
		virtual bool LoadFromRwNode(const CField* field, AddrType& base, const CRwNode& rw) const override;

	private:
		const CAddrOffset& m_addrOffset;
	};

	class CField
	{
	public:
		CField()
			: m_type(NULL)
			, m_owner(NULL)
			//, m_saveToRwNode(MakeShared<CAccessorAddrSaveToRwNode>(m_addrOffset))//为保留未使用的Method based accessor, 在构造时创建addr based accessor
			//, m_loadFromRwNode(MakeShared<CAccessorAddrLoadFromRwNode>(m_addrOffset))
			//, m_createPropertyTree(MakeShared<CAccessorAddrCreatePropertyTree>(m_addrOffset))
		{
		}

	public:
		void InitType(CNiflectType* type)
		{
			m_type = type;
		}
		void InitMemberMeta(const CString& name, const AddrOffsetType& offset, CField* owner/*备用*/)
		{
			m_name = name;
			m_addrOffset.SetOffset(offset);
			//m_owner = owner;
		}
		void InitMemberMeta_ReservedForMethodBasedAccessor(const CString& name, CField* owner/*备用*/)
		{
			//该函数及其相关代码为支持Method based accessor备用参考, 所实现的这种accessor支持偏移与成员函数混用的反射方式
			//
			//现不计划支持这种accessor的原因如下
			//实现困难:
			//1. 对于Map, 要求成员函数能够以某种形式提供iterator, 这样才能实现保存map, 但实际编码中, 提供iterator的情况极罕见
			//2. 对于Compound, Array等确实已经实现成员函数与地址偏移兼容的反射方法, 但实现非常繁琐, 存在较多重复逻辑的代码
			//3. 由于无法要求用户不定义返回copy的getter, 大部分流程都需要在递归函数中进行, 这就导致定义较多重复逻辑的代码
			//成员函数accessor缺陷:
			//1. 如Flax的成员函数accessor必须同时定义getter和setter, 否则不生成相关代码; 另外API_FIELD与getter setter的API_PROPERTY同时使用将产生重复的序列化代码
			//	1. 实际编码中, 并不能因为需要序列化就要求用户定义setter或getter
			//2. UE则不支持成员函数accessor
			//3. 实际的反射对象实例化过程不必要用setter的方式修改load后的数据, 应该在实例化流程中修改, 这样的好处在于不容易造成冗余逻辑
			//4. 由于保存时的值只能通过getter获取, 如果getter返回的是copy则意味着其子节点的保存也必须在此copy的基础上进行, 因此为保存一个末端节点就要通过从根节点开始的一条属性路径递归调用其中指定的getter最终获得欲保存的属性数据base

			m_name = name;
			//m_owner = owner;
		}
		CNiflectType* GetType() const
		{
			return m_type;
		}
		const CString& GetName() const
		{
			return m_name;
		}
		//template <typename T>
		//inline T& GetInstanceRef(const AddrType& base) const
		//{
		//	return *static_cast<T*>(this->GetBaseAddr(base));
		//}

	public:
		void AddChild(const CSharedField& field)
		{
			this->InsertChild(field, this->GetChildrenCount());
		}
		void InsertChild(const CSharedField& field, uint32 idx)
		{
			m_vecChild.insert(m_vecChild.begin() + idx, field);
		}
		uint32 GetChildrenCount() const
		{
			return static_cast<uint32>(m_vecChild.size());
		}
		CField* GetChild(uint32 idx) const
		{
			return m_vecChild[idx].Get();
		}

	public:
		//void InitAccessors()
		//{
		//	this->InitAccessorAddrSaveToRwNode();
		//	this->InitAccessorAddrLoadSaveToRwNode();
		//	this->InitAccessorAddrCreatePropertyTree();
		//}
		//void InitAccessorsAddrBased(const AddrOffsetType& offset)
		//{
		//	this->InitOffset(offset);
		//	this->InitAccessors();
		//}
		//void InitAccessorAddrSaveToRwNode()
		//{
		//	this->InitAccessorSaveToRwNode(MakeShared<CAccessorAddrSaveToRwNode>(m_addrOffset));
		//}
		//void InitAccessorAddrLoadSaveToRwNode()
		//{
		//	this->InitAccessorLoadFromRwNode(MakeShared<CAccessorAddrLoadFromRwNode>(m_addrOffset));
		//}
		//void InitAccessorAddrCreatePropertyTree()
		//{
		//	this->InitAccessorCreatePropertyTree(MakeShared<CAccessorAddrCreatePropertyTree>(m_addrOffset));
		//}
		void InitOffset(const AddrOffsetType& offset)
		{
			m_addrOffset.SetOffset(offset);
		}
		//void InitAccessorSaveToRwNode(const CSharedAccessorSaveToRwNode& accessor)
		//{
		//	ASSERT(m_saveToRwNode == NULL);
		//	m_saveToRwNode = accessor;
		//}
		//void InitAccessorLoadFromRwNode(const CSharedAccessorLoadFromRwNode& accessor)
		//{
		//	ASSERT(m_loadFromRwNode == NULL);
		//	m_loadFromRwNode = accessor;
		//}
		//void InitAccessorCreatePropertyTree(const CSharedAccessorCreatePropertyTree& accessor)
		//{
		//	ASSERT(m_createPropertyTree == NULL);
		//	m_createPropertyTree = accessor;
		//}
		
		void InitAccessors()
		{
			this->InitAccessorAddrGetter();
			this->InitAccessorAddrSetter();
		}
		void InitAccessorsAddrBased(const AddrOffsetType& offset)
		{
			this->InitOffset(offset);
			this->InitAccessors();
		}
		void InitAccessorAddrGetter()
		{
			this->InitAccessorGetter(MakeShared<CAccessorAddrGetter>(m_addrOffset));
		}
		void InitAccessorAddrSetter()
		{
			this->InitAccessorSetter(MakeShared<CAccessorAddrSetter>(m_addrOffset));
		}
		void InitAccessorGetter(const CSharedAccessorGetter& getter)
		{
			ASSERT(m_getter == NULL);
			m_getter = getter;
		}
		void InitAccessorSetter(const CSharedAccessorSetter& setter)
		{
			ASSERT(m_setter == NULL);
			m_setter = setter;
		}

	public:
		bool SaveToRwNode(const AddrType& base, CRwNode& rw) const
		{
			return m_getter->SaveToRwNode(this, base, rw);
			//return m_saveToRwNode->Do(this, base, rw);
		}
		bool LoadFromRwNode(AddrType& base, const CRwNode& rw) const
		{
			return m_setter->LoadFromRwNode(this, base, rw);
			//return m_loadFromRwNode->Do(this, base, rw);
		}
		CSharedProperty CreatePropertyTree(const AddrType& base, const CCreatingPropertyTreeContext& context = CCreatingPropertyTreeContext())
		{
			return m_getter->CreatePropertyTree(this, base, context);
			//return m_createPropertyTree->Do(this, base, context);
		}

	public:
		virtual bool FieldSaveToRwNode(const AddrType& base, CRwNode& rw) const = 0;
		virtual bool FieldLoadFromRwNode(AddrType& base, const CRwNode& rw) const = 0;
		virtual bool FieldInitProperty(const AddrType& base, CProperty* prop, const CCreatingPropertyTreeContext& context) const = 0;

	private:
		CString m_name;
		CNiflectType* m_type;
		TArrayNif<CSharedField> m_vecChild;
		CField* m_owner;
		CAddrOffset m_addrOffset;
		CSharedAccessorSaveToRwNode m_saveToRwNode;
		CSharedAccessorLoadFromRwNode m_loadFromRwNode;
		CSharedAccessorCreatePropertyTree m_createPropertyTree;
		CSharedAccessorGetter m_getter;
		CSharedAccessorSetter m_setter;
	};
	
	inline CAccessorAddrSaveToRwNode::CAccessorAddrSaveToRwNode(const CAddrOffset& addrOffset)
		: m_addrOffset(addrOffset)
	{
	}

	inline bool CAccessorAddrSaveToRwNode::Do(const CField* field, const AddrType& base, CRwNode& rw) const
	{
		auto obj = m_addrOffset.GetAddr(base);
		return field->FieldSaveToRwNode(obj, rw);
	}
	
	inline CAccessorAddrLoadFromRwNode::CAccessorAddrLoadFromRwNode(const CAddrOffset& addrOffset)
		: m_addrOffset(addrOffset)
	{
	}
	inline bool CAccessorAddrLoadFromRwNode::Do(const CField* field, AddrType& base, const CRwNode& rw) const
	{
		auto obj = m_addrOffset.GetAddr(base);
		return field->FieldLoadFromRwNode(obj, rw);
	}
	
	template <typename TCB>
	class TAccessorMemberFunctionSaveToRwNode : public IAccessorSaveToRwNode
	{
	public:
		TAccessorMemberFunctionSaveToRwNode(const TCB& Func)
			: m_Func(Func)
		{
		}
		
	public:
		virtual bool Do(const CField* field, const AddrType& base, CRwNode& rw) const override
		{
			const auto& instance = m_Func.Invoke(base);
			AddrType addr = const_cast<AddrType>(static_cast<const void*>(&instance));
			return field->FieldSaveToRwNode(addr, rw);
		}

	private:
		TCB m_Func;
	};

	template <typename TValue, typename TCB>
	class TAccessorMemberFunctionLoadFromRwNode : public IAccessorLoadFromRwNode
	{
	public:
		TAccessorMemberFunctionLoadFromRwNode(const TCB& Func)
			: m_Func(Func)
		{
		}
		
	public:
		virtual bool Do(const CField* field, AddrType& base, const CRwNode& rw) const override
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
	
	template <typename TField, typename TType>
	struct SFieldCreator
	{
		static TSharedPtr<TField> Create()
		{
			return MakeShared<TField>();
		}
	};

	template <typename TField, typename TType>
	static TSharedPtr<TField> CreateField()
	{
		auto shared = SFieldCreator<TField, TType>::Create();
		auto field = shared.Get();
		field->InitType(StaticGetType<TType>());
		return shared;
	}
}