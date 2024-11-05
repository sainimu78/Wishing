#include "NiflectGen/Generator/BypassSource.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"

namespace NiflectGen
{
	void GenerateSTLBypassMemSource(CMemSourceReferenceCache& cache)
	{
		auto& memSrc = cache.AddTempMemSrc();
		memSrc.m_filePath = "F:/Fts/Proj/Test/Interedit/Source/memSrcMyNihao.h";

        CCodeLines lines;
        constexpr const char* hct =
R"(#pragma once

class CMyNihaoInMemSrc
{
public:
    float m_a;
};)";

        CCodeTemplate tpl1;
        tpl1.ReadFromRawData(hct);
        CLabelToCodeMapping map;
        //MapLabelToLines(map, LABEL_0, linesGenCppInclude);
        //CCodeLines linesImpl;
        //for (auto& it1 : it0.m_vecTypeRegDataRef)
        //{
        //    for (auto& it2 : it1->m_taggedTypeGeneratedBody.m_linesStaticGetTypeSpecImpl)
        //        linesImpl.push_back(it2);
        //}
        //MapLabelToLines(map, LABEL_3, linesImpl);
        Niflect::TSet<Niflect::CString> setReplacedLabel;
        tpl1.ReplaceLabels(map, lines, &setReplacedLabel);

        CCppWriterRef writer(memSrc.m_data);
        writer.WriteLines(lines);

        cache.AddMemSrcRef(memSrc);
	}
}