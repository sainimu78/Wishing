#include "NiflectGen/CodeWriter/ModuleReg/SplittedModuleRegCodeWriter2.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/HardCoded/SplittedModuleRegTemplate.h"
#include "NiflectGen/CodeWriter/CppWriter.h"

namespace NiflectGen
{
    void WriteSplittedFieldLayoutSpec(const SSplittedFieldLayoutSpecWritingContext& context, SSplittedFieldLayoutSpecWritingData& data)
    {
        auto& typeRegModuleDirPath = context.m_moduleRegInfo.m_typeRegBasePath;
        //auto typeRegFieldLayoutDirPath = NiflectUtil::ConcatPath(typeRegModuleDirPath, "FieldLayout");
        auto& typeRegFieldLayoutDirPath = typeRegModuleDirPath;
        auto splitsCount = context.m_vecItem.size();
        data.m_vecFieldLayoutSpecData.resize(splitsCount);
        for (uint32 idx0 = 0; idx0 < splitsCount; ++idx0)
        {
            auto& it0 = context.m_vecItem[idx0];
            {
                auto& typeRegData = data.m_vecFieldLayoutSpecData[idx0];
                Niflect::CString relativeTypeRegFilePathNoExt;
                if (it0.m_taggedTypeHeaderFilePathRef != NULL)
                {
                    relativeTypeRegFilePathNoExt = CIncludesHelper::ConvertToIncludePath(*it0.m_taggedTypeHeaderFilePathRef, context.m_moduleRegInfo.m_userProvided.m_vecHeaderSearchPath);
                    relativeTypeRegFilePathNoExt = NiflectUtil::RemoveFileExt(relativeTypeRegFilePathNoExt);
                }
                else
                {
                    relativeTypeRegFilePathNoExt = NiflectUtil::FormatString("Misc_%u", idx0);
                }
                auto typeRegSplittedFilePathNoExt = NiflectUtil::ConcatPath(typeRegFieldLayoutDirPath, relativeTypeRegFilePathNoExt);
                typeRegData.m_implIncludePath = typeRegSplittedFilePathNoExt + NiflectGenDefinition::FileExt::PrivateH;
                typeRegData.m_declIncludePath = typeRegSplittedFilePathNoExt + NiflectGenDefinition::FileExt::GenH;

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
                    for (auto& it1 : it0.m_vecTypeRegDataRef)
                    {
                        for (auto& it2 : it1->m_registerTypeAndfieldLayout.m_dependencyHeaderFilePathRefs.m_vecDecl)
                            linesHInclude.push_back(*it2);
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
                    linesCppInclude.push_back(typeRegData.m_declIncludePath);
                    for (auto& it1 : it0.m_vecTypeRegDataRef)
                    {
                        for (auto& it2 : it1->m_registerTypeAndfieldLayout.m_dependencyHeaderFilePathRefs.m_vecImpl)
                            linesCppInclude.push_back(*it2);
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
    void WriteSplittedModuleRegs3(const SSplittedModuleRegWritingContext2& context, SSplittedModuleRegWritingData2& data)
    {
        auto splittedModuleRegDirPath = NiflectUtil::ConcatPath(context.m_moduleRegInfo.m_moduleRegBasePath, "Splitted");
        auto splitsCount = context.m_vecItem.size();
        data.m_vecSplittedModuleRegGenData.resize(splitsCount);
        data.m_vecSplittedModuleRegFuncsName.resize(splitsCount);
        for (uint32 idx0 = 0; idx0 < splitsCount; ++idx0)
        {
            auto& it0 = context.m_vecItem[idx0];

            {
                auto& splittedRegData = data.m_vecSplittedModuleRegGenData[idx0];

                {
                    auto fileName = NiflectUtil::FormatString("_%s_%u%s", context.m_moduleRegInfo.m_userProvided.m_moduleName.c_str(), idx0, NiflectGenDefinition::FileExt::H);
                    splittedRegData.m_includePath = NiflectUtil::ConcatPath(splittedModuleRegDirPath, fileName);
                }

                CCodeLines linesInvokeInitTypes;
                for (auto& it1 : it0.m_vecTypeRegDataRef)
                {
                    if (it1->m_taggedTypeInit.m_lines.size() > 0)
                    {
                        CCodeTemplate tpl1;
                        tpl1.ReadFromRawData(HardCodedTemplate::ImplScope);
                        CLabelToCodeMapping map;
                        MapLabelToLines(map, LABEL_3, it1->m_taggedTypeInit.m_lines);
                        Niflect::TSet<Niflect::CString> setReplacedLabel;
                        tpl1.ReplaceLabels(map, linesInvokeInitTypes, &setReplacedLabel);
                    }
                }

                Niflect::CString registerTypesFuncName;
                Niflect::CString initTypesFuncName;
                {
                    auto strIdx = NiflectUtil::FormatString("%u", idx0);
                    {
                        registerTypesFuncName = ReplaceLabelToText2(HardCodedTemplate::RegisterTypesFuncName, LABEL_0, LABEL_1, context.m_moduleRegInfo.m_userProvided.m_moduleName, strIdx);
                        auto funcSignature = ReplaceLabelToText1(HardCodedTemplate::FuncDecl, LABEL_2, registerTypesFuncName);
                        splittedRegData.m_h.push_back(funcSignature);
                    }
                    if (linesInvokeInitTypes.size() > 0)
                    {
                        initTypesFuncName = ReplaceLabelToText2(HardCodedTemplate::InitTypesFuncName, LABEL_0, LABEL_1, context.m_moduleRegInfo.m_userProvided.m_moduleName, strIdx);
                        auto funcSignature = ReplaceLabelToText1(HardCodedTemplate::FuncDecl, LABEL_2, initTypesFuncName);
                        splittedRegData.m_h.push_back(funcSignature);
                    }
                }
                {
                    CCodeLines linesImpl;
                    {
                        CCodeTemplate tpl1;
                        tpl1.ReadFromRawData(HardCodedTemplate::FuncImpl);
                        CLabelToCodeMapping map;
                        MapLabelToText(map, LABEL_2, registerTypesFuncName);
                        CCodeLines linesInvoke;
                        for (auto& it1 : it0.m_vecTypeRegDataRef)
                        {
                            for (auto& it2 : it1->m_registerTypeAndfieldLayout.m_linesInvokeRegisterType)
                                linesInvoke.push_back(it2);
                        }
                        MapLabelToLines(map, LABEL_3, linesInvoke);
                        Niflect::TSet<Niflect::CString> setReplacedLabel;
                        tpl1.ReplaceLabels(map, linesImpl, &setReplacedLabel);
                    }
                    if (linesInvokeInitTypes.size() > 0)
                    {
                        CCodeTemplate tpl1;
                        tpl1.ReadFromRawData(HardCodedTemplate::FuncImpl);
                        CLabelToCodeMapping map;
                        MapLabelToText(map, LABEL_2, initTypesFuncName);
                        MapLabelToLines(map, LABEL_3, linesInvokeInitTypes);
                        Niflect::TSet<Niflect::CString> setReplacedLabel;
                        tpl1.ReplaceLabels(map, linesImpl, &setReplacedLabel);
                    }
                    {
                        CCodeTemplate tpl1;
                        tpl1.ReadFromRawData(HardCodedTemplate::SplittedModuleRegCpp);
                        CLabelToCodeMapping map;
                        CCodeLines linesInclude;
                        auto& fieldLayoutSpecData = context.m_vecFieldLayoutSpecData[idx0];
                        linesInclude.push_back(splittedRegData.m_includePath);
                        linesInclude.push_back(fieldLayoutSpecData.m_declIncludePath);
                        MapLabelToLines(map, LABEL_4, linesInclude);
                        MapLabelToLines(map, LABEL_5, linesImpl);
                        Niflect::TSet<Niflect::CString> setReplacedLabel;
                        tpl1.ReplaceLabels(map, splittedRegData.m_cpp, &setReplacedLabel);
                    }
                }
                auto& funcsName = data.m_vecSplittedModuleRegFuncsName[idx0];
                funcsName.m_registerTypes = registerTypesFuncName;
                if (linesInvokeInitTypes.size() > 0)
                    funcsName.m_initTypes = initTypesFuncName;
            }
        }
    }
}