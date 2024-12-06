#include "CMakeCodeTemplate.h"
#include "NiflectGen/CodeWriter/CodeWriter.h"

namespace WishingProjectTool
{
	void ReadTemplateFromRawData(NiflectGen::CCodeTemplate& tpl, const char* data)
	{
        tpl.InitLabelMarks("@{", "}");
        tpl.ReadFromRawData(data);
	}
}