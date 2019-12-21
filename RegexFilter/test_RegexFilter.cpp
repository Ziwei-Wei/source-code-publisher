///////////////////////////////////////////////////////////////////////
// RegexFilter.h filter that take filename to match regex expression //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Regular Expression filter                            //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////

#define TEST_REGEXFILTER
#ifdef TEST_REGEXFILTER

#include "RegexFilter.h"
#include "../DirExplorerN/DirExplorerN.h"

int main(int argc, char *argv[])
{
	// prologue
	std::cout << "\n  Demonstrating RegexFilter";
	std::cout << "\n  =========================";
	std::cout << "\n  " + RegexFilter::version() << std::endl;
	std::cout << "\n  test subjects are" << std::endl;
	FileSystem::DirExplorerN de("..//test_files");
	de.search();
	std::vector<std::string> paths = de.getPath();
	std::vector<std::string> names = de.getNames();

	RegexFilter filter(de.getPath(), de.getNames());

	// no regex input
	std::cout << "\n\n\n  Demonstrating when there is no regex input";
	std::cout <<     "\n  ==========================================";
	std::cout << "\n  output are\n\n" << std::endl;

	std::vector<std::string> filtered = filter.getNames();
	for (std::string name : filtered) 
	{
		std::cout << "\n  --    " + name;
	}

	// when regex is [a-z].*
	std::cout << "\n\n\n Demonstrating when regex is [a-z].*";
	std::cout <<     "\n  ==========================================";
	std::cout << "\n  output are\n\n" << std::endl;

	filter.addRegex("[a - z].*");
	filtered = filter.getNames();

	// when regex is D.*
	std::cout << "\n\n\n  Demonstrating when we reset regex to D.*";
	std::cout <<     "\n  ========================================";
	std::cout << "\n  output are\n\n" << std::endl;

	filter.setRegex("D.*");
	filtered = filter.getNames();

	std::cout << "\n\n\n  Demonstrating end";
	std::cout <<     "\n  =================" << std::endl;
	system("pause");
	return 0;
}
#endif // REGEX