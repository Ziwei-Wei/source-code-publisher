#pragma once
///////////////////////////////////////////////////////////////////////
// Demonstrate.h    demonstrate files using a web browser            //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * open a web page to demonstrate files one by one, requires app
 * and file address inputs.
 *
 * Required Files:
 * ---------------
 * demonstrate.h
 * Process.h
 * demonstrate.cpp
 *
 * Maintenance History:
 * --------------------
 * ver 1.1 : 01 Mar, 2019
 */

#include "../Process/Process.h"
#include <vector>



namespace SourceCodePublisher
{
	class Demonstrate
	{
	public:

		static std::string version() { return "ver 1.1"; }

		// constructors and deconstructor

		Demonstrate();
		~Demonstrate();

		// set app path and file addresses

		void setApp(std::string appPath_);

		// demonstrate files in app

		void demonstrate(const std::vector<std::string>& path_, const std::vector<std::string>& name_);
		void demonstrate(const std::vector<std::string>& addresses_);
		
	private:
		// helper function
		bool isReady(const std::vector<std::string>& path_, const std::vector<std::string>& name_);
		std::string appPath;
	};
}