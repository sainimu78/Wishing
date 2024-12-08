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
	auto type = mesh.GetType();
	using namespace RwTree;
	CRwNode rw;
	type->SaveInstanceToRwNode(&mesh, &rw);
	std::ofstream ofs;
	NiflectUtil::MakeDirectories(filePath);
	if (NiflectUtil::OpenFileStream(ofs, filePath))
		CJsonFormat::Write(&rw, ofs);
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

		{
			CreateAsset(NiflectUtil::ConcatPath(MyContent, "Mesh.json"));
		}

		tableHolder = NULL;
	}
}