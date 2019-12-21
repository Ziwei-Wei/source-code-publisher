#include "Loader.h"

//TEST_STUB

#define TEST_LOADER
#ifdef TEST_LOADER

using namespace SourceCodePublisher;

int main(int argc, char *argv[])
{
	std::cout << argv[4];
	Loader testL;
	testL.loadCML(argc, argv);
	std::vector<std::string> path = testL.getPath();
	std::vector<std::string> name = testL.getName();
	std::vector<std::string> addresses;

	for (int i = 0; i < testL.getSize(); ++i)
	{	
		addresses.push_back(path[i] + "\\" + name[i]);
	}
	Loader newtest;
	newtest.loadFiles(addresses);

	std::vector<std::string> newpath = newtest.getPath();
	std::vector<std::string> newname = newtest.getName();
	for (int i = 0; i < newtest.getSize(); ++i)
	{
		std::cout << " \n" << newpath[i] << "\\" << newname[i];
	}

	std::cin.get();
}
#endif
