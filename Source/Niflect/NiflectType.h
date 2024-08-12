#pragma once
#include "Niflect/NiflectCommon.h"
#include "Niflect/NiflectRegisteredType.h"
#include "Niflect/NiflectMethod.h"
#include "Niflect/NiflectAccessor.h"
#include "Niflect/Util/TypeUtil.h"

namespace Niflect
{	
	typedef uint32 CTypeIndex;

	typedef CSharedAccessor (*InvokeCreateFieldLayoutFunc)();

	class CTypeInvokations
	{
	public:
		CTypeInvokations()
			: m_InvokeConstructorFunc(NULL)
			, m_InvokeDestructorFunc(NULL)
			, m_InvokeCreateFieldLayoutFunc(NULL)
		{
		}
		InvokeConstructorFunc m_InvokeConstructorFunc;//一些其它框架中称作 Ctor 与 Dtor
		InvokeDestructorFunc m_InvokeDestructorFunc;
		InvokeCreateFieldLayoutFunc m_InvokeCreateFieldLayoutFunc;
	};

	class CTypeCustomData
	{
	};
	using CSharedTypeCustomData = TSharedPtr<CTypeCustomData>;

	//todo: 可能需要绑factory或由factory创建, 而factory中绑module, 如此即可以树型组织, 以便获取各种信息
	//todo: 考虑是否需要定义带const的CNiflectType, 方便外部使用
	class CNiflectType
	{
	public:
		CNiflectType()
			: m_index(INDEX_NONE)
			, m_niflectTypeSize(0)
			, m_typeHash(0)
		{
		}

	public:
		//template <typename T>
		//void InitStaticType()
		//{
		//	TInternalRegisteredType<T>::s_type = this;
		//}
		void InitTypeMeta(uint32 niflectTypeSize, size_t typeHash, const CString& name, CTypeIndex index, const CTypeInvokations& cb)
		{
			m_name = name;
			m_index = index;
			m_niflectTypeSize = niflectTypeSize;
			m_cb = cb;
			m_typeHash = typeHash;
		}
		
	public:
		//CField* GetRootField() const
		//{
		//	return m_fieldRoot.Get();
		//}
		//const CSharedAccessor& GetSharedAccessorRoot() const
		//{
		//	return m_accessorRoot;
		//}
		const CTypeIndex& GetTypeIndex() const
		{
			return m_index;
		}
		const CString& GetTypeName() const
		{
			return m_name;
		}
		const uint32& GetTypeSize() const
		{
			return m_niflectTypeSize;//对于C++ Built in类型, 返回类型为const ref是为了方便赋值类型用auto
		}

	public:
		//void Construct(void* instanceBase) const
		//{
		//	if (m_cb.m_InvokeConstructorFunc != NULL)
		//		m_cb.m_InvokeConstructorFunc(instanceBase);
		//}
		//void Destruct(void* instanceBase) const
		//{
		//	if (m_cb.m_InvokeDestructorFunc != NULL)
		//		m_cb.m_InvokeDestructorFunc(instanceBase);
		//}
		CSharedAccessor CreateFieldLayout() const
		{
			if (m_cb.m_InvokeCreateFieldLayoutFunc != NULL)
				return m_cb.m_InvokeCreateFieldLayoutFunc();
			return NULL;
		}
		void InitFieldLayout()
		{
			//todo: 未确定方案, 用到再创建还是在Module初始化时统一遍历创建, 现用后者实验
			ASSERT(m_fieldRoot == NULL);
			m_fieldRoot = this->CreateFieldLayout();
		}
		template <typename TBase>
		TSharedPtr<TBase> MakeSharedInstance() const
		{
			//return GenericMakeShared<TBase, CMemory>(m_niflectTypeSize, m_cb.m_InvokeDestructorFunc, m_cb.m_InvokeConstructorFunc);
			return GenericPlacementMakeShared<TBase, CMemory>(m_niflectTypeSize, m_cb.m_InvokeDestructorFunc, m_cb.m_InvokeConstructorFunc);
		}
		//template <typename TBase>
		//inline TSharedPtr<TBase> MakeSharableInstance(TBase* obj) const
		//{
		//	return GenericMakeSharable<TBase, CMemory>(obj, m_cb.m_InvokeDestructorFunc);
		//}

	//public:
	//	template <typename T>
	//	inline T& GetInstanceRef(void* parentBase) const
	//	{
	//		return this->GetAccessorRoot()->GetInstanceRef<T>(parentBase);
	//	}
	public:
		//todo: 此函数可废弃, 改为静态函数获取m_typeHash
		template <typename T>
		inline T& GetInstanceRef(AddrType base) const
		{
			auto Check = [this]()
			{
				ASSERT(GetTypeHash<T>() == m_typeHash);
				return true;
			};
			ASSERT(Check());
			return *static_cast<T*>(base);
		}

