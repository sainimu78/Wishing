#include <stdio.h>
#include "Engine/Engine.h"
//#include "Windows.h"
#include "Niflect/Memory/Default/DefaultMemory.h"
#include "Niflect/Memory/Default/DefaultMemoryPoolScope.h"
#include "Niflect/Base/NiflectBase.h"
#include "Niflect/Memory/Stats/NiflectMemoryStats.h"
#include "Niflect/Serialization/RwTree.h"
#include "Niflect/Util/DebugUtil.h"

class CMyClassForSimplifiedMakeShared
{
public:
	CMyClassForSimplifiedMakeShared()
		: m_float(1.23f)
		, m_bool(true)
		, m_double(43.21)
	{

	}
	float m_float;
	bool m_bool;
	double m_double;
};

namespace Niflect
{
	static void DebugBuildSingleValue(CRwNode* root)
	{
		auto value = ToRwValue(root);
		value->SetFloat(1.23f);
	}
	static void DebugBuildSingleArray(CRwNode* root)
	{
		auto rwArray = ToRwArray(root);
		rwArray->AddFloat(1.23f);
		rwArray->AddFloat(4.56f);
	}
	static void DebugBuildStructure(CRwNode* root)
	{
		AddRwFloat(root, "Nihao", 1.23f);
		{
			auto node0 = AddRwNode(root, "Haike");
			AddRwFloat(node0, "Bucuo", 4.56f);
			AddRwFloat(node0, "Shima", 7.89f);
			AddRwString(node0, "Zhende", "Some Text");
		}
		{
			auto rwArray = AddRwArray(root, "Buxin");
			rwArray->AddFloat(2.34f);
			rwArray->AddFloat(2.56f);
		}
		{
			auto rwArray = AddRwArray(root, "Shide");
			{
				auto node1 = rwArray->AddItemNode();
				AddRwFloat(node1, "My Value 0", 3.12f);
			}
			{
				auto node1 = rwArray->AddItemNode();
				AddRwBool(node1, "My Value 1", false);
			}
			{
				auto node1 = rwArray->AddItemNode();
				AddRwBool(node1, "My Value 2", true);
			}
			{
				auto node1 = rwArray->AddItemNode();
				AddRwString(node1, "My Value 3", "My String Value");
			}
		}
	}

	//static void DebugPrintRecurs(const CRwNode& rwNode, uint32 arrayItemIdx = INDEX_NONE, uint32 level = 0)
	//{
	//	auto strLevel = NiflectUtil::DebugIndentToString(level);
	//	printf("%s", strLevel.c_str());
	//	if (arrayItemIdx == INDEX_NONE)
	//	{
	//		printf("%s", rwNode->GetName().c_str());
	//	}
	//	else
	//	{
	//		ASSERT(rwNode->GetName().empty());
	//		printf("[%u]", arrayItemIdx);
	//	}
	//	if (rwNode->IsValue())
	//	{
	//		if (arrayItemIdx == INDEX_NONE)
	//			printf(", ");

	//		Niflect::CString str;
	//		auto rwValue = rwNode->GetValue();
	//		switch (rwValue->GetType())
	//		{
	//		case ERwValueType::Bool:
	//			str = rwValue->GetBool() ? "true" : "false";
	//			break;
	//		case ERwValueType::Float:
	//			str = std::to_string(rwValue->GetFloat()).c_str();
	//			break;
	//		case ERwValueType::Double:
	//			str = std::to_string(rwValue->GetDouble()).c_str();
	//			break;
	//		case ERwValueType::Int32:
	//			str = std::to_string(rwValue->GetInt32()).c_str();
	//			break;
	//		case ERwValueType::String:
	//			str = rwValue->GetString().c_str();
	//			break;
	//		default:
	//			ASSERT(false);
	//			break;
	//		}
	//		printf("%s", str.c_str());
	//		printf("\n");
	//	}
	//	else if (rwNode->IsArray())
	//	{
	//		level++;
	//		printf("\n");
	//		auto rwArray = rwNode->GetArray();
	//		uint32 idxInc = 0;
	//		for (uint32 idx = 0; idx < rwArray->GetItemsCount(); ++idx)
	//			DebugPrintRecurs(rwArray->GetItem(idx), idxInc++, level);
	//	}
	//	else
	//	{
	//		level++;
	//		printf("\n");
	//		for (uint32 idx = 0; idx < rwNode->GetNodesCount(); ++idx)
	//			DebugPrintRecurs(rwNode->GetNode(idx), INDEX_NONE, level);
	//	}
	//}
	static void DebugPrintRecurs2(const CRwNode* rwNode, uint32 arrayItemIdx = INDEX_NONE, uint32 level = 0)
	{
		auto strLevel = NiflectUtil::DebugIndentToString(level);
		printf("%s", strLevel.c_str());
		if (arrayItemIdx == INDEX_NONE)
		{
			printf("%s", rwNode->GetName().c_str());
		}
		else
		{
			ASSERT(rwNode->GetName().empty());
			printf("[%u]", arrayItemIdx);
		}
		if (rwNode->IsValue())
		{
			if (arrayItemIdx == INDEX_NONE)
				printf(", ");

			Niflect::CString str;
			auto rwValue = rwNode->GetValue();
			switch (rwValue->GetType())
			{
			case ERwValueType::Bool:
				str = rwValue->GetBool() ? "true" : "false";
				break;
			case ERwValueType::Float:
				str = std::to_string(rwValue->GetFloat()).c_str();
				break;
			case ERwValueType::Double:
				str = std::to_string(rwValue->GetDouble()).c_str();
				break;
			case ERwValueType::Int32:
				str = std::to_string(rwValue->GetInt32()).c_str();
				break;
			case ERwValueType::String:
				str = rwValue->GetString().c_str();
				break;
			default:
				ASSERT(false);
				break;
			}
			printf("%s", str.c_str());
			printf("\n");
		}
		else
		{
			level++;
			printf("\n");
			for (uint32 idx = 0; idx < rwNode->GetNodesCount(); ++idx)
				DebugPrintRecurs2(rwNode->GetNode(idx), rwNode->IsArray() ? idx : INDEX_NONE, level);
		}
	}
	static void DebugPrintTestTree()
	{
		CRwNode root;
		DebugBuildStructure(&root);
		DebugPrintRecurs2(&root);
	}
}

typedef void (*FuncTestAPI_C)();

int main(int argc, char** argv)
{
	TestAPI_Cpp();
	
	using namespace Niflect;
	{
		auto stats = DebugGetMemoryStats();
		DebugPrintTestTree();
		printf("");
	}
	auto mem = Niflect::CMemory::Alloc(10);
	Niflect::CMemory::Free(mem);

	//auto hLib = LoadLibrary("Engine.dll");
	//if (hLib != NULL)
	//{
	//	if (auto Func = reinterpret_cast<FuncTestAPI_C>(GetProcAddress(hLib, "TestAPI_C")))
	//		Func();
	//}

	printf("Finished\n");
	fflush(stdout);
	return 0;
}