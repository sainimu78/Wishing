//#pragma once
//#include "NiflectGen/CodeWriter/TypeReg/TypeRegCodeWriter.h"
//
//namespace NiflectGen
//{
//	class CFieldLayoutBasedCodeWriter : public CTypeRegCodeWriter2
//	{
//		typedef CTypeRegCodeWriter2 inherited;
//	public:
//		CFieldLayoutBasedCodeWriter();
//
//	public:
//		virtual void WriteForFieldLayout(const STypeRegCreateFieldLayoutOfTypeWritingContext& context, STypeRegCreateFieldLayoutOfTypeWritingData& data) const final override;
//
//	protected:
//		virtual void WriteResocursorNodeBodyCode(CCodeLines& linesResoBodyCode) const {}
//		virtual void CollectDependencyHeaderFilePaths(CDependencyHeaderFilePathRefs& dependencyHeaderFilePathRefs) const = 0;
//
//	private:
//		void WriteCreateFieldLayoutOfType(const STypeRegCreateFieldLayoutOfTypeWritingContext& context, CCodeLines& dataDecl, CCodeLines& dataImpl) const;
//	};
//}