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
		CInheritableTypeRegCodeWriter2(const Niflect::TArrayNif<CResolvedCursorNode>& vecFieldResocursorNode, const Niflect::TArrayNif<CTaggedInheritableTypeMember*>& vecField, const CTaggedType* baseTaggedType);

	protected:
		virtual void WriteResocursorNodeBodyCode(CCodeLines& linesResoBodyCode) const override;
		virtual void CollectDependencyHeaderFilePathAddrs(CDependencyHeaderFilePathAddrs& dependencyHeaderFilePathAddrs) const override;

	public:
		virtual void WriteTypeRegRegisterTypeAndFieldLayout(const CWritingContext& context, CTypeRegRegisterAndFieldLayoutWritingData& data) const override;
		virtual void Deprecated_WriteTypeRegClass(const STypeRegClassWritingContext& context, CTypeRegClassWritingData2& data) const override;
		virtual void WriteInvokeInitType(const STypeRegClassWritingContext& context, CTypeRegTaggedTypeInitWritingData2& data) const override;

	private:
		void WriteStaticRegisterType(const STypeRegClassWritingContext& context, CCodeLines& lines) const;
		void WriteStaticInitType(const STypeRegClassWritingContext& context, CCodeLines& lines) const;

	private:
		const Niflect::TArrayNif<CResolvedCursorNode>& m_vecFieldResocursorNode;
		const Niflect::TArrayNif<CTaggedInheritableTypeMember*>& m_vecField;
		const CTaggedType* m_baseTaggedType;
	};
}