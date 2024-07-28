#pragma once
#include "Niflect/Field/CompoundField.h"

namespace Niflect
{
	typedef CCompoundField CCompoundTemplateField;

	class CContainerField : public CField
	{
	protected:
		CField* GetArgumentField(uint32 idx) const
		{
			return this->GetChild(idx);
		}
	};
}