#pragma once
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCodeWriter.h"
#include "NiflectGen/Resolver/ResolvedCursorNode.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCode.h"

namespace NiflectGen
{
	class CMiscTypeRegCodeWriter : public CTypeRegCodeWriter2
	{
	public:
		CMiscTypeRegCodeWriter(const CResolvedCursorNode& bindingTypeIndexedRoot);

	public:
		virtual void WriteTypeRegRegisterTypeAndFieldLayout(const CWritingContext& context, CTypeRegRegisterAndFieldLayoutWritingData& data) const override;

	private:
		const CResolvedCursorNode& m_bindingTypeIndexedRoot;
	};
}