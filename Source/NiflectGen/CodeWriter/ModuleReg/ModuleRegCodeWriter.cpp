#include "NiflectGen/CodeWriter/ModuleReg/ModuleRegCodeWriter.h"
#include "NiflectGen/Util/CursorUtil.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/CodeWriter/TypeReg/InheritableTypeRegCodeWriter.h"
#include "NiflectGen/CodeWriter/ModuleReg/SplittedModuleRegCodeWriter.h"
#include <algorithm>
#include "NiflectGen/Base/NiflectGenDefinition.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegPrivateHeaderCodeWriter.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegGenHeaderCodeWriter.h"
#include "NiflectGen/CodeWriter/ModuleReg/ModuleRegPrivateHeaderCodeWriter.h"

namespace NiflectGen
{
    class CScopedTypeCode
    {
    public:
        Niflect::TArrayNif<Niflect::CString> m_vecDeclScope;
        Niflect::TArrayNif<Niflect::CString> m_vecNamespace;
    };
    CTemplateBasedCppWriter::CTemplateBasedCppWriter(const CResolvedData& resolvedData, const CModuleRegInfoValidated& moduleRegInfo)
        : m_resolvedData(resolvedData)
        , m_moduleRegInfo(moduleRegInfo)
    {
        //printf("%s\n", HardCodedTemplate::InheritableTypeReg_ClassImpl);
        //printf("");
    }
    //class CWriteScope;
    //using CSharedWriteScope = Niflect::TSharedPtr<CWriteScope>;
    //class CWriteScope
    //{
    //public:
    //    Niflect::CString m_scopeName;
    //    Niflect::TArrayNif<uint32> m_vecResolvedTypesArrayIndex;
    //    CWriteScope* m_parent;
    //    Niflect::TArrayNif<CSharedWriteScope> m_vecChild;
    //};
    //void CTemplateBasedCppWriter::Write()
    //{
    //    //CWriteScope rootWriteScope;
    //    //Niflect::TMap<Niflect::CString, CWriteScope*> mapScopePathToWriteScope;
    //    Niflect::TArrayNif<CScopedTypeCode> vecScopedTypeCode;
    //    for (auto& it0 : m_resolvedData.m_vecResolvedTypes)
    //    {
    //        //printf("%s\n", it0.m_filePathRelativeToHeaderSearchPath.c_str());
    //        for (auto& it1 : it0.m_vecResolvedTaggedType)
    //        {
    //            auto& cursor = it1.m_taggedType->GetCursor();
    //            CScopedTypeCode scopedTypeCode;
    //            FindNamespaceAndScopeNameRecurs(cursor, scopedTypeCode.m_vecNamespace, scopedTypeCode.m_vecDeclScope);
    //            vecScopedTypeCode.emplace_back(scopedTypeCode);
    //            //if (it1.m_isBuiltinType)
    //            {
    //                //auto& cursor = it1.m_taggedType->GetCursor();
    //                //auto a = CXStringToCString(clang_getCursorSpelling(cursor));
    //                //printf("%s, %s\n", a.c_str(), it0.m_filePathRelativeToHeaderSearchPath.c_str());
    //                //Niflect::TArrayNif<Niflect::CString> vecNamespace;
    //                //Niflect::TArrayNif<Niflect::CString> vecDeclScope;
    //                //FindNamespaceAndScopeNameRecurs(cursor, vecNamespace, vecDeclScope);
    //                //Niflect::CString scopePath;
    //                //Niflect::TArrayNif<Niflect::CString> vecScope;
    //                //{
    //                //    for (uint32 idx2 = 0; idx2 < vecNamespace.size(); ++idx2)
    //                //    {
    //                //        scopePath += vecNamespace[idx2];
    //                //        vecScope.push_back(vecNamespace[idx2]);
    //                //    }
    //                //    for (uint32 idx2 = 0; idx2 < vecDeclScope.size(); ++idx2)
    //                //    {
    //                //        scopePath += vecDeclScope[idx2];
    //                //        vecScope.push_back(vecDeclScope[idx2]);
    //                //    }
    //                //}
    //                //auto parent = &rootWriteScope;
    //                //auto itFound = mapScopePathToWriteScope.find(scopePath);
    //                //if (itFound != mapScopePathToWriteScope.end())
    //                //    parent = itFound->second;
    //                //auto child = Niflect::MakeShared<CWriteScope>();
    //                //child->m_scopeName = 
    //                //parent->m_vecChild.push_back()
    //                //Niflect::CString strNamespace;
    //                //for (uint32 idx2 = 0; idx2 < vecNamespace.size(); ++idx2)
    //                //    strNamespace += vecNamespace[idx2] + "::";
    //                //Niflect::CString strScope;
    //                //for (uint32 idx2 = 0; idx2 < vecScope.size(); ++idx2)
    //                //    strScope += vecScope[idx2] + "::";
    //                //printf("%s, %s, %s\n", strNamespace.c_str(), strScope.c_str(), a.c_str());
    //            }
    //        }
    //    }
    //    printf("");
    //    //for (auto& it : m_resolvedData.m_vecResolvedType)
    //    //{
    //    //    auto& cursor = it.m_taggedType->GetCursor();

