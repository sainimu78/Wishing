#include "Editor/Test/TestSerializationRwTree.h"
#include "Niflect/Memory/Default/DefaultMemory.h"
#include "Niflect/Memory/Default/DefaultMemoryPoolScope.h"
#include "Niflect/NiflectBase.h"
#include "Niflect/Memory/Stats/NiflectMemoryStats.h"
#include "Niflect/Serialization/RwTree.h"
#include "Niflect/Util/DebugUtil.h"
#include "Niflect/Serialization/JsonFormat.h"
#include "Niflect/Serialization/BinaryFormat.h"
#include <fstream>
#include "Niflect/Util/StringUtil.h"
#include "Niflect/Test/TestDefinition.h"
#include "Editor/Diff/DiffArrays.h"
#include "Editor/Diff/Diff2.h"
#include "Niflect/Util/FileStreamUtil.h"

namespace TestSerializationRwTree
{
	using namespace RwTree;

	void TestMemory()
	{
		using namespace Niflect;
		CDefaultMemoryStatsScope memTestScope;
		auto stats = GetDefaultMemoryStats();
		if (true)//TLS Default Allocator
		{
			CDefaultMemoryPoolScope sdddddd;

			TestMemoryStatsOnThreadsBegin();
			DebugPrintTestTree();
			TestMemoryStatsOnThreadsEnd();
		}
	}
	void TestSerialization()
	{
		using namespace Niflect;
		CDefaultMemoryStatsScope memTestScope;
		auto stats = GetDefaultMemoryStats();
		if (true)
		{
			CRwNode root;
			auto rw = &root;
			SetRwTypedValue<bool>(AddRwValue(rw, "a"), true);
			SetRwTypedValue<int8>(AddRwValue(rw, "b"), 1);
			SetRwTypedValue<int16>(AddRwValue(rw, "c"), 2);
			SetRwTypedValue<int32>(AddRwValue(rw, "d"), 3);
			SetRwTypedValue<int64>(AddRwValue(rw, "e"), 4);
			SetRwTypedValue<uint8>(AddRwValue(rw, "f"), 5);
			SetRwTypedValue<uint16>(AddRwValue(rw, "g"), 6);
			SetRwTypedValue<uint32>(AddRwValue(rw, "h"), 7);
			SetRwTypedValue<uint64>(AddRwValue(rw, "i"), 8);
			SetRwTypedValue<float>(AddRwValue(rw, "j"), 9);
			SetRwTypedValue<double>(AddRwValue(rw, "k"), 10);
			SetRwTypedValue<Niflect::CString>(AddRwValue(rw, "l"), "11 in string");
			DebugPrintRecurs2(&root);
			ASSERT(GetRwTypedValue<bool>(FindRwValue(rw, "a")) == true);
			ASSERT(GetRwTypedValue<int8>(FindRwValue(rw, "b")) == 1);
			ASSERT(GetRwTypedValue<int16>(FindRwValue(rw, "c")) == 2);
			ASSERT(GetRwTypedValue<int32>(FindRwValue(rw, "d")) == 3);
			ASSERT(GetRwTypedValue<int64>(FindRwValue(rw, "e")) == 4);
			ASSERT(GetRwTypedValue<uint8>(FindRwValue(rw, "f")) == 5);
			ASSERT(GetRwTypedValue<uint16>(FindRwValue(rw, "g")) == 6);
			ASSERT(GetRwTypedValue<uint32>(FindRwValue(rw, "h")) == 7);
			ASSERT(GetRwTypedValue<uint64>(FindRwValue(rw, "i")) == 8);
			ASSERT(GetRwTypedValue<float>(FindRwValue(rw, "j")) == 9);
			ASSERT(GetRwTypedValue<double>(FindRwValue(rw, "k")) == 10);
			ASSERT(GetRwTypedValue<Niflect::CString>(FindRwValue(rw, "l")) == "11 in string");
			printf("");
		}
		if (false)//д�����õ� JSON ��ʽ�ļ�
		{
			const auto oldData = NiflectUtil::ReadStringFromFile(TestDefinition::FilePath::InputJson_JsonFormat);
			{
				CRwNode root;
				DebugBuildStructure(&root);
				//std::ofstream ofs(TestDefinition::FilePath::InputJson_JsonFormat, std::ios::binary);
				NiflectUtil::COutputFileStream ofs(TestDefinition::FilePath::InputJson_JsonFormat);
				CJsonFormat::Write(&root, ofs);
			}
			if (!oldData.empty())
				ASSERT(NiflectUtil::ReadStringFromFile(TestDefinition::FilePath::InputJson_JsonFormat) == oldData);
		}
		if (false)//JSON ��ʽ��
		{
			{
				CRwNode root;
				//std::ifstream ifs(TestDefinition::FilePath::InputJson_JsonFormat, std::ios::binary);
				NiflectUtil::CInputFileStream ifs(TestDefinition::FilePath::InputJson_JsonFormat);
				CJsonFormat::Read(&root, ifs);

				//std::ofstream ofs(TestDefinition::FilePath::OutputJson_JsonFormat, std::ios::binary);
				NiflectUtil::COutputFileStream ofs(TestDefinition::FilePath::OutputJson_JsonFormat);
				CJsonFormat::Write(&root, ofs);
			}
			ASSERT(NiflectUtil::ReadStringFromFile(TestDefinition::FilePath::InputJson_JsonFormat) == NiflectUtil::ReadStringFromFile(TestDefinition::FilePath::OutputJson_JsonFormat));
		}
		if (false)//JSON ��ʽ�� rapidjson ��д����
		{
			{
				CRwNode root;
				NiflectUtil::CInputFileStream ifs(TestDefinition::FilePath::InputJson_AnimGraphEditorData);
				CJsonFormat::Read(&root, ifs);

				NiflectUtil::COutputFileStream ofs(TestDefinition::FilePath::OutputJson_AnimGraphEditorData);
				CJsonFormat::Write(&root, ofs);
			}

			//д�Ľ������һЩ����
			//1. �޷�ԭ��ת��С��
			//2. ���� rapidjson ��������, �����ַ�Ϊ4���ո�, CJsonFormat Ϊ1�� Tab

			{
				//��Ϊ���Խ�tab����4���ո�
				Niflect::TArrayNif<Niflect::CString> vecLineA;
				Niflect::CString line;
				Niflect::CStringStream ss;
				auto strFromFile = NiflectUtil::ReadStringFromFile(TestDefinition::FilePath::OutputJson_AnimGraphEditorData);
				ss << strFromFile;
				while (std::getline(ss, line))
					vecLineA.push_back(line);
				for (auto& it : vecLineA)
				{
					auto pos = it.find_first_not_of("\t");
					if (pos > 0)
					{
						const auto& cnt = pos;
						for (uint32 idx1 = 0; idx1 < cnt; ++idx1)
							it.erase(it.begin());
						Niflect::CString testIndents;
						for (uint32 idx1 = 0; idx1 < cnt; ++idx1)
							testIndents += "    ";
						it = testIndents + it;
					}
				}
				ss.clear();
				Niflect::TArrayNif<Niflect::CString> vecLineB;
				ss << NiflectUtil::ReadStringFromFile(TestDefinition::FilePath::InputJson_AnimGraphEditorData);
				while (std::getline(ss, line))
					vecLineB.push_back(line);
				ASSERT(vecLineA.size() == vecLineB.size());
				bool same = vecLineA.size() > 0;
				ASSERT(same);
				uint32 diffCnt = 0;
				for (auto idx = 0; idx < vecLineA.size(); ++idx)
				{
					auto& a = vecLineA[idx];
					auto& b = vecLineB[idx];
					if (a != b)
					{
						diffCnt++;
						Niflect::CString strA;
						Niflect::CString strB;
						{
							auto pos = a.find_last_of(' ');
							strA = a.substr(pos + 1, a.length() - pos);
						}
						{
							auto pos = b.find_last_of(' ');
							strB = b.substr(pos + 1, b.length() - pos);
						}
						auto numA = std::stod(strA.c_str());
						auto numB = std::stod(strB.c_str());
						if (numA != numB)
						{
							same = false;
							break;
						}
						else
						{
							ASSERT((strA.length() - strB.length()) == 1);
						}
					}
				}
				ASSERT(diffCnt == 4);
				ASSERT(same);
			}
		}
		if (false)//JSON & �Զ��� Binary ��ʽ�໥ת��
		{
			{
				CRwNode root;
				DebugBuildStructure(&root);
				{
					//std::ofstream ofs(TestDefinition::FilePath::OutputBinary_0, std::ios::binary);
					NiflectUtil::COutputFileStream ofs(TestDefinition::FilePath::OutputBinary_0);
					CBinaryFormat::A_2(&root, ofs);
				}
				{
					//std::ofstream ofs(TestDefinition::FilePath::OutputJson_0, std::ios::binary);
					NiflectUtil::COutputFileStream ofs(TestDefinition::FilePath::OutputJson_0);
					CJsonFormat::Write(&root, ofs);
				}
			}
			{
				CRwNode root;
				//std::ifstream ifs(TestDefinition::FilePath::OutputBinary_0, std::ios::binary);
				NiflectUtil::CInputFileStream ifs(TestDefinition::FilePath::OutputBinary_0);
				CBinaryFormat::B_2(&root, ifs);

				//std::ofstream ofs(TestDefinition::FilePath::OutputJson_1, std::ios::binary);
				NiflectUtil::COutputFileStream ofs(TestDefinition::FilePath::OutputJson_1);
				CJsonFormat::Write(&root, ofs);
			}

			ASSERT(NiflectUtil::ReadStringFromFile(TestDefinition::FilePath::OutputJson_0) == NiflectUtil::ReadStringFromFile(TestDefinition::FilePath::OutputJson_1));
		}
		if (false)
		{
			//TestDiffLCS::SimpleNumberArrays();
			//TestDiffLCS::TestDiff();
			TestDiffLCS::TestLargeData();
			printf("");
		}
		if (false)
		{
			TestDiffEditGraph::TestLargeData();
			printf("");
		}
	}
}