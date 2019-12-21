///////////////////////////////////////////////////////////////////////
// Demonstrate.h    demonstrate files using a web browser            //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////
#include "Demonstrate.h"
//TEST_STUB

#define DEMONSTRATE
#ifdef DEMONSTRATE

#include "../FileSystem/FileSystem.h"

using namespace SourceCodePublisher;

int main(int argc, char *argv[])
{
	std::string testpath = FileSystem::Path::getFullFileSpec("../test_files/");
	std::string testname = "Converter.h";
	std::vector<std::string> path;
	std::vector<std::string> name;
	path.push_back(testpath);
	name.push_back(testname);
	Demonstrate D;
	D.demonstrate(path, name);
	std::cin.get();
}
#endif