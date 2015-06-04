﻿
/*
Copyright (c) 2013-2015 Maximus5
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "CmdArg.h"
#include "MArray.h"

bool ProcessSetEnvCmd(LPCWSTR& asCmdLine, bool bDoSet, CmdArg* rpsTitle = NULL);
bool SetConsoleCpHelper(UINT nCP);

class CProcessEnvCmd
{
public:
	struct Command
	{
		wchar_t  szCmd[8]; // 'set', 'chcp', 'title', and may be 'alias' later...
		wchar_t* pszName;
		wchar_t* pszValue;
	};
	MArray<Command*> m_Commands;
	size_t   mch_Total;   // wchar-s required to store all data, including all \0 terminators
	size_t   mn_SetCount; // Counts only 'set' commands
	Command* mp_CmdTitle;
	Command* mp_CmdChCp;

public:
	CProcessEnvCmd();
	~CProcessEnvCmd();

public:
	// Append helpers
	void AddCommands(LPCWSTR asCommands, LPCWSTR* ppszEnd = NULL); // May comes from Task or ConEmu's /cmd switch
	Command* Add(LPCWSTR asCmd, LPCWSTR asName, LPCWSTR asValue);

public:
	// Apply routine, returns true if environment was set/changed
	bool Apply(CmdArg* rpsTitle = NULL);
};
