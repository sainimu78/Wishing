#include <stdio.h>
#include "Util/MyCmd.h"

int main()
{
	TStringList vecStr;
#ifdef WIN32
	const char* cmd = "dir /B ..\\..\\..\\..\\..\\Niflect";
#else
	const char* cmd = "ls ../../../../../Niflect";
#endif
	auto b = CmdExec(cmd, vecStr);
	if(b)
	{
		for (auto& it : vecStr)
			printf("%s\n", it.c_str());
	}
	else
	{
		printf("Failed\n");
	}
	
	return 0;
}
