#pragma once
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCodeWriter.h"
#include "NiflectGen/Resolver/TypeRegSignature.h"
#include "NiflectGen/CodeWriter/TypeReg/TypeRegCode.h"

namespace NiflectGen
{
	class CMiscTypeRegCodeWriter : public CTypeRegCodeWriter2
	{
	public:
		CMiscTypeRegCodeWriter(const CBindingAccessorIndexedNode& bindingTypeIndexedRoot);

	public:
		virtual void WriteTypeRegRegisterTypeAndFieldLayout(const CWritingContext& context, CTypeRegRegisterAndFieldLayoutWritingData& data) const override;

	private:
		const CBindingAccessorIndexedNode& m_bindingTypeIndexedRoot;
	};
}