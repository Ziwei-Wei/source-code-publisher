#include "../Loader/Loader.h"
#include "../Converter/Converter.h"
#include "../Display/Display.h"
#include "../Dependencies/Dependencies.h"
#include "../Demonstrate/Demonstrate.h"
#include "IExecutive.h"

using namespace SourceCodePublisher;

class codeConverter : public IcodeConverter
{
public:

	virtual void convert(const std::vector<std::string>& addresses_, const std::string& output_, bool addDisplay_ = true, bool addDependency_ = true) {

		//get files
		Loader files;
		files.loadFiles(addresses_);

		//convert to HTML
		SourceCodePublisher::Converter HTML;
		HTML.setOutputAddress(output_);
		HTML.convertAll(files.getPath(), files.getName());

		//add display button
		if (addDisplay_ == true) {
			Display addDisplay(HTML.getOffset());
			addDisplay.convertAll(files.getPath(), files.getName(), HTML.getOutPath(), HTML.getOutName());
		}
		
		//add dependencies
		if (addDependency_ == true) { 
			Dependencies addDepend(HTML.getOffset());
			addDepend.convertAll(files.getPath(), files.getName(), HTML.getOutPath(), HTML.getOutName());
		}
	}

	virtual void convert(const std::string& path_, const std::string& output_, bool recurive_ = true, bool addDisplay_ = true, bool addDependency_ = true) {
		int argc = 4;
		char *argv[5];
		argv[1] = (char*)path_.c_str();
		argv[2] = (char*)"/s\0";
		argv[3] = (char*)"*.cpp\0";
		argv[4] = (char*)"*.h\0";

		if (recurive_ == false) {
			argv[2] = (char*)"";
		}

		//get files
		Loader files;
		files.loadCML(argc, argv);

		//convert to HTML
		SourceCodePublisher::Converter HTML;
		HTML.setOutputAddress(output_);
		HTML.convertAll(files.getPath(), files.getName());

		//add display button
		if (addDisplay_ == true) {
			Display addDisplay(HTML.getOffset());
			addDisplay.convertAll(files.getPath(), files.getName(), HTML.getOutPath(), HTML.getOutName());
		}

		//add dependencies
		if (addDependency_ == true) {
			Dependencies addDepend(HTML.getOffset());
			addDepend.convertAll(files.getPath(), files.getName(), HTML.getOutPath(), HTML.getOutName());
		}
	}

	virtual void demonstrate(const std::vector<std::string>& addresses_) {
		//demonstrate
		Demonstrate showInBrowser;
		showInBrowser.demonstrate(addresses_);
	}
};


IcodeConverter* createCodeConverter() {
	return new codeConverter();
}

#define TEST_EXECUTIVE
#ifdef TEST_EXECUTIVE
using namespace SourceCodePublisher;
void printMSG(const std::string& msg)
{
	std::string out;
	out += "\n\n\n  //////////////////////////////////////////////////////////////////////////////////////////////////";
	out += "\n  ";
	out += msg;
	out += "\n  //////////////////////////////////////////////////////////////////////////////////////////////////";
	std::cout << out << std::endl;
}


int main(int argc, char *argv[])
{
	std::string outpath = FileSystem::Path::getFullFileSpec("..\\convertedPages");
	std::string add = "C:\\Users\\R2D404\\Desktop\\SourceCodePublisher3";
	codeConverter* pCodeConverter = new codeConverter();
	pCodeConverter->convert(add, outpath);
	std::cin.get();
}
#endif // TEST_EXECUTIVE


