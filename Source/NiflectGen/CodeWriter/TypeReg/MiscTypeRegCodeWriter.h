#pragma once
#include "NiflectGen/CodeWriter/TypeReg/FieldLayoutBasedCodeWriter.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCode.h"

namespace NiflectGen
{
	class CMiscTypeRegCodeWriter : public CFieldLayoutBasedCodeWriter
	{
		typedef CFieldLayoutBasedCodeWriter inherited;

	protected:
		virtual void WriteResocursorNodeBodyCode(CCodeLines& linesResoBodyCode) const override;
		virtual void CollectDependencyHeaderFilePaths(CDependencyHeaderFilePathRefs& dependencyHeaderFilePathRefs) const override;

	public:
		virtual void WriteTypeRegRegisterTypeAndFieldLayout(const CWritingContext& context, CTypeRegRegisterAndFieldLayoutWritingData& data) const override;
	};
}