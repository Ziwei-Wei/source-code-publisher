#pragma once
///////////////////////////////////////////////////////////////////////
// Converter.h convert .cpp and .h files to HTML                     //
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
 * Converter.h  Converter.cpp
 * FileSystem.h  FileSystem.cpp
 *
 * Maintenance History:
 * --------------------
 * ver 1.1 : 01 Mar, 2019
 */

#include "../FileSystem/FileSystem.h"

namespace SourceCodePublisher
{
	class Converter
	{
	public:

		static std::string version() { return "ver 1.1"; }

		// constructor and deconstructor

		Converter();
		~Converter();

		// convert function
		void convertAll(const std::vector<std::string>& path_, const std::vector<std::string>& name_);
		void convert(const std::string& path_, const std::string& name_);

		// set output directory and new html format file

		void setOutputAddress(const std::string& address);
		void setNewFormat(const std::string& path, const std::string& name);
		void caculateOffset();

		// get current input, output address and number of converted files

		int getOffset();
		std::vector<std::string> getOutPath();
		std::vector<std::string> getOutName();

	private:
		int offset;
		std::string HTMLbutton;
		std::string HTMLformat;
		std::string endHTML;
		std::string outPath;
		std::vector<std::string> names;
	};
}