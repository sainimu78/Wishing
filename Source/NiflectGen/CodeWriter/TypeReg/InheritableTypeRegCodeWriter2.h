#pragma once
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCodeWriter.h"
#include "NiflectGen/Collector/CollectionData.h"
#include "NiflectGen/Resolver/ResolvedData.h"
#include "NiflectGen/TaggedType/TaggedInheritableType.h"

namespace NiflectGen
{
	class CInheritableTypeRegCodeWriter2 : public CTypeRegCodeWriter2
	{
		typedef CTypeRegCodeWriter2 inherited;
	public:
		CInheritableTypeRegCodeWriter2(const Niflect::TArrayNif<CResolvedCursorNode>& vecFieldResocursorNode, const Niflect::TArrayNif<CTaggedInheritableTypeMember*>& vecField, const CTaggedType* baseTaggedType, uint32 generatedBodyLineNumber);

	protected:
		virtual void WriteResocursorNodeBodyCode(CCodeLines& linesResoBodyCode) const override;
		virtual void CollectDependencyHeaderFilePathAddrs(CDependencyHeaderFilePathAddrs& dependencyHeaderFilePathAddrs) const override;
		virtual void CollectDataForGenH(SCollectingGeneratedBodyWritingData& data) const override;

	public:
		virtual void WriteInvokeInitType(const STypeRegClassWritingContext& context, CTypeRegTaggedTypeInitWritingData2& data) const override;

	private:
		void WriteStaticInitType(const STypeRegClassWritingContext& context, CCodeLines& lines) const;

	private:
		const Niflect::TArrayNif<CResolvedCursorNode>& m_vecFieldResocursorNode;
		const Niflect::TArrayNif<CTaggedInheritableTypeMember*>& m_vecField;
		const CTaggedType* m_baseTaggedType;
		const uint32 m_generatedBodyLineNumber;
	};
}