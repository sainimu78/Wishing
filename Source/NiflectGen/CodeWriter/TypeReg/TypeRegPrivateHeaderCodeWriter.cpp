#include "NiflectGen/CodeWriter/TypeReg/TypeRegPrivateHeaderCodeWriter.h"
#include "NiflectGen/CodeWriter/HardCoded/TypeRegPrivateHeaderTemplate.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/CppWriter.h"

namespace NiflectGen
{
	void WriteTypeRegsPrivateHeader(const CWritingContext& context, const STypeRegPrivateHeaderWritingContext& genCtx, STypeRegPrivateHeaderWritingData& data)
	{
		//todo: 收集同namespace, 同global的class定义

		CNoDupPathCollector includesNoDup;
		CCodeLines linesRegClasses;
		for (auto& it0 : genCtx.m_vecWritingData)
		{
			for (auto& it1 : it0->m_linesRegClass)
				linesRegClasses.push_back(it1);
			for (auto& it1 : it0->m_privateHeaderincludePath.m_vecPath)
				includesNoDup.Add(it1);
		}
		CCodeLines linesIncludes;
		CIncludesHelper::Write(includesNoDup, linesIncludes);

		{
			CCodeTemplate tpl;
			tpl.ReadFromRawData(HardCodedTemplate::TypeRegPrivateH);
			CLabelToCodeMapping map;
			MapLabelToLines(map, LABEL_0, linesIncludes);
			MapLabelToLines(map, LABEL_1, linesRegClasses);
			tpl.ReplaceLabels(map, data.m_privateH);
		}
	}
}