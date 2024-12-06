#include "CMakeCodeTemplate.h"
#include "NiflectGen/CodeWriter/CodeWriter.h"

namespace WishingProjectTool
{
	void ReadTemplateFromRawData(NiflectGen::CCodeTemplate& tpl, const char* data)
	{
        tpl.InitLabelMarks(TEMPLATELABEL_L, TEMPLATELABEL_R);
        tpl.ReadFromRawData2(data);
	}
}