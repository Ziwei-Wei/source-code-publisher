///////////////////////////////////////////////////////////////////////
// Display.h  add buttons to source code to show/close code          //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////
#include "Display.h"
//TEST_STUB

#define TEST_DISPLAY
#ifdef TEST_DISPLAY


using namespace SourceCodePublisher;

int main(int argc, char *argv[])
{
	std::string originalpath = FileSystem::Path::getFullFileSpec("../test_files/");
	std::string originalname = "Converter.cpp";
	std::string testpath = FileSystem::Path::getFullFileSpec("../convertedPages/");
	std::string testname = "Converter.cpp.html";
	Display D(37);
	D.recordCommentPosition(originalpath, originalname);
	D.convertComment(testpath, testname);
	std::cin.get();
}
#endif