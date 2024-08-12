#pragma once
#include "Niflect/NiflectRegistration.h"
//#include "Niflect/Test/NiflectGenerated/MyModule/MyField.private.h"
//#include "Niflect/Test/NiflectGenerated/MyModule/MyClass.private.h"
//#include "Niflect/Test/NiflectGenerated/MyModule/MyTransform.private.h"

namespace Niflect
{
	TSharedPtr<CNiflectRegistration>* s_reg = NULL;
	CNiflectRegistration* CNiflectRegistration::Get()
	{
		static TSharedPtr<CNiflectRegistration> s_holder(MakeShared<CNiflectRegistration>());
		if (s_reg == NULL)
			s_reg = &s_holder;
		return s_holder.Get();
	}
	void CNiflectRegistration::Release()
	{
		*s_reg = NULL;
	}
	void CNiflectRegistration::InitialReg()
	{
	}
}

namespace NiflectModuleReg
{
	using namespace Niflect;
	
	//class CModuleReg_MyModule0 : public CNiflectRegistration
	//{
	//protected:
	//	virtual void DoInitTables() override
	//	{
	//		{
	//			auto table = this->AddNewTable();
	//			table->Init(CString());
	//		}
	//	}
	//	//todo: 创建前可与分配空间, 实现预分类后, #1, ..., #3, 可并行执行(如 parallel for)
	//	virtual void DoRegisterTypes() override
	//	{
	//		//#1, 创建模块内所有 Reflector Type
	//		{
	//			auto& table = this->GetMutableTable(0);
	//			//MyTestClassScope::CInheritableTypeReg_CFloatField::StaticRegisterType(table);//todo: 基础类型需要另外一种注册流程, 如模块手工注册反射类流程
	//			//MyTestClassScope::CInheritableTypeReg_CStringField::StaticRegisterType(table);
	//			//MyTestClassScope::CInheritableTypeReg_CBoolField::StaticRegisterType(table);
	//			//MyTestClassScope::CEnumReg_EMyEnum_OptionStyle::StaticRegisterType(table);
	//			//MyTestClassScope::CInheritableTypeReg_CMyClass0::StaticRegisterType(table);
	//			//MyTestClassScope::CInheritableTypeReg_CMyClassBase0::StaticRegisterType(table);
	//			//MyTestClassScope::CInheritableTypeReg_CMyTransformFloat::StaticRegisterType(table);
	//			//MyTestClassScope::CInheritableTypeReg_CMyClass1::StaticRegisterType(table);
	//		}
	//	}
	//	virtual void DoInitTypes() const override
	//	{
	//		//#2, 填反射信息
	//		{
	//			//MyTestClassScope::CInheritableTypeReg_CFloatField::StaticInitInheritance();//todo: 基础类型需要另外一种注册流程, 如模块手工注册反射类流程
	//			//MyTestClassScope::CInheritableTypeReg_CStringField::StaticInitInheritance();
	//			//MyTestClassScope::CInheritableTypeReg_CBoolField::StaticInitInheritance();
	//			//MyTestClassScope::CEnumReg_EMyEnum_OptionStyle::StaticInitEnumMeta();
	//			//MyTestClassScope::CInheritableTypeReg_CMyClass0::StaticInitInheritance();
	//			//MyTestClassScope::CInheritableTypeReg_CMyClassBase0::StaticInitInheritance();
	//			//MyTestClassScope::CInheritableTypeReg_CMyTransformFloat::StaticInitInheritance();
	//			//MyTestClassScope::CInheritableTypeReg_CMyClass1::StaticInitInheritance();
	//		}
	//	}
	//	virtual void DoInitMethods() const override
	//	{
	//		//MyTestClassScope::CInheritableTypeReg_CMyClassBase0::StaticInitMethods();
	//	}
	//};

	//static void CreateModuleRegistration()
	//{
	//	CNiflectRegistration::StaticCreate<CModuleReg_MyModule0>();
	//}
	//
	//static void DestroyModuleRegistration()
	//{
	//	CNiflectRegistration::StaticDestroy();
	//}
}

const Niflect::CNiflectRegistration* GetNiflectModuleRegistration()
{
	return Niflect::CNiflectRegistration::Get();
}