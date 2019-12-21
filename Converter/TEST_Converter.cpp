///////////////////////////////////////////////////////////////////////
// Converter.h convert .cpp and .h files to HTML                     //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////
#include "Converter.h"
#include <iostream>
//TEST_STUB

#define TEST_CONVERTER
#ifdef TEST_CONVERTER

using namespace SourceCodePublisher;

int main(int argc, char *argv[])
{
	std::string testpath = FileSystem::Path::getFullFileSpec("../test_files/");
	std::string testname = "Converter.cpp";
	Converter C;
	C.convert(testpath, testname);
	std::cin.get();
}
#endif