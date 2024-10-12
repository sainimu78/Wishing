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
		CInheritableTypeRegCodeWriter2(const CResolvedCursorNode& bindingTypeIndexedRoot, const Niflect::TArrayNif<CResolvedCursorNode>& vecMemberIndexedRoot, const CTaggedType* baseTaggedType);

	public:
		virtual void WriteTypeRegRegisterTypeAndFieldLayout(const CWritingContext& context, CTypeRegRegisterAndFieldLayoutWritingData& data) const override;
		virtual void WriteTypeRegClass(const STypeRegClassWritingContext& context, CTypeRegClassWritingData2& data) const override;
		virtual void WriteTaggedTypeInit(const STypeRegClassWritingContext& context, CTypeRegTaggedTypeInitWritingData2& data) const override;

	private:
		void WriteStaticRegisterType(const STypeRegClassWritingContext& context, CCodeLines& lines) const;
		void WriteStaticInitType(const STypeRegClassWritingContext& context, CCodeLines& lines) const;

	private:
		const CResolvedCursorNode& m_bindingTypeIndexedRoot;
		const Niflect::TArrayNif<CResolvedCursorNode>& m_vecMemberIndexedRoot;
		const CTaggedType* m_baseTaggedType;
	};
}