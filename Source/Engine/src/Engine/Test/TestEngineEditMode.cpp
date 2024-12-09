#include "Engine/Test/TestEngineEditMode.h"
#include "Niflect/Util/StringUtil.h"

namespace TestEngineEditMode
{
	enum EArg { ECmd, EVal };
	void Run(const Niflect::CString& input)
	{
		auto vecArg = NiflectUtil::Split(input, ' ');
		ASSERT(vecArg.size() % 2 == 0);
		for (uint32 idx = 0; idx < vecArg.size(); idx += 2)
		{
			auto arg = &vecArg[idx];
			if (arg[ECmd] == "r")
			{
				printf("Reload %s\n", arg[EVal].c_str());
			}
		}
	}
}