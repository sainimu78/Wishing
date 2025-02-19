#pragma once
#include <string>
#include <vector>

using TStringList = std::vector<std::string>;

bool CmdExec(const char* cmd, TStringList* pLstStr = NULL);
bool CmdExec(const char* cmd, TStringList& lstStr);
bool CmdExecNonblocking(const char* cmd);