#include "NiflectGen/CodeWriter/ModuleReg/CreateTypeAccessorCodeWriter.h"
#include "NiflectGen/CodeWriter/HardCoded/CreateTypeAccessorTemplate.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"

namespace NiflectGen
{
    void WriteSplittedCreateTypeAccessorSpec(const SSplittedCreateTypeAccessorSpecWritingContext& context, CTypeRegCreateTypeAccessorSpecData& data)
    {
        auto splitsCount = context.m_vecItem.size();
        data.m_vecCreateTypeAccessorSpecData.resize(splitsCount);
        for (uint32 idx0 = 0; idx0 < splitsCount; ++idx0)
        {
            auto& it0 = context.m_vecItem[idx0];
            {
                auto& typeRegData = data.m_vecCreateTypeAccessorSpecData[idx0];
                Niflect::CString relativeTypeRegFilePathNoExt;
                if (it0.m_taggedTypeHeaderFilePathAddr != NULL)
                {
                    relativeTypeRegFilePathNoExt = CIncludesHelper::ConvertToIncludePath(*it0.m_taggedTypeHeaderFilePathAddr, context.m_moduleRegInfo.m_userProvided.m_writingHeaderSearchPaths.m_vecForRegularConversion);
                    relativeTypeRegFilePathNoExt = NiflectUtil::RemoveFileExt(relativeTypeRegFilePathNoExt);
                }
                else
                {
                    relativeTypeRegFilePathNoExt = NiflectUtil::FormatString("Misc_%u", idx0);
                }
                auto fileNameNoExt = NiflectUtil::GetFileName(relativeTypeRegFilePathNoExt);
                auto internalFileNameNoExt = "_" + fileNameNoExt;
                Niflect::CString dirPath;
                NiflectUtil::GetParentDirPathSafe(relativeTypeRegFilePathNoExt, dirPath);
                auto internalRelativeTypeRegFilePathNoExt = NiflectUtil::ConcatPath(dirPath, internalFileNameNoExt);
                auto typeRegSplittedFilePathNoExt = NiflectUtil::ConcatPath(context.m_moduleRegInfo.m_typeRegBasePath, internalRelativeTypeRegFilePathNoExt);
                typeRegData.m_implSourceFilePath = typeRegSplittedFilePathNoExt + NiflectGenDefinition::FileExt::Cpp;
                typeRegData.m_declHeaderFilePath = typeRegSplittedFilePathNoExt + NiflectGenDefinition::FileExt::H;

                CCodeLines linesH;
                CCodeLines linesCpp;
                for (auto& it1 : it0.m_vecTypeRegDataRef)
                {
                    for (auto& it2 : it1->m_registerTypeAndfieldLayout.m_linesCreateFieldLayoutOfTypeDecl)
                        linesH.push_back(it2);
                    for (auto& it2 : it1->m_registerTypeAndfieldLayout.m_linesCreateFieldLayoutOfTypeImpl)
                        linesCpp.push_back(it2);
                }
                {
                    CCodeTemplate tpl1;
                    tpl1.ReadFromRawData(HardCodedTemplate::FieldLayoutSpecH);
                    CLabelToCodeMapping map;
                    CCodeLines linesHInclude;
                    {
                        Niflect::TArrayNif<CHeaderFilePathData> vecHeaderData;
                        vecHeaderData.push_back(NiflectGenDefinition::NiflectFramework::FilePath::NiflectTypeHeader);//含 CreateTypeAccessor 的函数模板声明
                        for (auto& it1 : it0.m_vecTypeRegDataRef)
                        {
                            for (auto& it2 : it1->m_registerTypeAndfieldLayout.m_dependencyHeaderFilePathAddrs.m_vecDecl)
                                vecHeaderData.push_back(*it2);
                        }
                        CIncludesHelper::ConvertFromHeaderFilePaths(vecHeaderData, context.m_moduleRegInfo.m_userProvided.m_writingHeaderSearchPaths, linesHInclude);
                    }
                    MapLabelToLines(map, LABEL_4, linesHInclude);
                    MapLabelToLines(map, LABEL_6, linesH);
                    Niflect::TSet<Niflect::CString> setReplacedLabel;
                    tpl1.ReplaceLabels(map, typeRegData.m_decl, &setReplacedLabel);
                }
                {
                    CCodeTemplate tpl1;
                    tpl1.ReadFromRawData(HardCodedTemplate::FieldLayoutSpecCpp);
                    CLabelToCodeMapping map;

                    CCodeLines linesCppInclude;
                    {
                        Niflect::TArrayNif<CHeaderFilePathData> vecHeaderData;
                        vecHeaderData.push_back({ typeRegData.m_declHeaderFilePath, true });
                        for (auto& it1 : it0.m_vecTypeRegDataRef)
                        {
                            for (auto& it2 : it1->m_registerTypeAndfieldLayout.m_dependencyHeaderFilePathAddrs.m_vecImpl)
                                vecHeaderData.push_back(*it2);
                        }
                        CIncludesHelper::ConvertFromHeaderFilePaths(vecHeaderData, context.m_moduleRegInfo.m_userProvided.m_writingHeaderSearchPaths, linesCppInclude);
                        //linesCppInclude = linesFilePath;
                    }
                    MapLabelToLines(map, LABEL_4, linesCppInclude);
                    MapLabelToLines(map, LABEL_5, linesCpp);
                    Niflect::TSet<Niflect::CString> setReplacedLabel;
                    tpl1.ReplaceLabels(map, typeRegData.m_impl, &setReplacedLabel);
                }

                //printf("[%u]---------------------------------\n", idx0);
                //DebugPrintCodeLines(typeRegData.m_impl);
            }
        }
    }
}