	public:
		void SetCustomData(const CSharedTypeCustomData& data)
		{
			m_customData = data;
		}
		CTypeCustomData* GetCustomData() const
		{
			return m_customData.Get();
		}
		template <typename TCustomData>
		TCustomData* GetDerivedCustomData() const
		{
			return static_cast<TCustomData*>(m_customData.Get());
		}

	public:
		template <typename T>
		static size_t GetTypeHash()
		{
			return typeid(T).hash_code();
		}

	private:
		virtual void DebugFuncForDynamicCast() {}//仅为动态检查类型避免错误, 如已定义非调试用的virtual函数则可移除, 备注: error C2683: 'dynamic_cast': 'XXX' is not a polymorphic type 

	private:
		CString m_name;
		CTypeIndex m_index;
		uint32 m_niflectTypeSize;
		CSharedAccessor m_fieldRoot;
		//todo: 实现成员函数反射(CFunction), 考虑是否有可能与有必要实现支持任意构造函数
		CTypeInvokations m_cb;
		size_t m_typeHash;
		CSharedTypeCustomData m_customData;
	};

	using CSharedType = TSharedPtr<CNiflectType>;
	
	class CEnumMeta
	{
	public:
		TArrayNif<CString> m_vecEnumConstant;
	};

	class CEnum : public CNiflectType
	{
	public:
		void InitEnumMeta(const CEnumMeta& data)
		{
			ASSERT(m_meta.m_vecEnumConstant.size() == 0);
			m_meta = data;
		}
		const CEnumMeta& GetMeta() const
		{
			return m_meta;
		}
		const CString& GetName(uint32 idx) const
		{
			return m_meta.m_vecEnumConstant[idx];
		}
		uint32 FindIndex(const CString& name) const
		{
			for (uint32 idx = 0; idx < m_meta.m_vecEnumConstant.size(); ++idx)
			{
				if (m_meta.m_vecEnumConstant[idx] == name)
					return idx;
			}
			return INDEX_NONE;
		}

	private:
		CEnumMeta m_meta;
	};

	class CFunction : public CNiflectType
	{
	};

	class CInheritableType : public CNiflectType
	{
		typedef CNiflectType inherited;
	public:
		CInheritableType()
			: m_parent(NULL)
		{
		}
		void InitInheritableTypeMeta(CInheritableType* parent)
		{
			m_parent = parent;
		}
		CInheritableType* GetParent() const
		{
			return m_parent;
		}

	//private:
	//	static void GetStackedTypes(CNiflectType* derivedType, bool reversed, TArrayNif<CInheritableType*>& vecStackedType)
	//	{
	//		auto baseType = CInheritableType::CastChecked(derivedType);
	//		while (baseType != NULL)
	//		{
	//			if (!reversed)
	//				vecStackedType.insert(vecStackedType.begin(), baseType);
	//			else
	//				vecStackedType.push_back(baseType);
	//			baseType = baseType->GetParent();
	//		}
	//	}

	//public:
	//	inline static void GetStackedTypesConstructionOrder(CNiflectType* derivedType, TArrayNif<CInheritableType*>& vecStackedType)
	//	{
	//		GetStackedTypes(derivedType, false, vecStackedType);
	//	}
	//	inline static void GetStackedTypesDestructionOrder(CNiflectType* derivedType, TArrayNif<CInheritableType*>& vecStackedType)
	//	{
	//		GetStackedTypes(derivedType, true, vecStackedType);
	//	}

	public:
		static CInheritableType* Cast(CNiflectType* base)
		{
			ASSERT(base == NULL || dynamic_cast<CInheritableType*>(base) != NULL);
			return static_cast<CInheritableType*>(base);
		}
		static CInheritableType* CastChecked(CNiflectType* base)
		{
			return dynamic_cast<CInheritableType*>(base);
		}

	private:
		CInheritableType* m_parent;//todo: 应定义AddChild建立层级关系; 进一步地, 可能还需要另外的容器建立引用关系, 目前不确认引用关系是静态或动态建立
	};

	typedef CInheritableType CStruct;
	
	//todo: 考虑是否从CStruct继承以复用树型关系, 但m_parent是不同的, 如果复用则CClass的m_parent使用CStruct的m_parent并相应Cast, 是否可接受
	class CClass : public CInheritableType
	{
		typedef CInheritableType inherited;
	public:
		static CClass* Cast(CNiflectType* base)
		{
			ASSERT(base == NULL || dynamic_cast<CClass*>(base) != NULL);
			return static_cast<CClass*>(base);
		}

	public:
		TArrayNif<CNiflectMethod2> m_vecMethod;
	};
}