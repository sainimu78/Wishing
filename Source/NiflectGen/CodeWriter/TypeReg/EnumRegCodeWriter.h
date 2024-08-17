#pragma once
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCodeWriter.h"

namespace NiflectGen
{
	class CEnumRegCodeWriter : public CTypeRegCodeWriter
	{
		typedef CTypeRegCodeWriter inherited;
	public:
		CEnumRegCodeWriter(const CXCursor& cursor, const STypeRegClassWritingSetting& writingSetting);

	public:
		virtual void WriteDecl(const CWritingContext& context, CTypeRegDeclWrittingData& data) const override;
		virtual void WriteImpl(const CWritingContext& context, CTypeRegImplWrittingData& data) const override;
		virtual void WriteClass(const CWritingContext& context, CTypeRegClassWrittingData& data) const override;
		virtual Niflect::CString WriteTypeRegClassName() const override;
		virtual void GetInvokationRequirement(CTypeRegInvokationData& data) const override;
		virtual Niflect::CString GetInfoTypeName() const override;
	};
}