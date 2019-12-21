///////////////////////////////////////////////////////////////////////
// Demonstrate.h    demonstrate files using a web browser            //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////

#include "../Process/Process.h"
#include "Demonstrate.h"
#include <conio.h>

namespace SourceCodePublisher
{
	// -----< get vector of converted files >---------------

	Demonstrate::Demonstrate()
	{
		appPath = "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe";
	}

	// -----< get vector of converted files >---------------

	Demonstrate::~Demonstrate() {}

	// -----< get vector of converted files >---------------

	void Demonstrate::setApp(std::string appPath_)
	{
		appPath = appPath_;
	}

	// -----< check is ready for display >-----------------
	bool Demonstrate::isReady(const std::vector<std::string>& path_, const std::vector<std::string>& name_)
	{
		if (path_.size() != name_.size())
		{
			std::cout << "\n\n  Input path amount shall equal to input name amount." << std::endl;
			return false;
		}
		if (appPath.empty())
		{
			std::cout << "\n\n  Missing appPath, not ready to demonstrate" << std::endl;
			return false;
		}
		return true;
	}

	// -----< get vector of converted files >---------------

	void Demonstrate::demonstrate(const std::vector<std::string>& path_, const std::vector<std::string>& name_)
	{
		if (!isReady(path_, name_))
		{
			return;
		}
		Process p;
		std::cout << "\n\n\n  Current application is in location : " + appPath;
		std::cout << "\n  ==================================";
		std::cout << "\n  Demonstrateing file in web browser";
		std::cout << "\n  ==================================";
		p.title("test application");
		p.application(appPath);

		for (size_t i = 0; i < path_.size(); ++i)
		{
			std::string cmdLine = "/A " + path_[i] + "\\" + name_[i];
			p.commandLine(cmdLine);

			std::cout << "\n  You need to kill each window (upper right button) to continue.";
			std::cout << "\n  Press key to start";
			_getche();

			std::cout << "\n  starting process: \"" << appPath << "\"";
			std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
			p.create();
			CBP callback = []() { std::cout << "\n  --- child process exited with this message ---\n"; };
			p.setCallBackProcessing(callback);
			p.registerCallback();

			WaitForSingleObject(p.getProcessHandle(), INFINITE);  // wait for created process to terminate
		}
	}

	// -----< get vector of converted files >---------------

	void Demonstrate::demonstrate(const std::vector<std::string>& addresses_)
	{
		if (appPath.empty())
		{
			std::cout << "\n\n  Missing appPath, not ready to demonstrate" << std::endl;
			return;
		}
		Process p;
		std::cout << "\n\n\n  Current application is in location : " + appPath;
		std::cout << "\n  ==================================";
		std::cout << "\n  Demonstrateing file in web browser";
		std::cout << "\n  ==================================";
		p.title("test application");
		p.application(appPath);

		for (size_t i = 0; i < addresses_.size(); ++i)
		{
			std::string cmdLine = "/A " + addresses_[i];
			p.commandLine(cmdLine);

			std::cout << "\n  You need to kill each window (upper right button) to continue.";
			std::cout << "\n  Press key to start";
			_getche();

			std::cout << "\n  starting process: \"" << appPath << "\"";
			std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
			p.create();
			CBP callback = []() { std::cout << "\n  --- child process exited with this message ---\n"; };
			p.setCallBackProcessing(callback);
			p.registerCallback();

			WaitForSingleObject(p.getProcessHandle(), INFINITE);  // wait for created process to terminate
		}
	}
}
