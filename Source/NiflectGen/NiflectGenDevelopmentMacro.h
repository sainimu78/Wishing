#pragma once

//要求非模板的Accessor类型必须使用NIF_T标记
//2024.08.21, 现规划废弃此要求, 且 Accessor 可为一定规则的模板类
//#define TAGGED_REQUIREMENT_OF_NON_TEMPLATE_ACCESSOR_TYPE