#include "Editor/Test/TestEdAsset.h"
#include "Editor_private.h"
#include "Niflect/Memory/Default/DefaultMemory.h"
#include "Niflect/Util/ConcatHardCodedStrings.h"
#include "Niflect/Util/StringUtil.h"
#include "Niflect/Serialization/JsonFormat.h"
#include "Niflect/Util/FileStreamUtil.h"
#include "Niflect/Util/SystemUtil.h"

#define TEST_ROOT_PATH "../../../../../.."
#define TEST_CONTENT_ROOT_PATH CONCAT_HARDCODED_STRINGS_2(TEST_ROOT_PATH, "/MyContent")
constexpr const char* MyContent = TEST_CONTENT_ROOT_PATH;

static void CreateAsset(const Niflect::CString& filePath)
{
	Editor::CEdMesh mesh;
	mesh.m_debugName = "nihao";
	auto type = mesh.GetType();
	using namespace RwTree;
	CRwNode rw;
	AddRwString(&rw, "TypeName", type->GetTypeName());
	auto rwData = AddRwNode(&rw, "Data");
	type->SaveInstanceToRwNode(&mesh, rwData);
	std::ofstream ofs;
	NiflectUtil::MakeDirectories(filePath);
	if (NiflectUtil::OpenFileStream(ofs, filePath))
	{
		CJsonFormat::Write(&rw, ofs);
	}
	else
	{
		ASSERT(false);
	}
}
static Niflect::TSharedPtr<Editor::CEdAsset> LoadAsset(Niflect::CNiflectTable* table, const Niflect::CString& filePath)
{
	Niflect::TSharedPtr<Editor::CEdAsset> asset;
	using namespace RwTree;
	std::ifstream ifs;
	if (NiflectUtil::OpenFileStream(ifs, filePath))
	{
		CRwNode rw;
		CJsonFormat::Read(&rw, ifs);
		auto typeName = FindRwString(&rw, "TypeName");
		if (auto type = table->FindTypeByTypeName(typeName))
		{
			auto rwData = FindRwNode(&rw, "Data");
			asset = type->MakeSharedInstance<Editor::CEdAsset>();
			type->LoadInstanceFromRwNode(asset.Get(), rwData);
		}
	}
	else
	{
		ASSERT(false);
	}
	return asset;
}

void TestEdAsset()
{
	auto memTest = Niflect::GetDefaultMemoryStats();
	{
		auto tableHolder = Niflect::MakeShared<Niflect::CNiflectTable>();
		auto table = tableHolder.Get();
		Niflect::GeneratedInitialReg(table);
		Niflect::GeneratedInitTypes();
		table->InitTypesLayout();

		auto meshFilePath = NiflectUtil::ConcatPath(MyContent, "Mesh.json");
		{
			{
				CreateAsset(meshFilePath);
			}
			{
				auto asset = LoadAsset(table, meshFilePath);
				auto mesh = asset.Cast<Editor::CEdMesh>();
				printf("");
			}
		}

		tableHolder = NULL;
	}
}