///////////////////////////////////////////////////////////////////////
// Dependencies.h add hyper link to source file to link each other   //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////
#include "Dependencies.h"
//TEST_STUB

#define TEST_DEPENDENCIES
#ifdef TEST_DEPENDENCIES

using namespace SourceCodePublisher;

int main(int argc, char *argv[])
{
	std::string testpath = FileSystem::Path::getFullFileSpec("../convertedPages/");
	std::string testname = "Converter.h.html";
	Dependencies C(37);
	C.convert(testpath, testname);
	std::cin.get();
}
#endif