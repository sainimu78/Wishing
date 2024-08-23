#pragma once
#include "Niflect/NiflectType.h"

namespace Niflect
{
	//为Module中所有CType的容器, 不需要被继承
	class CNiflectTable
	{
		friend class CNiflectModule;
	public:
		void Init(const CString& name)
		{
			m_name = name;
		}
		template <typename TInfo, typename TType>
		void RegisterType(const CString& typeName, const InvokeCreateFieldLayoutFunc& Func)
		{
			CTypeInvokations typeFuncs;
			typeFuncs.m_InvokeConstructorFunc = &GenericInstanceInvokeConstructor<TType>;
			typeFuncs.m_InvokeDestructorFunc = &GenericInstanceInvokeDestructor<TType>;
			typeFuncs.m_InvokeCreateFieldLayoutFunc = Func;

			auto shared = MakeShared<TInfo>();
			auto type = shared.Get();
			auto idx = this->AddType(shared);
			ASSERT(!TInternalRegisteredType<TType>::IsValid());
			TInternalRegisteredType<TType>::s_type = type;
			//type->InitStaticType<TType>();
			type->InitTypeMeta(sizeof(TType), CNiflectType::GetTypeHash<TType>(), typeName, idx, typeFuncs);
			ASSERT(TInternalRegisteredType<TType>::IsValid());
		}
		uint32 GetTypesCount() const
		{
			return static_cast<uint32>(m_vecType.size());//todo: 考虑如何避免cast
		}
		CNiflectType* GetTypeByIndex(uint32 idx) const
		{
			return m_vecType[idx].Get();
		}
		
	private:
		uint32 AddType(const CSharedType& type)//避免VS跳错, 暂时加My后缀
		{
			uint32 idx = this->GetTypesCount();
			m_vecType.push_back(type);
			return idx;
		}

	public:
		TArrayNif<CSharedType> m_vecType;
		CString m_name;
	};

	using CSharedTable = TSharedPtr<CNiflectTable>;
	
	template <typename TInfo, typename TType>
	class TStaticTableTypeReg
	{
	public:
		TStaticTableTypeReg(CNiflectTable* table, const CString& typeName, const InvokeCreateFieldLayoutFunc& Func)
		{
			table->RegisterType<TInfo, TType>(typeName, Func);
		}
		template <typename TNatimeta>
		TStaticTableTypeReg(CNiflectTable* table, const CString& typeName, const InvokeCreateFieldLayoutFunc& Func, const TNatimeta& natimeta)
			: TStaticTableTypeReg(table, typeName, Func)
		{
			auto type = StaticGetType<TType>();
			type->SetNatimeta(MakeShared<TNatimeta>(natimeta));
		}
	};

	template <typename TAccessor>
	static CSharedAccessor __InternalCreateFieldLayoutForFunctionPointer()
	{
		return MakeShared<TAccessor>();
	}

#define NIFLECT_MEMBER_FUNCTION_GET_TYPE_VIRTUAL()\
	public:\
		virtual Niflect::CNiflectType* GetType() const { return NULL; }

#define NIFLECT_MEMBER_FUNCTION_GET_TYPE_OVERRIDE(typeName)\
	public:\
		virtual Niflect::CNiflectType* GetType() const override\
		{\
			return Niflect::StaticGetType<typeName>();\
		}
	
//begin, 仅留作备用, 不需要考虑静态变量名冲突, 因为本就不能在同namespace中出现同名类型
//#define NIFLECT_STATIC_TYPE_REG_VAR_NAME_COMBINE_INNER(A, B) s_typeReg_##A##_##B
//#define NIFLECT_STATIC_TYPE_REG_VAR_NAME_COMBINE(A, B) NIFLECT_STATIC_TYPE_REG_VAR_NAME_COMBINE_INNER(A, B)
//#define NIFLECT_STATIC_TYPE_REG_VAR_NAME(typeName) NIFLECT_STATIC_TYPE_REG_VAR_NAME_COMBINE(typeName, __LINE__)
//end

#define NIFLECT_REGISTER(niflectType, typeName, invokeGetTable, customDataObject)\
	static Niflect::TStaticTableTypeReg<niflectType, typeName> s_typeReg_##typeName(invokeGetTable, #typeName, customDataObject);
}