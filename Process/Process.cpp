///////////////////////////////////////////////////////////////////////
// Process.cpp - class used to start process                         //
// ver 1.0                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018         //
///////////////////////////////////////////////////////////////////////

#include "Process.h"

CBP Process::cbp_ = []() { std::cout << "\n  --- child process exited ---"; };

//----< Process constructor >------------------------------------------
/*
* - This eventually will have more functionality
*/
inline Process::Process()
{
	GetStartupInfo(&startInfo_);
	startInfo_.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	startInfo_.dwX = 200;
	startInfo_.dwY = 250;
	startInfo_.dwYSize = 300;
}
//----< helper function to convert strings >---------------------------

std::string wToS(const std::wstring& ws)
{
	std::string conv;
	for (auto ch : ws)
	{
		conv.push_back(static_cast<char>(ch));
	}
	return conv;
}
//----< helper function to convert strings >---------------------------

std::wstring sToW(const std::string& s)
{
	std::wstring conv;
	for (auto ch : s)
	{
		conv.push_back(static_cast<wchar_t>(ch));
	}
	return conv;
}
//----< define application new process runs >--------------------------

void Process::application(const std::string& appName)
{
	appName_ = sToW(appName);
}
//----< define commandline passed to new application >-----------------

void Process::commandLine(const std::string& cmdLine)
{
	commandLine_ = sToW(cmdLine);
}
//----< define title bar for console window >--------------------------
/*
* - applications like Notepad overwrite this string
*/
void Process::title(const std::string& title)
{
	title_ = sToW(title);
	startInfo_.lpTitle = const_cast<LPWSTR>(title_.c_str());
}
//----< start new child process >--------------------------------------

bool Process::create(const std::string& appName)
{
	std::wstring app;
	if (appName.size() == 0)
		app = appName_;
	else
	{
		app = sToW(appName);
	}
	LPCTSTR applic = const_cast<LPCTSTR>(app.c_str());
	LPTSTR cmdLine = const_cast<LPTSTR>(commandLine_.c_str());
	LPSECURITY_ATTRIBUTES prosec = nullptr;
	LPSECURITY_ATTRIBUTES thrdsec = nullptr;
	BOOL inheritHandles = false;
	DWORD createFlags = CREATE_NEW_CONSOLE;  // or CREATE_NO_WINDOW
	LPVOID environment = nullptr;
	LPCTSTR currentPath = nullptr;
	LPSTARTUPINFO pStartInfo = &startInfo_;
	LPPROCESS_INFORMATION pPrInfo = &procInfo_;

	BOOL OK =
		CreateProcess(
			applic, cmdLine, prosec, thrdsec, inheritHandles,
			createFlags, environment, currentPath, pStartInfo, pPrInfo
		);
	return OK;
}

///////////////////////////////////////////////////////////////////////
// child process exit callback processing

//----< provide new callable object for callback to invoke >-----------

void Process::setCallBackProcessing(CBP cbp)
{
	cbp_ = cbp;
}
//----< function called when child process exists >--------------------

void Process::callback()
{
	cbp_();
}
//----< Windows API declared function type for callbacks >-------------

void CALLBACK WaitOrTimerCallback(_In_ PVOID lpParameter, _In_ BOOLEAN TimerOrWaitFired)
{
	Process p;
	p.callback();
	return;
}
//----< register callback with Windows API >---------------------------

void Process::registerCallback()
{
	HANDLE hNewHandle;
	HANDLE hProcHandle = procInfo_.hProcess;
	RegisterWaitForSingleObject(
		&hNewHandle, hProcHandle, WaitOrTimerCallback,
		NULL, INFINITE, WT_EXECUTEONLYONCE
	);
}

HANDLE Process::getProcessHandle()
{
	return procInfo_.hProcess;
}