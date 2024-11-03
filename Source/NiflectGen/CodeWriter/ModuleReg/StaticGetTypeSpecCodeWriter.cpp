#include "NiflectGen/CodeWriter/ModuleReg/StaticGetTypeSpecCodeWriter.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/HardCoded/StaticGetTypeTemplate.h"

namespace NiflectGen
{
    void WriteSplittedStaticGetTypeSpec(const SSplittedCreateTypeAccessorSpecWritingContext& context, CTypeRegStaticGetTypeSpecData& data)
    {
        auto splitsCount = context.m_vecItem.size();
        data.m_vecStaticGetTypeSpecData.resize(splitsCount);
        for (uint32 idx0 = 0; idx0 < splitsCount; ++idx0)
        {
            auto& it0 = context.m_vecItem[idx0];
            if (it0.m_taggedTypeHeaderFilePathAddr != NULL)
            {
                auto relativeTypeRegFilePathNoExt = CIncludesHelper::ConvertToIncludePath(*it0.m_taggedTypeHeaderFilePathAddr, context.m_moduleRegInfo.m_userProvided.m_writingHeaderSearchPaths.m_vecForRegularConversion);
                relativeTypeRegFilePathNoExt = NiflectUtil::RemoveFileExt(relativeTypeRegFilePathNoExt);
                auto& staticGetTypeSpecData = data.m_vecStaticGetTypeSpecData[idx0];
                auto typeRegSplittedFilePathNoExt = NiflectUtil::ConcatPath(context.m_moduleRegInfo.m_genHBasePath, relativeTypeRegFilePathNoExt);
                staticGetTypeSpecData.m_genHHeaderFilePath = typeRegSplittedFilePathNoExt + NiflectGenDefinition::FileExt::GenH;
                staticGetTypeSpecData.m_implSourceFilePath = typeRegSplittedFilePathNoExt + NiflectGenDefinition::FileExt::GenCpp;

                {
                    CCodeLines linesGenHInclude;
                    CHeaderFilePathDataArray vecHeaderData;
                    ASSERT(!context.m_moduleRegInfo.m_userProvided.m_moduleApiMacroHeader.empty());
                    vecHeaderData.push_back(NiflectGenDefinition::NiflectFramework::FilePath::NiflectTypeHeader);
                    vecHeaderData.push_back(context.m_moduleRegInfo.m_userProvided.m_moduleApiMacroHeader);
                    CIncludesHelper::ConvertFromHeaderFilePaths(vecHeaderData, context.m_moduleRegInfo.m_userProvided.m_writingHeaderSearchPaths, linesGenHInclude);

                    CCodeTemplate tpl1;
                    tpl1.ReadFromRawData(HardCodedTemplate::GenH);
                    CLabelToCodeMapping map;
                    MapLabelToLines(map, LABEL_0, linesGenHInclude);
                    CCodeLines linesTypeDecls;
                    {
                        for (auto& it1 : it0.m_vecTypeRegDataRef)
                        {
                            for (auto& it2 : it1->m_taggedTypeGeneratedBody.m_linesFullScopedTypeDecl)
                                linesTypeDecls.push_back(it2);
                        }
                    }
                    MapLabelToLines(map, LABEL_1, linesTypeDecls);
                    CCodeLines linesStaticGetTypeSpecDecl;
                    for (auto& it1 : it0.m_vecTypeRegDataRef)
                    {
                        for (auto& it2 : it1->m_taggedTypeGeneratedBody.m_linesStaticGetTypeSpecDecl)
                            linesStaticGetTypeSpecDecl.push_back(it2);
                    }
                    MapLabelToLines(map, LABEL_2, linesStaticGetTypeSpecDecl);
                    Niflect::TSet<Niflect::CString> setReplacedLabel;
                    tpl1.ReplaceLabels(map, staticGetTypeSpecData.m_genH, &setReplacedLabel);

                    CCodeLines linesGenH;
                }
                {
                    CCodeLines linesGenCppInclude;
                    CHeaderFilePathDataArray vecHeaderData;
                    ASSERT(!context.m_moduleRegInfo.m_userProvided.m_moduleApiMacroHeader.empty());
                    vecHeaderData.push_back(staticGetTypeSpecData.m_genHHeaderFilePath);
                    CIncludesHelper::ConvertFromHeaderFilePaths(vecHeaderData, context.m_moduleRegInfo.m_userProvided.m_writingHeaderSearchPaths, linesGenCppInclude);

                    CCodeTemplate tpl1;
                    tpl1.ReadFromRawData(HardCodedTemplate::GenCpp);
                    CLabelToCodeMapping map;
                    MapLabelToLines(map, LABEL_0, linesGenCppInclude);
                    CCodeLines linesImpl;
                    for (auto& it1 : it0.m_vecTypeRegDataRef)
                    {
                        for (auto& it2 : it1->m_taggedTypeGeneratedBody.m_linesStaticGetTypeSpecImpl)
                            linesImpl.push_back(it2);
                    }
                    MapLabelToLines(map, LABEL_3, linesImpl);
                    Niflect::TSet<Niflect::CString> setReplacedLabel;
                    tpl1.ReplaceLabels(map, staticGetTypeSpecData.m_impl, &setReplacedLabel);
                }
            }
        }
    }
}