    //    //    auto a = CXStringToCString(clang_getCursorSpelling(cursor));
    //    //    auto loc = clang_getCursorLocation(cursor);
    //    //    CXFile file;
    //    //    clang_getSpellingLocation(loc, &file, NULL, NULL, NULL);
    //    //    auto fileName = CXStringToCString(clang_getFileName(file));
    //    //    printf("%s, %s\n", a.c_str(), fileName.c_str());
    //    //}
    //    printf("");
    //}
    void CTemplateBasedCppWriter::CreateWriters(const CWritingContext& context, Niflect::TArrayNif<CTypeRegGenFileInfo>& vecTypeRegGenFileInfo)
    {
        ASSERT(m_vecWriter.size() == 0);

        {
            auto& userProvided = m_moduleRegInfo.m_userProvided;
            for (auto& it1 : userProvided.m_vecOriginalHeader)
            {
                auto ret = m_mapping.m_mapOriginalFilePathToModuleRegIndicesAndIncPath.insert({ it1, SModuleRegIndicesAndIncludePath()});
                auto& item = ret.first->second;
                if (ret.second)
                {
                    auto incPath = CIncludesHelper::ConvertToIncludePath(it1, userProvided.m_vecHeaderSearchPath);
                    item.m_includePath_reserved = incPath;
                    auto orgIncPathPrivateH = NiflectUtil::ReplaceFilePathExt(incPath, NiflectGenDefinition::FileExt::H, NiflectGenDefinition::FileExt::PrivateH);
                    auto genIncPathPrivateH = NiflectUtil::ConcatPath(m_moduleRegInfo.m_typeRegBasePath, orgIncPathPrivateH);
                    auto orgIncPathGenH = NiflectUtil::ReplaceFilePathExt(incPath, NiflectGenDefinition::FileExt::H, NiflectGenDefinition::FileExt::GenH);
                    auto genIncPathGenH = NiflectUtil::ConcatPath(m_moduleRegInfo.m_typeRegBasePath, orgIncPathGenH);
                    item.m_includePathPrivateHIndex = static_cast<uint32>(vecTypeRegGenFileInfo.size());
                    vecTypeRegGenFileInfo.push_back(CTypeRegGenFileInfo(genIncPathPrivateH, genIncPathGenH));
                }
                else
                {
                    ASSERT(false);//todo: 一次调用只能输出一个ModuleReg, 计划废弃ModuleReg数组, 如果将ModuleReg混在一起处理可能导致一些Module依赖配错却能输出正确结果
                }
            }
        }

        auto& accessorBindingMapping = m_resolvedData.deprecated_m_mapping.m_accessorBindingMapping;
        for (auto& it0 : accessorBindingMapping.m_vecAccessorBinding2)
        {
            if (it0.m_accessorData.m_isNotATemplate)
            {
                auto filePath = GetCursorFilePath(it0.m_accessorSubcursor.m_cursorDecl);
                auto itFound = m_mapping.m_mapOriginalFilePathToModuleRegIndicesAndIncPath.find(filePath);
                if (itFound != m_mapping.m_mapOriginalFilePathToModuleRegIndicesAndIncPath.end())
                {
                    auto& item = itFound->second;
                    uint32 writerIndex = static_cast<uint32>(m_vecWriter.size());
                    m_mapping.m_vecTypeRegIndices.push_back(writerIndex);
                    auto& privateHeaderData = vecTypeRegGenFileInfo[item.m_includePathPrivateHIndex];
                    privateHeaderData.m_vecTypeRegDataIndex.push_back(writerIndex);
                    ASSERT(it0.Is1D());//不支持模板, 因此只能为1D, 对应的Binding类型可能为builtin, 类型Decl或别名
                    CAccessorBindingMapping2 placeholder0;
                    CTaggedTypesMapping placeholder1;
                    CUntaggedTemplateTypesMapping placeholder2;
                    SResolvedMappings placeholderMappings{ placeholder0, placeholder1, placeholder2 };
                    CResolvingDependenciesContext placeholderCtx(placeholderMappings, NULL);
                    STypeRegClassWritingSetting setting = { m_moduleRegInfo.m_userProvided.m_vecHeaderSearchPath, m_resolvedData.deprecated_m_mapping, placeholderCtx };
                    m_vecWriter.push_back(Niflect::MakeShared<CInheritableTypeRegCodeWriter_FieldAccessor>(it0.m_accessorSubcursor.m_cursorDecl, setting, it0.m_actualFieldDeclCursor, it0.m_vecWWWW[0].m_subcursor));
                    m_mapping.m_vecTypeRegIncludePathPrivateHRef.push_back(&privateHeaderData.m_prevateHIncludePath);
                }
            }
        }

        for (auto& it0 : m_resolvedData.m_vecResolvedTypes2)
        {
            auto& cursor = it0.m_taggedType->GetCursor();
            auto filePath = GetCursorFilePath(cursor);
            //在此处挑选实际需要生成的类型是为避免在Resolve或之前的流程中可能出现的大量路径查找, 在此处虽查找量未减少, 但可通过如并行实现一定优化
            auto itFound = m_mapping.m_mapOriginalFilePathToModuleRegIndicesAndIncPath.find(filePath);
            if (itFound != m_mapping.m_mapOriginalFilePathToModuleRegIndicesAndIncPath.end())
            {
                auto& item = itFound->second;
                uint32 writerIndex = static_cast<uint32>(m_vecWriter.size());
                m_mapping.m_vecTypeRegIndices.push_back(writerIndex);
                auto& privateHeaderData = vecTypeRegGenFileInfo[item.m_includePathPrivateHIndex];
                privateHeaderData.m_vecTypeRegDataIndex.push_back(writerIndex);
                CAccessorBindingMapping2 placeholder0;
                CTaggedTypesMapping placeholder1;
                CUntaggedTemplateTypesMapping placeholder2;
                SResolvedMappings placeholderMappings{ placeholder0, placeholder1, placeholder2 };
                CResolvingDependenciesContext placeholderCtx(placeholderMappings, NULL);
                STypeRegClassWritingSetting setting = { m_moduleRegInfo.m_userProvided.m_vecHeaderSearchPath, m_resolvedData.deprecated_m_mapping, placeholderCtx };
                m_vecWriter.push_back(it0.m_taggedType->CreateCodeWriter(setting));
                m_mapping.m_vecTypeRegIncludePathPrivateHRef.push_back(&privateHeaderData.m_prevateHIncludePath);
            }
        }
    }
    void CTemplateBasedCppWriter::CreateWriters3(const CWritingContext& context, Niflect::TArrayNif<CTypeRegGenFileInfo>& vecTypeRegGenFileInfo)
    {
        //Niflect::TMap<Niflect::CString, SModuleRegIndicesAndIncludePath> mapOriginalFilePathToModuleRegIndicesAndIncPath;
        //{
        //    ASSERT(m_vecWriter.size() == 0);
        //    {
        //        auto& userProvided = m_moduleRegInfo.m_userProvided;
        //        for (auto& it1 : userProvided.m_vecOriginalHeader)
        //        {
        //            auto ret = mapOriginalFilePathToModuleRegIndicesAndIncPath.insert({ it1, SModuleRegIndicesAndIncludePath() });
        //            auto& item = ret.first->second;
        //            if (ret.second)
        //            {
        //                auto incPath = CIncludesHelper::ConvertToIncludePath(it1, userProvided.m_vecHeaderSearchPath);
        //                item.m_includePath_reserved = incPath;
        //                auto orgIncPathPrivateH = NiflectUtil::ReplaceFilePathExt(incPath, NiflectGenDefinition::FileExt::H, NiflectGenDefinition::FileExt::PrivateH);
        //                auto genIncPathPrivateH = NiflectUtil::ConcatPath(m_moduleRegInfo.m_typeRegBasePath, orgIncPathPrivateH);
        //                auto orgIncPathGenH = NiflectUtil::ReplaceFilePathExt(incPath, NiflectGenDefinition::FileExt::H, NiflectGenDefinition::FileExt::GenH);
        //                auto genIncPathGenH = NiflectUtil::ConcatPath(m_moduleRegInfo.m_typeRegBasePath, orgIncPathGenH);
        //                item.m_includePathPrivateHIndex = static_cast<uint32>(vecTypeRegGenFileInfo.size());
        //                vecTypeRegGenFileInfo.push_back(CTypeRegGenFileInfo(genIncPathPrivateH, genIncPathGenH));
        //            }
        //            else
        //            {
        //                ASSERT(false);//todo: 一次调用只能输出一个ModuleReg, 计划废弃ModuleReg数组, 如果将ModuleReg混在一起处理可能导致一些Module依赖配错却能输出正确结果
        //            }
        //        }
        //    }

        //    for (auto& it0 : m_resolvedData.m_taggedMapping.m_vecType)
        //    {
        //        auto& cursor = it0->GetCursor();
        //        auto filePath = GetCursorFilePath(cursor);
        //        //在此处挑选实际需要生成的类型是为避免在Resolve或之前的流程中可能出现的大量路径查找, 在此处虽查找量未减少, 但可通过如并行实现一定优化
        //        auto itFound = mapOriginalFilePathToModuleRegIndicesAndIncPath.find(filePath);
        //        if (itFound != mapOriginalFilePathToModuleRegIndicesAndIncPath.end())
        //        {
        //            auto& item = itFound->second;
        //            auto& privateHeaderData = vecTypeRegGenFileInfo[item.m_includePathPrivateHIndex];
        //            uint32 writerIndex = static_cast<uint32>(m_vecWriter.size());
        //            m_mapping.m_vecTypeRegIndices.push_back(writerIndex);
        //            privateHeaderData.m_vecTypeRegDataIndex.push_back(writerIndex);
        //            CResolvedMapping placeholder;
        //            SResolvedMappings mappings{ *m_resolvedData.m_accessorBindingMapping, m_resolvedData.m_taggedMapping, m_resolvedData.m_untaggedTemplateMapping };
        //            CResolvingDependenciesContext creationCtx(mappings, context.m_log);
        //            STypeRegClassWritingSetting setting = { m_moduleRegInfo.m_userProvided.m_vecHeaderSearchPath, placeholder, creationCtx };
        //            auto writer = it0->CreateCodeWriter(setting);
        //            m_vecWriter.push_back(writer);
        //            m_mapping.m_vecTypeRegIncludePathPrivateHRef.push_back(&privateHeaderData.m_prevateHIncludePath);
        //        }
        //    }
        //}

        //printf("");

        for (auto& it0 : m_resolvedData.m_signatureMapping.m_vecItem)
        {
            if (it0.m_indexedRoot.m_settingIdx != INDEX_NONE)
            {
                auto writer = Niflect::MakeShared<CInheritableTypeRegCodeWriter2>();
                m_vecWriter2.push_back(writer);
            }
            else if (it0.m_indexedRoot.m_taggedIdx != INDEX_NONE)
            {
                ASSERT(false);//writer基类已改
                auto& taggedType = m_resolvedData.m_taggedMapping.m_vecType[it0.m_indexedRoot.m_taggedIdx];

                CResolvedMapping placeholder;
                SResolvedMappings mappings{ *m_resolvedData.m_accessorBindingMapping, m_resolvedData.m_taggedMapping, m_resolvedData.m_untaggedTemplateMapping };
                CResolvingDependenciesContext creationCtx(mappings, context.m_log);
                STypeRegClassWritingSetting setting = { m_moduleRegInfo.m_userProvided.m_vecHeaderSearchPath, placeholder, creationCtx };
                auto writer = taggedType->CreateCodeWriter(setting);
                m_vecWriter.push_back(writer);
            }
            else
            {
                ASSERT(false);
            }
        }
    }
    void CTemplateBasedCppWriter::Deprecated_Write2(const CWritingContext& context, CCodeGenData& data)
    {
        Niflect::TArrayNif<CTypeRegGenFileInfo> vecTypeRegGenFileInfo;
        this->CreateWriters(context, vecTypeRegGenFileInfo);

        Niflect::TArrayNif<CTypeRegWritingData> vecTypeRegData;
        this->WriteTypeRegs(context, vecTypeRegData);

        {
            auto& userProvided = m_moduleRegInfo.m_userProvided;
            Niflect::TArrayNif<SSplittedModuleRefInfo> vecRefInfo;
            for (auto& it1 : m_mapping.m_vecTypeRegIndices)
            {
                SSplittedModuleRefInfo ref{&vecTypeRegData[it1], m_mapping.m_vecTypeRegIncludePathPrivateHRef[it1]};
                vecRefInfo.push_back(ref);
            }
            SSplittedModuleRegWritingContext spliitedModuleRegWritingCtx = { userProvided.m_moduleName, m_moduleRegInfo.m_moduleRegBasePath, vecRefInfo };
            Niflect::TArrayNif<CSplittedModuleRegInvokationData> vecSplittedModuleRegInvokationData;
            WriteSplittedModuleRegs(context, spliitedModuleRegWritingCtx, vecSplittedModuleRegInvokationData, data.m_vecSplittedModuleRegGenData);

            SModuleRegWritingContext moduleRegWritngCtx = { userProvided.m_moduleName, vecSplittedModuleRegInvokationData, data.m_vecSplittedModuleRegGenData };
            auto genIncPathPrivateH = NiflectUtil::ConcatPath(m_moduleRegInfo.m_moduleRegBasePath, userProvided.m_moduleName) + NiflectGenDefinition::FileExt::PrivateH;
            data.m_moduleRegGenData.m_privateHIncludePath = genIncPathPrivateH;
            SModuleRegWritingData moduleRegWrtingData = { data.m_moduleRegGenData.m_privateH };
            WriteModuleRegPrivateHeader(context, moduleRegWritngCtx, moduleRegWrtingData);
        }

        data.m_vecTypeRegGenData.resize(vecTypeRegGenFileInfo.size());
        for (uint32 idx0 = 0; idx0 < vecTypeRegGenFileInfo.size(); ++idx0)
        {
            STypeRegPrivateHeaderWritingContext writingCtx;
            for (auto& it1 : vecTypeRegGenFileInfo[idx0].m_vecTypeRegDataIndex)
                writingCtx.m_vecWritingData.push_back(&vecTypeRegData[it1]);
            auto& typeRegGenData = data.m_vecTypeRegGenData[idx0];
            typeRegGenData.m_privateHIncludePath = vecTypeRegGenFileInfo[idx0].m_prevateHIncludePath;
            STypeRegPrivateHeaderWritingData writingData = { typeRegGenData.m_privateH };
            WriteTypeRegsPrivateHeader(context, writingCtx, writingData);
        }
        for (uint32 idx0 = 0; idx0 < vecTypeRegGenFileInfo.size(); ++idx0)
        {
            STypeRegGenHeaderWritingContext writingCtx;
            for (auto& it1 : vecTypeRegGenFileInfo[idx0].m_vecTypeRegDataIndex)
                writingCtx.m_vecWritingData.push_back(&vecTypeRegData[it1]);
            auto& typeRegGenData = data.m_vecTypeRegGenData[idx0];
            typeRegGenData.m_genHIncludePath = vecTypeRegGenFileInfo[idx0].m_genHIncludePath;
            STypeRegGenHeaderWritingData writingData = { typeRegGenData.m_genH };
            WriteTypeRegsGenHeader(context, writingCtx, writingData);
        }
    }
    void CTemplateBasedCppWriter::Write3(const CWritingContext& context, CCodeGenData& data)
    {
        Niflect::TArrayNif<CTypeRegGenFileInfo> vecTypeRegGenFileInfo;
        this->CreateWriters3(context, vecTypeRegGenFileInfo);

        printf("");
    }
    void CTemplateBasedCppWriter::WriteTypeRegs(const CWritingContext& context, Niflect::TArrayNif<CTypeRegWritingData>& vecTypeRegData)
    {
        for (auto& it : m_vecWriter)
            it->Deprecated_Init();

        vecTypeRegData.resize(m_vecWriter.size());
        for (uint32 idx0 = 0; idx0 < m_vecWriter.size(); ++idx0)
        {
            auto& it = m_vecWriter[idx0];
            auto& data = vecTypeRegData[idx0];

            it->WritePrivateHeaderIncludePath(context, data.m_privateHeaderincludePath);

            if (false)
            {
                CTypeRegDeclWrittingData dataClassDecl(data.deprected_m_linesRegDecl);
                it->WriteDecl(context, dataClassDecl);
                CCodeLines linesClassImpl;
                CTypeRegImplWrittingData dataClassImpl(data.deprected_m_linesRegImpl);
                it->WriteImpl(context, dataClassImpl);

                DebugPrintCodeLines(dataClassDecl.m_lines);
                DebugPrintCodeLines(dataClassImpl.m_lines);
            }
            if (true)
            {
                CTypeRegClassWrittingData dataClass(data.m_linesRegClass, data.m_privateHeaderincludePath);
                it->WriteClass(context, dataClass);

                DebugPrintCodeLines(dataClass.m_lines);
                printf("");
            }

            data.m_regClassName = it->WriteTypeRegClassName();
            //auto regNamespace = "reserved_reg_namespace";//todo: 从it获取namespace?

            //data.m_linesInvokingRegisterType.push_back(ReplaceLabelToText2(HardCodedTemplate::ModuleReg_InvokationRegisterType, LABEL_5, LABEL_6, regNamespace, regScopeName));

            it->GetInvokationRequirement(data.m_invokationRequirement);
            //if (dataInvocationRequirement.m_requiredInvokationInitType)
            //{
                //data.m_linesInvokingInitType.push_back(ReplaceLabelToText2(HardCodedTemplate::ModuleReg_InvokationInitType, LABEL_5, LABEL_6, regNamespace, regScopeName));
            //}

            it->WriteGenHeaderDeclaration(context, data.m_genHeaderDeclData);

            data.m_vecNamespaceRequirement = it->GetNamespaces();
        }
    }
    //void CTemplateBasedCppWriter::WriteModuleRegs(const CWritingContext& context, const Niflect::TArrayNif<CTypeRegWritingData>& vecTypeRegData, Niflect::TArrayNif<CModuleRegWritingData>& vecModuleRegData)
    //{

    //}
}