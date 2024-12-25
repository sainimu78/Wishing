#pragma once
#include "CodeWriter/CodeTemplate.h"

#define TEMPLATELABEL_L "@{"
#define TEMPLATELABEL_R "}"

#define MAKELABEL(name) TEMPLATELABEL_L name TEMPLATELABEL_R

namespace CMakeGen
{
	void ReadTemplateFromRawData(NiflectGen::CCodeTemplate& tpl, const char* data);
}