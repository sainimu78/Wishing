#pragma once
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCodeWriter.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCode.h"

namespace NiflectGen
{
	class CMiscTypeRegCodeWriter : public CTypeRegCodeWriter2
	{
		typedef CTypeRegCodeWriter2 inherited;

	protected:
		virtual void WriteResocursorNodeBodyCode(CCodeLines& linesResoBodyCode) const override;
		virtual void CollectDependencyHeaderFilePaths(CDependencyHeaderFilePathRefs& dependencyHeaderFilePathRefs) const override;

	public:
		virtual void WriteTypeRegRegisterTypeAndFieldLayout(const CWritingContext& context, CTypeRegRegisterAndFieldLayoutWritingData& data) const override;
	};
}