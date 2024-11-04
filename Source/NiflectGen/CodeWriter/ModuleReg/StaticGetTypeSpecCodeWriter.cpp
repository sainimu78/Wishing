#include "NiflectGen/CodeWriter/ModuleReg/StaticGetTypeSpecCodeWriter.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/HardCoded/StaticGetTypeTemplate.h"

namespace NiflectGen
{
    static Niflect::CString removeNonAlphanumeric(const Niflect::CString& path) {
        auto result = path; // 创建一个副本以进行修改

        // 使用 std::remove_if 和 std::erase 方法删除非字母和数字字符
        result.erase(std::remove_if(result.begin(), result.end(),
            [](unsigned char c) {
                return !std::isalnum(c); // 检查字符是否为字母或数字
            }),
            result.end());

        return result; // 返回处理后的字符串
    }
    static Niflect::CString ConvertHeaderFilePathToGenHFileId(const Niflect::CString& filePath)
    {
        return removeNonAlphanumeric(filePath);
    }
    static Niflect::CString GenerateLineNumberMacroName(const char* hct, const Niflect::CString& fileId, uint32 lineNumber)
    {
        auto lineNumberInString = NiflectUtil::FormatString("%u", lineNumber);
        return ReplaceLabelToText2(hct, LABEL_4, LABEL_5, fileId, lineNumberInString);
    }
    static void GenerateLineNumberMacroDefinition(const char* hct, const Niflect::CString& macroName, const CCodeLines& linesBody, CCodeLines& linesDefinition)
    {
        CCodeTemplate tpl1;
        tpl1.ReadFromRawData(hct);
        CLabelToCodeMapping map;
        MapLabelToText(map, LABEL_7, macroName);
        MapLabelToLines(map, LABEL_8, linesBody);
        Niflect::TSet<Niflect::CString> setReplacedLabel;
        tpl1.ReplaceLabels(map, linesDefinition, &setReplacedLabel);
    }

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
                auto internalRelativeTypeRegFilePathNoExt = NiflectUtil::ConcatPath(context.m_moduleRegInfo.m_typeRegBasePath, ConvertToInternalFilePath(relativeTypeRegFilePathNoExt));
                staticGetTypeSpecData.m_implSourceFilePath = internalRelativeTypeRegFilePathNoExt + NiflectGenDefinition::FileNamePostfix::Gen + context.m_moduleRegInfo.GetSourceFileExtForGenFileMode();

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
                    Niflect::CString genHFileId = ConvertHeaderFilePathToGenHFileId(staticGetTypeSpecData.m_genHHeaderFilePath);
                    MapLabelToText(map, LABEL_4, genHFileId);

                    CCodeLines linesMacros;
                    {
                        for (auto& it1 : it0.m_vecTypeRegDataRef)
                        {
                            auto& lineNumber = it1->m_taggedTypeGeneratedBody.m_generatedBodyLineNumber;
                            if (lineNumber != INDEX_NONE)
                            {
                                CCodeLines linesItemsDefinition;
                                CCodeLines linesRootBody;
                                {
                                    auto macroNameItem0 = GenerateLineNumberMacroName(HardCodedTemplate::LineNumberMacroExposeToAccessor, genHFileId, lineNumber);
                                    linesRootBody.push_back(ReplaceLabelToText1(HardCodedTemplate::LineNumberMacroItem, LABEL_7, macroNameItem0));
                                    GenerateLineNumberMacroDefinition(HardCodedTemplate::LineNumberMacroDefinition, macroNameItem0, it1->m_taggedTypeGeneratedBody.m_linesMacroBodyExposeToAccessor, linesItemsDefinition);
                                }
                                CCodeLines linesRootDefinition;
                                {
                                    auto macroNameRoot = GenerateLineNumberMacroName(HardCodedTemplate::LineNumberMacroGeneratedBody, genHFileId, lineNumber);
                                    GenerateLineNumberMacroDefinition(HardCodedTemplate::LineNumberMacroDefinition, macroNameRoot, linesRootBody, linesRootDefinition);
                                }
                                {
                                    CCodeTemplate tpl1;
                                    tpl1.ReadFromRawData(HardCodedTemplate::LineNumberMacros);
                                    CLabelToCodeMapping map;
                                    MapLabelToLines(map, LABEL_9, linesItemsDefinition);
                                    MapLabelToLines(map, LABEL_10, linesRootDefinition);
                                    Niflect::TSet<Niflect::CString> setReplacedLabel;
                                    tpl1.ReplaceLabels(map, linesMacros, &setReplacedLabel);
                                }
                            }
                        }
                    }
                    MapLabelToLines(map, LABEL_6, linesMacros);

                    Niflect::TSet<Niflect::CString> setReplacedLabel;
                    tpl1.ReplaceLabels(map, staticGetTypeSpecData.m_genH, &setReplacedLabel);
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