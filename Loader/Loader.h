#pragma once
///////////////////////////////////////////////////////////////////////
// Loader.h  load/store addresses by command line or path plus name  //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This Package takes command line input and scan files correspoundingly.
 * It will store the searched files for future access.
 *
 * Required Files:
 * ---------------
 * Loader.h  Loader.cpp
 * DirExplorerN.h  CodeUtilities.h StringUtilities.h
 * FileSystem.h  FileSystem.cpp
 * RegexFilter.h  RegexFilter.cpp
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 01 Mar, 2019
 */

#include "../FileSystem/FileSystem.h"
#include "../DirExplorerN/DirExplorerN.h"
#include "../RegexFilter/RegexFilter.h"
#include "../DirExplorerN/CodeUtilities.h"
#include "../DirExplorerN/StringUtilities.h"

namespace SourceCodePublisher
{
	class Loader{
	public:

		inline static std::string version() { return "ver 1.0"; }
		
		//constructor and deconstructor
		Loader();
		virtual ~Loader();

		//load and clean operation
		void loadCML(int argc, char *argv[]);
		void loadAddresses(const std::vector<std::string>& path_, const std::vector<std::string>& name_);
		void loadFiles(const std::vector<std::string>& addresses_);
		void clean();

		//getters
		int getSize();
		std::vector<std::string> getPath();
		std::vector<std::string> getName();
		std::vector<std::string> getAddresses();

	private:
		int size = 0;
		std::vector<std::string> filePath;
		std::vector<std::string> fileName;
	};
};
