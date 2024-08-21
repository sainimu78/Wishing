#include "NiflectGen/CodeWriter/ModuleReg/SplittedModuleRegCodeWriter.h"
#include "NiflectGen/CodeWriter/CodeTemplate.h"
#include "NiflectGen/CodeWriter/HardCoded/SplittedModuleRegistrationTemplate.h"
#include "Niflect/Util/StringUtil.h"
#include "NiflectGen/CodeWriter/CppWriter.h"
#include "NiflectGen/Base/NiflectGenDefinition.h"

namespace NiflectGen
{
    void DetermineSplitting(const Niflect::TArrayNif<SSplittedModuleRefInfo>& vecTypeRegRefInfo, Niflect::TArrayNif<CSplittedModuleRegInvokationData>& vecSplittedModuleRegInvokationData, Niflect::TArrayNif<CSplittedModuleRegGenData>& vecSplittedModuleRegData, Niflect::TArrayNif<Niflect::TArrayNif<uint32> >& vecSplittedModuleRegToTypeRegs)
    {
        vecSplittedModuleRegInvokationData.resize(1);
        vecSplittedModuleRegData.resize(1);
        vecSplittedModuleRegToTypeRegs.resize(vecSplittedModuleRegInvokationData.size());
        for (uint32 idx = 0; idx < vecTypeRegRefInfo.size(); ++idx)
        {
            vecSplittedModuleRegToTypeRegs[0].push_back(idx);
        }
    }
	void WriteSplittedModuleRegs(const CWritingContext& context, const SSplittedModuleRegWritingContext& writingCtx, Niflect::TArrayNif<CSplittedModuleRegInvokationData>& vecSplittedModuleRegInvokationData, Niflect::TArrayNif<CSplittedModuleRegGenData>& vecSplittedModuleRegData)
	{
        Niflect::TArrayNif<Niflect::TArrayNif<uint32> > vecSplittedModuleRegToTypeRegs;
        DetermineSplitting(writingCtx.m_vecTypeRegRefInfo, vecSplittedModuleRegInvokationData, vecSplittedModuleRegData, vecSplittedModuleRegToTypeRegs);
        ASSERT(vecSplittedModuleRegInvokationData.size() == vecSplittedModuleRegData.size());

        for (uint32 idx0 = 0; idx0 < vecSplittedModuleRegInvokationData.size(); ++idx0)
        {
            auto& dataForInvokation = vecSplittedModuleRegInvokationData[idx0];
            auto& data = vecSplittedModuleRegData[idx0];

            auto splittedModuleName = ReplaceLabelToText2(HardCodedTemplate::SplittedModuleName, LABEL_SHARED_0, LABEL_0, writingCtx.m_moduleName, NiflectUtil::FormatString("%u", idx0));
            {
                CCodeTemplate tpl;
                tpl.ReadFromRawData(HardCodedTemplate::SplittedModuleRegH);
                CLabelToCodeMapping map;
                MapLabelToText(map, LABEL_1, splittedModuleName);
                tpl.ReplaceLabels(map, data.m_h);
            }
            dataForInvokation.m_invokationRegisterTypes.push_back(ReplaceLabelToText1(HardCodedTemplate::SplittedModuleRegInvokationRegisterTypes, LABEL_1, splittedModuleName));
            dataForInvokation.m_invokationInitTypes.push_back(ReplaceLabelToText1(HardCodedTemplate::SplittedModuleRegInvokationInitTypes, LABEL_1, splittedModuleName));
            data.m_includePath = NiflectUtil::FormatString("%s/__%s%s", writingCtx.m_moduleRegBasePath.c_str(), splittedModuleName.c_str(), NiflectGenDefinition::FileExt::H);

            {
                CCodeTemplate tpl;
                tpl.ReadFromRawData(HardCodedTemplate::ModuleReg_TypeRegInitTable);
                CLabelToCodeMapping map;
                MapLabelToText(map, LABEL_1, splittedModuleName);
                tpl.ReplaceLabels(map, dataForInvokation.m_codeInitTables);
            }

            auto& vecTypeRegIndex = vecSplittedModuleRegToTypeRegs[idx0];
            CCodeLines linesInvokationRegisterType;
            CCodeLines linesInvokationInitType;
            CNoDupPathCollector includesNoDup;
            includesNoDup.Add(data.m_includePath);
            for (uint32 idx1 = 0; idx1 < vecTypeRegIndex.size(); ++idx1)
            {
                auto& refInfo = writingCtx.m_vecTypeRegRefInfo[vecTypeRegIndex[idx1]];
                auto& it0 = *refInfo.m_typeRegData;
                includesNoDup.Add(*refInfo.m_includePathPrivateH);
                auto regNamespace = "reserved_reg_namespace";//todo: ��it��ȡnamespace?
                linesInvokationRegisterType.push_back(ReplaceLabelToText2(HardCodedTemplate::InvokationRegisterType, LABEL_6, LABEL_7, regNamespace, it0.m_regClassName));
                if (it0.m_invokationRequirement.m_requiredInvokationInitType)
                    linesInvokationInitType.push_back(ReplaceLabelToText2(HardCodedTemplate::InvokationInitType, LABEL_6, LABEL_7, regNamespace, it0.m_regClassName));

                //data.m_linesInvokingRegisterType.push_back(ReplaceLabelToText2(HardCodedTemplate::InvokationRegisterType, LABEL_6, LABEL_7, regNamespace, it0.m_regClassName));
                //if (it0.m_invokationRequirement.m_requiredInvokationInitType)
                //{
                //    data.m_linesInvokingInitType.push_back(ReplaceLabelToText2(HardCodedTemplate::InvokationInitType, LABEL_6, LABEL_7, regNamespace, it0.m_regClassName));
                //}
            }
            CCodeLines linesIncludes;
            CIncludesHelper::Write(includesNoDup, linesIncludes);

            CCodeLines linesInvokationRegisterTypeScope;
            {
                CCodeTemplate tpl;
                tpl.ReadFromRawData(HardCodedTemplate::TypeRegRegsterTypeScope);
                CLabelToCodeMapping map;
                MapLabelToLines(map, LABEL_3, linesInvokationRegisterType);
                tpl.ReplaceLabels(map, linesInvokationRegisterTypeScope);
            }
            {
                CCodeTemplate tpl;
                tpl.ReadFromRawData(HardCodedTemplate::SplittedModuleRegCpp);
                CLabelToCodeMapping map;
                MapLabelToText(map, LABEL_1, splittedModuleName);
                MapLabelToLines(map, LABEL_2, linesInvokationRegisterTypeScope);
                MapLabelToLines(map, LABEL_4, linesInvokationInitType);
                MapLabelToLines(map, LABEL_5, linesIncludes);
                tpl.ReplaceLabels(map, data.m_cpp);
            }
        }
	}
}