#pragma once
#include "Niflect/NiflectTable.h"

namespace Niflect
{
	typedef void (*ModuleRegisterTypesFunc)(CNiflectTable* table);
	typedef void (*ModuleInitTypesFunc)();

	class CNiflectModule
	{
	public:
		CNiflectModule()
			: m_RegisterTypesFunc(NULL)
			, m_InitTypesFunc(NULL)
		{
		}
		void InitMeta(const Niflect::CString& name, const ModuleRegisterTypesFunc& RegisterTypesFunc, const ModuleInitTypesFunc& InitTypesFunc)
		{
			m_name = name;
			m_RegisterTypesFunc = RegisterTypesFunc;
			m_InitTypesFunc = InitTypesFunc;
		}
		const Niflect::CString& GetName() const
		{
			return m_name;
		}
		void RegisterTypes()
		{
			m_RegisterTypesFunc(&m_table);
		}
		void InitTypes()
		{
			m_InitTypesFunc();
		}

	private:
		Niflect::CString m_name;
		CNiflectTable m_table;
		ModuleRegisterTypesFunc m_RegisterTypesFunc;
		ModuleInitTypesFunc m_InitTypesFunc;
	};
	using CSharedModule = Niflect::TSharedPtr<CNiflectModule>;

	typedef Niflect::CNiflectModule* (*GetModuleFunc)();

	constexpr const char* GeneratedGetModule = "NiflectGeneratedGetModule";
}