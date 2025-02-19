#include "Util/MyCmd.h"
#include <sstream>

#ifdef WIN32
#include <Windows.h>
#else
#endif

#ifdef WIN32
#define CmdExecPOpen _popen
#define CmdExecPClose _pclose
#else
#define CmdExecPOpen popen
#define CmdExecPClose pclose
#endif

#ifdef WIN32
static bool system_hide(const char* argCmd, bool getResult, std::stringstream& ss)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead = NULL;
	HANDLE hWrite = NULL;
	const int pipeBufSiz = 64;
	std::string cmd = argCmd;
	cmd = "cmd /c " + cmd;
	//ss.seekp(0);

	if (getResult == true)
	{
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;

		if (!CreatePipe(&hRead, &hWrite, &sa, 0))
		{
			return false;
		}
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	if (!CreateProcess(NULL, (char*)cmd.c_str(), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		return false;
	}
	CloseHandle(hWrite);

	if (getResult == true)
	{
		char buffer[pipeBufSiz] = { 0 };
		DWORD bytesRead;
		while (true)
		{
			//memset(buffer,0,strlen(buffer));  
			if (ReadFile(hRead, buffer, pipeBufSiz, &bytesRead, NULL) == NULL)

				break;
			ss.write(buffer, bytesRead);

			//printf(buffer);
			//Sleep(100);       
		}
		ss << '\0';
	}
	return true;
}
#else
#endif

static void LoadFromStringStream(std::stringstream& in, TStringList& vecStr)
{
	std::string line;
	vecStr.clear();
	while (std::getline(in, line))
	{
		vecStr.push_back(line);
	}
}
static void LoadFromString(std::string& str, TStringList& vecStr)
{
	std::stringstream in;
	in.str(str);
	std::string line;
	vecStr.clear();
	while (std::getline(in, line))
	{
		vecStr.push_back(line);
	}
}

bool CmdExec(const char* cmd, TStringList* pLstStr)
{
	bool result = false;
#ifdef WIN32
	std::stringstream ss;
	result = system_hide(cmd, pLstStr != NULL, ss);
	if ((result == true) && (pLstStr != NULL))
		LoadFromStringStream(ss, *pLstStr);
#else
	char buffer[128];
	std::string str = "";
	FILE* pipe = CmdExecPOpen(cmd, "r");
	result = pipe != NULL;// throw "popen() failed!";
	if ((result == true) && (pLstStr != NULL))
	{
		try {
			while (!feof(pipe)) {
				if (fgets(buffer, 128, pipe) != NULL)
					str += buffer;
			}
		}
		catch (...) {
			CmdExecPClose(pipe);
			//throw;
		}
		CmdExecPClose(pipe);
	}
	if (pLstStr != NULL)
		LoadFromString(str, *pLstStr);
#endif
	return result;
}
bool CmdExec(const char* cmd, TStringList& lstStr)
{
	return CmdExec(cmd, &lstStr);
}
bool CmdExecNonblocking(const char* cmd)
{
	std::string str = cmd;
#ifdef WIN32
	str = "start " + str;
#else
	str = str + " &";
	//FILE* pipe = CmdExecPOpen(str.c_str(), "r");
	//CmdExecPClose(pipe);
#endif
	return CmdExec(str.c_str(), NULL);
}