#include "NiflectGen/CodeWriter/GenTimeNiflectMacro.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "Niflect/Util/SystemUtil.h"

namespace NiflectGen
{
	void WriteGenTimeNiflectMacroHeader(const SGenTimeNiflectMacroHeaderWritingContext& context)
	{
		CCodeLines linesMacroTagDefine;
		linesMacroTagDefine.push_back("#define GENERATED_BODY(...) typedef void* CONCAT_SYMBOLS_2(" MACROTAG_GENERATED_BODY ",__LINE__);");
		linesMacroTagDefine.push_back("#define NIFLECTGENTAG_TYPE typedef void* " MACROTAG_TYPE ";");
		linesMacroTagDefine.push_back("#define NIFLECTGENTAG_FIELD typedef void* CONCAT_SYMBOLS_2(" MACROTAG_FIELD ",__LINE__);");
		linesMacroTagDefine.push_back("#define NIFLECTGENTAG_METHOD typedef void* " MACROTAG_METHOD ";");
		linesMacroTagDefine.push_back(R"(#define NIFLECTGENTAG_ENUMCONST __attribute__((annotate(")" MACROTAG_ENUMCONST R"("))))");

		Niflect::CString relativeFilePath = NiflectGenDefinition::NiflectFramework::FilePath::NiflectMacroHeader;
		std::ifstream ifs;
		for (auto& it : context.m_vecModuleHeaderSearchPath)
		{
			auto filePath = NiflectUtil::ConcatPath(it, relativeFilePath);
			if (NiflectUtil::OpenFileStream(ifs, filePath))
				break;
		}
		if (!ifs.is_open())
		{
			GenLogError(context.m_log, NiflectUtil::FormatString("Failed to open %s", relativeFilePath.c_str()));
			return;
		}

		CCodeTemplate tpl1;
		tpl1.ReadFromInputStream(ifs);
		CLabelToCodeMapping map;
		MapLabelToLines(map, "GenTimeReplacement", linesMacroTagDefine);
		Niflect::TSet<Niflect::CString> setReplacedLabel;
		CCodeLines linesHeader;
		tpl1.ReplaceLabels(map, linesHeader, &setReplacedLabel);

		CCppWriter writer;
		writer.WriteLines(linesHeader);
		auto outputFilePath = NiflectUtil::ConcatPath(context.m_genTimeBasePath, relativeFilePath);
		NiflectUtil::MakeDirectories(outputFilePath);
		NiflectUtil::WriteStringToFile(writer.m_code, outputFilePath);
	}
}