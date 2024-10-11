#include "NiflectGen/Test/TestTypeRegSignature.h"
#include "NiflectGen/Generator/Generator.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "Niflect/Memory/Default/DefaultMemory.h"
#include "NiflectGen/Collector/Collector.h"
#include "NiflectGen/Resolver/Resolver.h"

namespace TestGen
{
	using namespace NiflectGen;

	static void TestSuccess_TypeRegSignature0()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature0.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 7);
					auto it = vecSignature.begin();
					//单一类型
					ASSERT(*(it++) == "TestMyFinding::EMyOption");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "bool");
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "int32");
					ASSERT(*(it++) == "TestAccessor2::TMyTransform<float>");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature1()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature1.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 4);
					auto it = vecSignature.begin();
					//特化
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "TestAccessor2::TMyTransform<float>");
					ASSERT(*(it++) == "Niflect::TArrayNif<bool>");
					ASSERT(*(it++) == "std::vector<bool>");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature2()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature2.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 4);
					auto it = vecSignature.begin();
					//1维容器模板
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "+float");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature3()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature3.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 6);
					auto it = vecSignature.begin();
					//嵌套1维容器模板
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "+float");
					ASSERT(*(it++) == "Niflect::TArrayNif<Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "+Niflect::TArrayNif<float>");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature4()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature4.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 6);
					auto it = vecSignature.begin();
					//结构模板
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-float");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature5()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature5.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 8);
					auto it = vecSignature.begin();
					//1维容器模板与结构模板
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-float");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, float>");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, float>");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature6()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature6.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 10);
					auto it = vecSignature.begin();
					//不同的1容器模板嵌套
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "+float");
					ASSERT(*(it++) == "std::pair<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature7()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature7.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 8);
					auto it = vecSignature.begin();
					//1维容器模板套特化
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "Niflect::TArrayNif<bool>");
					ASSERT(*(it++) == "std::pair<Niflect::CString, Niflect::TArrayNif<bool> >");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-Niflect::TArrayNif<bool>");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, Niflect::TArrayNif<bool> >");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, Niflect::TArrayNif<bool> >");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature8()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature8.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 10);
					auto it = vecSignature.begin();
					//不同的1维容器模板嵌套
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-float");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, float>");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> >");
					ASSERT(*(it++) == "+Niflect::TMap<Niflect::CString, float>");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature9()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature9.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 12);
					auto it = vecSignature.begin();
					//不同的1维容器模板嵌套
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "+float");
					ASSERT(*(it++) == "std::pair<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "Niflect::TArrayNif<Niflect::TMap<Niflect::CString, Niflect::TArrayNif<float> > >");
					ASSERT(*(it++) == "+Niflect::TMap<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature10()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature10.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 15);
					auto it = vecSignature.begin();
					//位置在后的成员不产生重复Signature
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-float");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, float>");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> >");
					ASSERT(*(it++) == "+Niflect::TMap<Niflect::CString, float>");
					ASSERT(*(it++) == "std::pair<Niflect::CString, Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> > >");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> >");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> > >");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> > >");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature11()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature11.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 40);
					auto it = vecSignature.begin();
					//综合测试
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "bool");
					ASSERT(*(it++) == "Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "+float");
					ASSERT(*(it++) == "Niflect::TArrayNif<bool>");
					ASSERT(*(it++) == "Niflect::TArrayNif<Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "+Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "Niflect::TArrayNif<Niflect::TArrayNif<bool> >");
					ASSERT(*(it++) == "+Niflect::TArrayNif<bool>");
					ASSERT(*(it++) == "std::vector<float>");
					ASSERT(*(it++) == "+float");
					ASSERT(*(it++) == "std::vector<bool>");
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-float");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, float>");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "int32");
					ASSERT(*(it++) == "std::pair<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "std::pair<Niflect::CString, Niflect::TArrayNif<bool> >");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-Niflect::TArrayNif<bool>");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, Niflect::TArrayNif<bool> >");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, Niflect::TArrayNif<bool> >");
					ASSERT(*(it++) == "Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> >");
					ASSERT(*(it++) == "+Niflect::TMap<Niflect::CString, float>");
					ASSERT(*(it++) == "std::pair<Niflect::CString, Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> > >");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> >");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> > >");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> > >");
					ASSERT(*(it++) == "TestAccessor2::TMyTransform<float>");
					ASSERT(*(it++) == "Niflect::TArrayNif<Niflect::TMap<Niflect::CString, Niflect::TArrayNif<float> > >");
					ASSERT(*(it++) == "+Niflect::TMap<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature12()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature12.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 4);
					auto it = vecSignature.begin();
					//成员为TaggedType
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "bool");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_1");
					ASSERT(*(it++) == "float");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_TypeRegSignature13()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			CModuleRegInfo info;
			info.m_vecOriginalHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestOriginalTypeRegSignature13.h"));
			info.m_vecBindingSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorBindingTypeRegSignature.h"));
			NiflectGenDefinition::Test::AddBasicHeaderSearchPaths(info.m_vecHeaderSearchPath);
			gen->SetModuleRegInfo(info);
			gen->Generate([&info](void* cursorAddr)
				{
					auto& cursor = *static_cast<CXCursor*>(cursorAddr);
					CTaggedNode2 taggedRoot;
					CGenLog log;
					CCollectingContext context(&log);
					CCollectionData collectionData;
					CDataCollector collector;
					collector.Collect(cursor, &taggedRoot, context, collectionData);
					ASSERT(log.m_vecText.size() == 0);
					CResolvingContext resolvingContext(&log);
					CModuleRegInfoValidated validatedModuleRegInfo(info);
					CResolver resolver(collectionData, validatedModuleRegInfo);
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 26);
					auto it = vecSignature.begin();
					//成员含TaggedType的综合测试
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "bool");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_1");
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "std::pair<Niflect::CString, TestMyFinding::CMyClass_0>");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "Niflect::TArrayNif<TestMyFinding::CMyClass_0>");
					ASSERT(*(it++) == "+TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, TestMyFinding::CMyClass_0>");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, TestMyFinding::CMyClass_0>");
					ASSERT(*(it++) == "std::pair<Niflect::CString, Niflect::TArrayNif<TestMyFinding::CMyClass_0> >");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-Niflect::TArrayNif<TestMyFinding::CMyClass_0>");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, Niflect::TArrayNif<TestMyFinding::CMyClass_0> >");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, Niflect::TArrayNif<TestMyFinding::CMyClass_0> >");
					ASSERT(*(it++) == "Niflect::TArrayNif<Niflect::TMap<Niflect::CString, Niflect::TArrayNif<TestMyFinding::CMyClass_0> > >");
					ASSERT(*(it++) == "+Niflect::TMap<Niflect::CString, Niflect::TArrayNif<TestMyFinding::CMyClass_0> >");
					ASSERT(*(it++) == "Niflect::TArrayNif<Niflect::TMap<Niflect::CString, TestMyFinding::CMyClass_0> >");
					ASSERT(*(it++) == "+Niflect::TMap<Niflect::CString, TestMyFinding::CMyClass_0>");
					ASSERT(*(it++) == "std::pair<Niflect::CString, Niflect::TArrayNif<Niflect::TMap<Niflect::CString, TestMyFinding::CMyClass_0> > >");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-Niflect::TArrayNif<Niflect::TMap<Niflect::CString, TestMyFinding::CMyClass_0> >");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, Niflect::TArrayNif<Niflect::TMap<Niflect::CString, TestMyFinding::CMyClass_0> > >");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, Niflect::TArrayNif<Niflect::TMap<Niflect::CString, TestMyFinding::CMyClass_0> > >");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	void TestSuccess_TypeRegSignature()
	{
		TestSuccess_TypeRegSignature0();
		TestSuccess_TypeRegSignature1();
		TestSuccess_TypeRegSignature2();
		TestSuccess_TypeRegSignature3();
		TestSuccess_TypeRegSignature4();
		TestSuccess_TypeRegSignature5();
		TestSuccess_TypeRegSignature6();
		TestSuccess_TypeRegSignature7();
		TestSuccess_TypeRegSignature8();
		TestSuccess_TypeRegSignature9();
		TestSuccess_TypeRegSignature10();
		TestSuccess_TypeRegSignature11();
		TestSuccess_TypeRegSignature12();
		TestSuccess_TypeRegSignature13();
	}
}