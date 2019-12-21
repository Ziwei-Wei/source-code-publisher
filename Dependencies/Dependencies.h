#pragma once
///////////////////////////////////////////////////////////////////////
// Dependencies.h add hyper link to source file to link each other   //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This Package takes addresses of .cpp and .h code files as input. It will
 * read these files and produce respective HTML version of code and store
 * them in an assisgned folder.
 *
 * Required Files:
 * ---------------
 * Dependencies.h  Dependencies.cpp
 * FileSystem.h  FileSystem.cpp
 * Toker.h  Toker.cpp
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 01 Mar, 2019
 */

#include "../Tokenizer/Toker.h"
#include "../FileSystem/FileSystem.h"

namespace SourceCodePublisher {
	class Dependencies
	{
	public:
		static std::string version() { return "ver 1.0"; }

		// constructor and deconstructor
		Dependencies(int offset_);
		~Dependencies();

		// convert function
		void convertAll(const std::vector<std::string>& codepath_, const std::vector<std::string>& codename_, const std::vector<std::string>& path_, const std::vector<std::string>& name_);
		void convert(const std::string& path_, const std::string& name_);
		void recordPosition(const std::string& codepath_, const std::string& codename_);

	private:

		int offset;
		std::vector<int> position;
	};
};

