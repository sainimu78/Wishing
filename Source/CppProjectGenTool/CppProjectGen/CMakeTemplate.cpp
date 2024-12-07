#include "CMakeTemplate.h"

namespace WishingProjectTool
{
	void ReadTemplateFromRawData(NiflectGen::CCodeTemplate& tpl, const char* data)
	{
        tpl.InitLabelMarks(TEMPLATELABEL_L, TEMPLATELABEL_R);
        tpl.ReadFromRawData2(data);
	}
}