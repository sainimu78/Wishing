#include "NiflectGen/Test/TestFieldResocursorName.h"
#include "NiflectGen/Generator/Generator.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "Niflect/Memory/Default/DefaultMemory.h"
#include "NiflectGen/Collector/Collector.h"
#include "NiflectGen/Resolver/Resolver.h"
#include "NiflectGen/CodeWriter/ModuleReg/ModuleRegCodeWriter.h"

namespace TestGen
{
	using namespace NiflectGen;

	static void InitGenFieldResocursorName(CGenerator& gen, uint32 idx)
	{
		CModuleRegInfo info;
		auto moduleHeader = NiflectUtil::FormatString("%s%u.h", CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestModuleHeaderFieldResocursorName"), idx);
		info.m_vecModuleHeader.push_back(moduleHeader);
		info.m_vecAccessorSettingHeader.push_back(CONCAT_CONST_CHAR_2(ROOT_TEST_PATH, "/TestAccessorSettingFieldResocursorName.h"));
		Test::AddHeaderSearchPaths(info.m_vecParsingHeaderSearchPath, info.m_writingHeaderSearchPaths);
		gen.InitModuleRegInfo(info);
	}

	static void TestSuccess_FieldResocursorName0()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 0);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 7);
					auto it = vecSignature.begin();
					//��һ����
					ASSERT(*(it++) == "TestMyFinding::EMyOption");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "bool");
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "int32");
					ASSERT(*(it++) == "TestAccessor2::TMyTransform<float>");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName1()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 1);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 4);
					auto it = vecSignature.begin();
					//�ػ�
					ASSERT(*(it++) == "TestAccessor2::TMyTransform<float>");
					ASSERT(*(it++) == "Niflect::TArrayNif<bool>");
					ASSERT(*(it++) == "std::vector<bool>");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName2()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 2);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 4);
					auto it = vecSignature.begin();
					//1ά����ģ��
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "+float");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName3()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 3);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 6);
					auto it = vecSignature.begin();
					//Ƕ��1ά����ģ��
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "+float");
					ASSERT(*(it++) == "Niflect::TArrayNif<Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "+Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName4()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 4);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 6);
					auto it = vecSignature.begin();
					//�ṹģ��
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-float");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName5()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 5);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 8);
					auto it = vecSignature.begin();
					//1ά����ģ����ṹģ��
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-float");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, float>");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName6()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 6);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 10);
					auto it = vecSignature.begin();
					//��ͬ��1����ģ��Ƕ��
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "+float");
					ASSERT(*(it++) == "std::pair<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-Niflect::TArrayNif<float>");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, Niflect::TArrayNif<float> >");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName7()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 7);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 8);
					auto it = vecSignature.begin();
					//1ά����ģ�����ػ�
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "Niflect::TArrayNif<bool>");
					ASSERT(*(it++) == "std::pair<Niflect::CString, Niflect::TArrayNif<bool> >");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-Niflect::TArrayNif<bool>");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, Niflect::TArrayNif<bool> >");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, Niflect::TArrayNif<bool> >");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName8()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 8);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 10);
					auto it = vecSignature.begin();
					//��ͬ��1ά����ģ��Ƕ��
					ASSERT(*(it++) == "Niflect::CString");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "-Niflect::CString");
					ASSERT(*(it++) == "-float");
					ASSERT(*(it++) == "Niflect::TMap<Niflect::CString, float>");
					ASSERT(*(it++) == "+std::pair<Niflect::CString, float>");
					ASSERT(*(it++) == "Niflect::TArrayNif<Niflect::TMap<Niflect::CString, float> >");
					ASSERT(*(it++) == "+Niflect::TMap<Niflect::CString, float>");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName9()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 9);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 12);
					auto it = vecSignature.begin();
					//��ͬ��1ά����ģ��Ƕ��
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
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName10()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 10);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 15);
					auto it = vecSignature.begin();
					//λ���ں�ĳ�Ա�������ظ�Signature
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
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName11()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 11);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 40);
					auto it = vecSignature.begin();
					//�ۺϲ���
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
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName12()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 12);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 4);
					auto it = vecSignature.begin();
					//��ԱΪTaggedType
					ASSERT(*(it++) == "bool");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_1");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName13()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 13);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					ASSERT(vecSignature.size() == 26);
					auto it = vecSignature.begin();
					//��Ա��TaggedType���ۺϲ���
					ASSERT(*(it++) == "bool");
					ASSERT(*(it++) == "float");
					ASSERT(*(it++) == "TestMyFinding::CMyClass_0");
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
					ASSERT(*(it++) == "TestMyFinding::CMyClass_1");
					ASSERT(it == vecSignature.end());
				});
		}
	}
	static void TestSuccess_FieldResocursorName14()
	{
		auto memTest = Niflect::GetDefaultMemoryStats();
		{
			auto gen = CreateGenerator();
			InitGenFieldResocursorName(*gen, 14);
			CCodeGenData genData;
			gen->Generate(genData, [&gen](void* cursorAddr)
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
					CResolver resolver(collectionData, gen->GetModuleRegInfo());
					CResolvedData resolvedData;
					resolver.Resolve4(&taggedRoot, resolvingContext, resolvedData);
					ASSERT(log.m_vecText.size() == 0);
					Niflect::TArrayNif<Niflect::CString> vecSignature;
					resolvedData.m_signatureMapping.DebugGenSignatures(vecSignature);
					Niflect::TArrayNif<Niflect::CString> vecExpected;
					//1ά����ģ���׽ṹģ��
					vecExpected.push_back("Niflect::CString");
					vecExpected.push_back("float");
					vecExpected.push_back("std::pair<Niflect::CString, float>");
					vecExpected.push_back("-Niflect::CString");
					vecExpected.push_back("-float");
					vecExpected.push_back("Niflect::TArrayNif<std::pair<Niflect::CString, float> >");
					vecExpected.push_back("+std::pair<Niflect::CString, float>");
					vecExpected.push_back("TestMyFinding::CMyClass_0");
					uint32 idx = 0;
					for (auto& it : vecSignature)
						ASSERT(vecExpected[idx++] == it);
					ASSERT(vecSignature.size() == idx);
				});
		}
	}
	void TestSuccess_FieldResocursorName()
	{
		TestSuccess_FieldResocursorName0();
		TestSuccess_FieldResocursorName1();
		TestSuccess_FieldResocursorName2();
		TestSuccess_FieldResocursorName3();
		TestSuccess_FieldResocursorName4();
		TestSuccess_FieldResocursorName5();
		TestSuccess_FieldResocursorName6();
		TestSuccess_FieldResocursorName7();
		TestSuccess_FieldResocursorName8();
		TestSuccess_FieldResocursorName9();
		TestSuccess_FieldResocursorName10();
		TestSuccess_FieldResocursorName11();
		TestSuccess_FieldResocursorName12();
		TestSuccess_FieldResocursorName13();
		TestSuccess_FieldResocursorName14();
	}
}