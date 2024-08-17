#include "NiflectGen/Generator/Generator.h"
#include "NiflectGen/Util/CompilerUtil.h"
#include "clang-c/Index.h"
#include "NiflectGen/Generator/CursorNode.h"
#include <iostream>
#include "NiflectGen/Util/CursorUtil.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "Niflect/Util/StringUtil.h"
#include "NiflectGen/Collector/Collector.h"
#include "NiflectGen/Log/Log.h"
#include "Niflect/Util/DebugUtil.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/CodeWriter/ModuleReg/ModuleRegCodeWriter.h"
#include "NiflectGen/Resolver/Resolver.h"

//#include <fstream>//std::getline
//#include <stack>

namespace NiflectGen
{
    using namespace Niflect;

    Niflect::TSharedPtr<CGenerator> CreateGenerator()
    {
        return MakeShared<CGenerator>();
    }

    //void CModuleReg::Validate()
    //{
    //    m_moduleRegPath = "";
    //}

    CGenerator::CGenerator()
        : m_collectorHolder(MakeShared<CDataCollector>())
        , m_collector(*m_collectorHolder)
        , m_genDataHolder(MakeShared<CCodeGenData>())
        , m_genData(*m_genDataHolder)
    {
    }
    void CGenerator::AddTypeBindingSettingHeader(const Niflect::CString& filePath)
    {
        ASSERT(NiflectGenDefinition::FileExt::IsH(filePath));
        m_vecTypeBindingSettingFilePath.push_back(filePath);
    }
    void CGenerator::PrepareSourceFiles()
    {
        m_tempSource.m_filePath = "TempSource.cpp";

        CSimpleCppWriter writer(m_tempSource.m_data);
        writer.AddHeaderFirstLine();
        for (auto& it : m_vecTypeBindingSettingFilePath)
            writer.AddInclude(it);
        for (auto& it : m_vecFileForSearchingH)
            writer.AddInclude(it);
    }
    void CGenerator::GetUnsavedSourceFiles(Niflect::TArrayNif<CXUnsavedFile>& vecUnsavedFileHandle)
    {
        vecUnsavedFileHandle.resize(1);

        m_tempSource.FillData(&vecUnsavedFileHandle.back());
    }
    static void AddSourceFile(const CString& filePath, TArrayNif<CString>& vecCpp, TArrayNif<CString>& vecH)
    {
        if (NiflectGenDefinition::FileExt::IsCpp(filePath))
        {
            ASSERT(false);//todo: 未实现.cpp文件中使用反射标记
            vecCpp.push_back(filePath);
        }
        else
        {
            vecH.push_back(filePath);
        }
    }
    void CGenerator::AddFileForSearching(const CString& filePath)
    {
        AddSourceFile(filePath, m_vecFileForSearchingCpp, m_vecFileForSearchingH);
    }
    void CGenerator::AddIncludePath(const Niflect::CString& dirPath)
    {
        m_vecHeaderSearchPath.push_back(dirPath);
    }
    void CGenerator::ParseSourceFiles()
    {
        this->PrepareSourceFiles();
        Niflect::TArrayNif<CXUnsavedFile> vecUnsavedFileHandle;
        this->GetUnsavedSourceFiles(vecUnsavedFileHandle);

        CCompilerOption opt;
        opt.InitDefault();
        opt.AddIncludePaths(m_vecHeaderSearchPath);

        bool displayDiagnostics = true;
        auto index = clang_createIndex(true, displayDiagnostics);

        auto translation_unit = clang_parseTranslationUnit(index, m_tempSource.m_filePath.c_str(), opt.GetArgV(), 
            opt.GetArgC(), vecUnsavedFileHandle.data(), 
            static_cast<uint32>(vecUnsavedFileHandle.size()), CXTranslationUnit_DetailedPreprocessingRecord | CXTranslationUnit_SkipFunctionBodies
        );

        if (false)//if (true)//
        {
            auto cursor = clang_getTranslationUnitCursor(translation_unit);
#pragma warning( disable : 4996 )
            FILE* fp = fopen("E:/a.txt", "w");
#pragma warning( default : 4996 )
            int level = 0;
            CVisitCallbacks callbacks;
            callbacks.m_EnterFunc = [&fp, &level](const CXCursor& cursor)
                {
                    DebugPrintCursor(fp, cursor, level);
                    level++;
                };
            callbacks.m_LeaveFunc = [&level](const CXCursor& cursor)
                {
                    level--;
                };
            VisitCursorRecurs(cursor, callbacks);
            fclose(fp);
            printf("");
        }

        if (true)//if (false)//
        {
            auto cursor = clang_getTranslationUnitCursor(translation_unit);
            CTaggedNode2 taggedRoot;
#pragma warning( disable : 4996 )
            FILE* fp = fopen("E:/b.txt", "w");
#pragma warning( default : 4996 )
            CGenLog log;
            CCollectingContext context(&log);
            CVisitingDebugData debugData;
            debugData.Init(cursor, fp);
            context.m_debugData = &debugData;
            CCollectionData collectionData;
            m_collector.Collect(cursor, &taggedRoot, context, collectionData);
            //if (false)
            //{
            //    for (auto& it : collectionData.m_vecBindingSetting)
            //    {
            //        PrintTemplateSubcursor333333333(it.m_subCursorRoot, 0);
            //        ASSERT(it.m_subCursorRoot.m_vecChild.size() == 2);
            //        printf("---------\n");
            //    }
            //}
            if (true)
            {
                CResolvingContext resolvingContext(&log);
                CResolver resolver(collectionData, m_vecHeaderSearchPath);
                CResolvedData resolvedData;
                resolver.Resolve2(&taggedRoot, resolvingContext, resolvedData);
                //resolver.DebugFinish(resolvedData);
                CTemplateBasedCppWriter writer(resolvedData, CModuleRegInfoValidated(CModuleRegInfo()));
                CWritingContext writingContext(&log);
                CCodeGenData genData;
                writer.Write2(writingContext, genData);
                printf("");
            }
            if (false)
            {
                TArrayNif<CTaggedType*> vecOrderedNode;
                SortTaggedNodesInDependencyOrder(&taggedRoot, vecOrderedNode);
                for (auto& it : vecOrderedNode)
                {
                    auto& cursor = it->GetCursor();
                    auto strName = CXStringToCString(clang_getCursorSpelling(cursor));
                    auto type = clang_getCursorType(cursor);
                    auto strType = CXStringToCString(clang_getTypeSpelling(type));
                    printf("%s\n", strName.c_str());
                }
            }
            debugData.Check();
            m_collector.DebugFinish2(&taggedRoot, collectionData);
            fclose(fp);
            printf("");
        }


        if (translation_unit)
            clang_disposeTranslationUnit(translation_unit);

        if (index)
            clang_disposeIndex(index);
    }
    void CGenerator::SetModuleRegInfo(const CModuleRegInfo& moduleRegInfo)
    {
        m_moduleRegInfo = moduleRegInfo;
    }
    void CGenerator::Generate()
    {
        //#1, Cleanup & Prepare
        CModuleRegInfoValidated validatedModuleRegInfo(m_moduleRegInfo);
        //todo: 路径有效性检查, 重复路径剔除等
        const auto& userProvided = validatedModuleRegInfo.m_userProvided;
        validatedModuleRegInfo.m_moduleRegBasePath = NiflectUtil::ConcatPath(userProvided.m_genIncludeBasePath, userProvided.m_moduleName);

        //预留清理module, 从module输出目录中的缓存可获取生成的所有文件

        m_tempSource.m_filePath = "TempSource.cpp";
        CSimpleCppWriter writer(m_tempSource.m_data);
        writer.AddHeaderFirstLine();
        for (auto& it1 : userProvided.m_vecBindingSettingHeader)
            writer.AddInclude(it1);
        for (auto& it1 : userProvided.m_vecOriginalHeader)
            writer.AddInclude(it1);

        CCompilerOption opt;
        opt.InitDefault();
        opt.AddIncludePaths(userProvided.m_vecHeaderSearchPath);

        //#2, Parse headers
        Niflect::TArrayNif<CXUnsavedFile> vecUnsavedFileHandle;
        this->GetUnsavedSourceFiles(vecUnsavedFileHandle);

        const bool displayDiagnostics = true;
        auto index = clang_createIndex(true, displayDiagnostics);

        auto translation_unit = clang_parseTranslationUnit(index, m_tempSource.m_filePath.c_str(), opt.GetArgV(),
            opt.GetArgC(), vecUnsavedFileHandle.data(),
            static_cast<uint32>(vecUnsavedFileHandle.size()), CXTranslationUnit_DetailedPreprocessingRecord | CXTranslationUnit_SkipFunctionBodies
        );

        if (false)//if (true)//
        {
            auto cursor = clang_getTranslationUnitCursor(translation_unit);
#pragma warning( disable : 4996 )
            FILE* fp = fopen("E:/a.txt", "w");
#pragma warning( default : 4996 )
            int level = 0;
            CVisitCallbacks callbacks;
            callbacks.m_EnterFunc = [&fp, &level](const CXCursor& cursor)
                {
                    DebugPrintCursor(fp, cursor, level);
                    level++;
                };
            callbacks.m_LeaveFunc = [&level](const CXCursor& cursor)
                {
                    level--;
                };
            VisitCursorRecurs(cursor, callbacks);
            fclose(fp);
            printf("");
        }

        if (true)//if (false)//
        {
            auto cursor = clang_getTranslationUnitCursor(translation_unit);
            CTaggedNode2 taggedRoot;
#pragma warning( disable : 4996 )
            FILE* fp = fopen("E:/b.txt", "w");
#pragma warning( default : 4996 )
            CGenLog log;
            CCollectingContext context(&log);
            CVisitingDebugData debugData;
            debugData.Init(cursor, fp);
            context.m_debugData = &debugData;
            CCollectionData collectionData;
            m_collector.Collect(cursor, &taggedRoot, context, collectionData);
            if (true)
            {
                CResolvingContext resolvingContext(&log);
                CResolver resolver(collectionData, m_vecHeaderSearchPath);
                CResolvedData resolvedData;
                resolver.Resolve2(&taggedRoot, resolvingContext, resolvedData);

                //#3, Generate code
                CTemplateBasedCppWriter writer(resolvedData, validatedModuleRegInfo);
                CWritingContext writingContext(&log);
                writer.Write2(writingContext, m_genData);
            }
            debugData.Check();
            m_collector.DebugFinish2(&taggedRoot, collectionData);
            fclose(fp);
        }

        if (translation_unit)
            clang_disposeTranslationUnit(translation_unit);

        if (index)
            clang_disposeIndex(index);
    }
    void CGenerator::Save() const
    {
        //#4, Save to files
        auto a = m_genData.m_moduleRegGenData.m_privateHIncludePath;
        printf("");
    }

    CXChildVisitResult visitAST(CXCursor cursor, CXCursor parent, CXClientData data)
    {
        if (clang_getCursorKind(cursor) == CXCursor_MacroExpansion)
        {
            std::cout << "Macro: " << clang_getCString(clang_getCursorSpelling(cursor)) << std::endl;
            CXTranslationUnit unit = clang_Cursor_getTranslationUnit(cursor);
            CXSourceRange range = clang_getCursorExtent(cursor);
            CXToken* tokens = nullptr;
            unsigned int nTokens = 0;
            clang_tokenize(unit, range, &tokens, &nTokens);
            if (nTokens > 0)
            {
                for (unsigned int i = 1; i < nTokens; ++i)
                {
                    CXToken token = tokens[i];
                    CXString spelling = clang_getTokenSpelling(unit, token);
                    std::string param = clang_getCString(spelling);
                    std::cout << "Argument: " << param << std::endl;
                    clang_disposeString(spelling);
                }
            }
            if (tokens)
                clang_disposeTokens(unit, tokens, nTokens);

            //CXSourceRange range = clang_getCursorExtent(cursor);
            //CXString source_text = clang_getRangeText(clang_Cursor_getTranslationUnit(cursor), range);
            //std::string param = clang_getCString(source_text);
            //param = param.substr(param.find_first_of('(') + 1);
            //param = param.substr(0, param.find_last_of(')'));
            //std::cout << "Arguments: " << param << std::endl;
            //clang_disposeString(source_text);
        }
        return CXChildVisit_Continue;
    }
	void InitTypeBindingTable()
	{
        //auto debugSettingCppFilePath = CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Test/TestTypeBindingSetting.cpp");
        //auto debugSettingCppFilePath = CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Test/TestTypesHeaderForGen0.h");
        auto debugSettingCppFilePath = CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/Generated/NiflectGenerated/SampleTest/TempHeader.h");
        //auto debugSettingCppFilePath = CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/Generated/NiflectGenerated/SampleTest/TempSource.cpp");
        //auto debugSettingCppFilePath = CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client/ReflectionSystemDemo/Test/TestTypeBindingSetting.h");
        CCompilerOption opt;
        opt.InitDefault();
        Niflect::TArrayNif<Niflect::CString> vecIncludePath;
        vecIncludePath.push_back(CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/S3Engine"));
        //todo: 现代码未合并到引擎, 因此暂使用SampleTest的路径, 合并后可移除
        vecIncludePath.push_back(CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/SampleTest/SampleGamePrototyping/Cos/Client"));
        //deprecated: 解析头文件要求依赖生成.gen.h, 如果无法避免依赖.h, 则需要生成该.h
        //发现未指定为c++编译, 指定后则无报错
        vecIncludePath.push_back(CONCAT_CONST_CHAR_2(DEVELOPMENT_ROOT_SOURCE_PATH, "/Generated"));
        opt.AddIncludePaths(vecIncludePath);

        bool displayDiagnostics = true;
        auto index = clang_createIndex(true, displayDiagnostics);

        auto filePath = debugSettingCppFilePath;

        auto translation_unit = clang_createTranslationUnitFromSourceFile(
            index, filePath, opt.GetArgC(), opt.GetArgV(), 0, NULL
        );

        if (false)//获取宏展开与参数
        {
            CXCursor cursor = clang_getTranslationUnitCursor(translation_unit);
            clang_visitChildren(cursor, visitAST, nullptr);
        }

        if (false)
        {
            auto cursor = clang_getTranslationUnitCursor(translation_unit);
            CCursorTree cursorTree;
            cursorTree.BuildFromRoot(cursor);
#pragma warning( disable : 4996 )
            FILE* fp = fopen("E:/a.txt", "w");
            CCursorTree::DebugStaticPrintNodeRecurs(fp, &cursorTree.m_root);
            fclose(fp);
#pragma warning( default : 4996 )
        }

        if (false)
        {
            auto cursor = clang_getTranslationUnitCursor(translation_unit);
#pragma warning( disable : 4996 )
            FILE* fp = fopen("E:/a.txt", "w");
            CCursorTree::StaticPrintCursorRecurs(fp, cursor);
            fclose(fp);
#pragma warning( default : 4996 )
        }

        if (true)
        {
            auto cursor = clang_getTranslationUnitCursor(translation_unit);
#pragma warning( disable : 4996 )
            FILE* fp = fopen("E:/a.txt", "w");
#pragma warning( default : 4996 )
            CVisitCallbacks callbacks;
            int level = 0;
            callbacks.m_EnterFunc = [&fp, &level](const CXCursor& handle)
                {
                    DebugPrintCursor(fp, handle, level);
                    level++;
                };
            callbacks.m_LeaveFunc = [&level](const CXCursor& handle)
                {
                    level--;
                };
            VisitCursorRecurs(cursor, callbacks);
            fclose(fp);
        }

        if (translation_unit)
            clang_disposeTranslationUnit(translation_unit);

        if (index)
            clang_disposeIndex(index);
	}


    //class CNiceCoder : public Niflect::TArrayNif<Niflect::CString>
    //{
    //public:
    //    CNiceCoder();
    //    void Add(const Niflect::CString& t);
    //    //template <typename ...TArgs>
    //    //inline void Add(const QString& fmt, TArgs&& ...args)
    //    //{
    //    //	this->Add(QString(fmt).arg(args...));//需要参数都为QString, 不够方便
    //    //}
    //    template <typename T1>
    //    void Add(const Niflect::CString& fmt, const T1& v1)
    //    {
    //        this->Add(QString(fmt).arg(v1));
    //    }
    //    template <typename T1, typename T2>
    //    inline void Add(const Niflect::CString& fmt, const T1& v1, const T2& v2)
    //    {
    //        this->Add(QString(fmt).arg(v1).arg(v2));
    //    }
    //    template <typename T1, typename T2, typename T3>
    //    inline void Add(const Niflect::CString& fmt, const T1& v1, const T2& v2, const T3& v3)
    //    {
    //        this->Add(QString(fmt).arg(v1).arg(v2).arg(v3));
    //    }
    //    template <typename T1, typename T2, typename T3, typename T4>
    //    inline void Add(const Niflect::CString& fmt, const T1& v1, const T2& v2, const T3& v3, const T4& v4)
    //    {
    //        this->Add(QString(fmt).arg(v1).arg(v2).arg(v3).arg(v4));
    //    }
    //    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    //    inline void Add(const Niflect::CString& fmt, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5)
    //    {
    //        this->Add(QString(fmt).arg(v1).arg(v2).arg(v3).arg(v4).arg(v5));
    //    }
    //    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    //    inline void Add(const Niflect::CString& fmt, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6)
    //    {
    //        this->Add(QString(fmt).arg(v1).arg(v2).arg(v3).arg(v4).arg(v5).arg(v6));
    //    }
    //    void AddLines(const QStringList& qlst, QString qstrPrefix, QString qstrPostfix, bool bLastWithPostfix);
    //    void AddFunctionInputArgumentLines(const QStringList& qlst);
    //    void AddFunctionOutputArgumentLines(const QStringList& qlst);
    //    void AddFunctionBodyLines(const QStringList& qlst);
    //    void AddLines(const QStringList& qlst);
    //    void AddChunk(const QStringList& qlst);
    //    void BeginSemicolonBlock();
    //    void BeginBlock(bool hasSemicolon = false);
    //    void EndBlock();
    //    void AddEmptyLine();
    //    void SetLevel(int lv);
    //    int GetLevel() const;
    //    void EnterLevel();
    //    void LeaveLevel();

    //protected:
    //    virtual void InternalAdd(const QString& t);
    //    QString GetIndents() const;

    //protected:
    //    QString m_qstrIndent;
    //    //QString m_qstrEndOfLine;
    //    QString m_qstrBeginBlock;
    //    QString m_qstrEndBlock;
    //    std::stack<QString> m_stkEndBlock;
    //    QString m_qstrNewLine;
    //    int m_level;
    //};

    //struct SShaderTemplateLabelInfo
    //{
    //    int m_numOfIndents;
    //    size_t m_indexOfSection;
    //};
    //class CShaderTemplater {
    //public:
    //    void Read(const std::string& fileName) {
    //        std::ifstream file(fileName);
    //        if (!file.is_open())
    //            return;

    //        m_Context.clear();
    //        m_LabelInfo.clear();

    //        std::string line;
    //        bool isNewSection = false;
    //        while (std::getline(file, line)) {
    //            if (!line.empty()) {
    //                std::string trimmedLine = Trim(line);
    //                size_t prefixPos = trimmedLine.find(m_labelPrefix);
    //                if (prefixPos != std::string::npos) {
    //                    size_t postfixPos = trimmedLine.find(m_labelPostfix, prefixPos + m_labelPrefix.length());
    //                    if (postfixPos != std::string::npos) {
    //                        int cntTab = CountTabs(line);
    //                        m_LabelInfo.push_back(SShaderTemplateLabelInfo{ cntTab, m_Context.size() });
    //                        m_Context.emplace_back();
    //                        m_Context.back().push_back(trimmedLine.substr(prefixPos + m_labelPrefix.length(), postfixPos - (prefixPos + m_labelPrefix.length())));
    //                        isNewSection = true;
    //                        continue;
    //                    }
    //                }
    //            }
    //            if (m_Context.empty() || isNewSection) {
    //                m_Context.emplace_back();
    //                isNewSection = false;
    //            }
    //            m_Context.back().push_back(line);
    //        }
    //    }

    //    void ReplaceLabels(const std::map<std::string, std::vector<std::string>*>& mapLabelAndChunk, CNiceCoder& coder) const {
    //        size_t replacedLabelIndex = 0;
    //        for (size_t idx = 0; idx < m_Context.size(); ++idx) {
    //            const std::vector<std::string>& section = m_Context[idx];
    //            if (!m_LabelInfo.empty() && replacedLabelIndex < m_LabelInfo.size() && m_LabelInfo[replacedLabelIndex].m_indexOfSection == idx) {
    //                const std::string& label = section.front();
    //                assert(!label.empty());
    //                if (!label.empty()) {
    //                    coder.SetLevel(m_LabelInfo[replacedLabelIndex].m_numOfIndents);
    //                    coder.Add("//" + m_labelPrefix + label + m_labelPostfix);
    //                    auto itFound = mapLabelAndChunk.find(label);
    //                    if (itFound != mapLabelAndChunk.end()) {
    //                        coder.AddChunk(*itFound->second);
    //                    }
    //                    coder.SetLevel(coder.GetLevel() - m_LabelInfo[replacedLabelIndex].m_numOfIndents);
    //                }
    //                ++replacedLabelIndex;
    //            }
    //            else {
    //                for (const auto& it : section) {
    //                    coder.Add(it);
    //                }
    //            }
    //        }
    //    }

    //private:
    //    std::vector<std::vector<std::string>> m_Context;
    //    std::vector<SShaderTemplateLabelInfo> m_LabelInfo;
    //    std::string m_labelPrefix;
    //    std::string m_labelPostfix;

    //    struct CShaderTemplateLabelInfo {
    //        int m_numOfIndents;
    //        size_t m_indexOfSection;
    //        // You might need other members here
    //    };

    //    // Utility functions
    //    std::string Trim(const std::string& str) {
    //        size_t first = str.find_first_not_of(" \t\n\r\f\v");
    //        if (first == std::string::npos)
    //            return "";
    //        size_t last = str.find_last_not_of(" \t\n\r\f\v");
    //        return str.substr(first, (last - first + 1));
    //    }

    //    int CountTabs(const std::string& str) {
    //        return std::count(str.begin(), str.end(), '\t');
    //    }
    //};

//    void TestMustache()
//    {
//        using namespace Niflect;
//        auto memTest = DebugGetMemoryStats();
//        if (false)
//        {
//            using namespace NiflectMustache;
//            CString view{R"(void MyFunc()
//{
//    MyArray arr;
//    {{#names}}
//    arr.add("{{name}}");
//    {{/names}}
//})"};
//            CData context;
//            CList array;
//            CData item0("name", "Chris");
//            CData item1("name", "Mark");
//            CData item2("name", "Scott");
//            array.push_back(item0);
//            array.push_back(item1);
//            array.push_back(item2);
//            context.set("names", array);
//            CMustache tmpl(view);
//            std::cout << tmpl.render(context) << std::endl;
//            printf("");
//        }
//        if (true)
//        {
//            using namespace NiflectMustache;
//            CString view0{ R"(void MyFunc()
//{
//    MyArray arr;
//    {{#names}}
//    arr.add("{{.}}");
//    {{/names}}
//})" };
//            CMustache tmpl0(view0);
//            CData context0;
//            {
//                CList array;
//                CData item0("Chris");
//                CData item1("Mark");
//                CData item2("Scott");
//                array.push_back(item0);
//                array.push_back(item1);
//                array.push_back(item2);
//                context0.set("names", array);
//            }
//            CString view1{ R"(class CMyClass
//{
//public:
//    {{>MemberFunc}}
//};)" };
//            CMustache tmpl1(view1);
//            {
//                CData context1;
//                CPartial sss = [&tmpl0, &context0]()
//                    {
//                        return tmpl0.render(context0);
//                    };
//                context1.set("MemberFunc", sss);
//                std::cout << tmpl1.render(context1) << std::endl;
//                printf("");
//            }
//        }
//    }
}

//static void TestMustache()
//{
//    //std::string view{ "{{#names}}Hi {{name}}!\n{{/names}}" };
//    //using namespace kainjow;
//    //mustache::data context;
//    //mustache::data array(mustache::data::type::list);
//    //mustache::data item0("name", "Chris");
//    //mustache::data item1("name", "Mark");
//    //mustache::data item2("name", "Scott");
//    //array.push_back(item0);
//    //array.push_back(item1);
//    //array.push_back(item2);
//    //context.set("names", array);
//    //mustache::mustache tmpl(view);
//    //std::cout << tmpl.render(context) << std::endl;
//    //printf("");
//
//    //using namespace NiflectMustache;
//    //using namespace Niflect;
//    //CString view{ "{{#names}}Hi {{name}}!\n{{/names}}" };
//    //CData context;
//    //CData array(CData::type::list);
//    //CData item0("name", "Chris");
//    //CData item1("name", "Mark");
//    //CData item2("name", "Scott");
//    //array.push_back(item0);
//    //array.push_back(item1);
//    //array.push_back(item2);
//    //context.set("names", array);
//    //CMustache tmpl(view);
//    //CStringStream ss;
//    //tmpl.render(context, ss);
//    //std::cout << ss.str() << std::endl;
//    //printf("");
//
//    using namespace Niflect;
//
//    auto memTest = DebugGetMemoryStats();
//    //auto memTestInitial = *memTest;
//    {
//        using namespace NiflectMustache;
//        CString view{ "{{#names}}Hi {{name}}!\n{{/names}}" };
//        CData context;
//        CData array(CData::type::list);
//        CData item0("name", "Chris");
//        CData item1("name", "Mark");
//        CData item2("name", "Scott");
//        array.push_back(item0);
//        array.push_back(item1);
//        array.push_back(item2);
//        context.set("names", array);
//        CMustache tmpl(view);
//        std::cout << tmpl.render(context) << std::endl;
//        printf("");
//    }
//    //ASSERT(memcmp(&memTestInitial, memTest, sizeof(memTestInitial)) == 0);
//}

//class CStaticTest
//{
//public:
//    CStaticTest()
//    {
//        TestMustache();
//    }
//};
//CStaticTest s;