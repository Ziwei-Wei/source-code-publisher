///////////////////////////////////////////////////////////////////////
// Loader.h  load/store addresses by command line or path plus name  //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////

#include "Loader.h"

Utilities::ProcessCmdLine::Usage customUsage()
{
	std::string usage;
	usage += "\n  Command Line: path [/option]* [/pattern]* [/regex]*";
	usage += "\n    path is relative or absolute path where processing begins";
	usage += "\n    [/option]* are one or more options of the form:";
	usage += "\n      /s - walk directory recursively";
	usage += "\n    [/pattern]* are one or more pattern strings of the form:";
	usage += "\n      *.h *.cpp *.cs *.txt or *.*";
	usage += "\n    [/regex]* are regex to select files from patterns";
	usage += "\n";
	return usage;
}

namespace SourceCodePublisher
{
	// -----< constructor and deconstructor >---------------
	Loader::Loader() {}
	Loader::~Loader() {}

	// -----< load from command line args >---------------
	void Loader::loadCML(int argc, char *argv[])
	{
		//process commandline args
		Utilities::ProcessCmdLine* pcl = new Utilities::ProcessCmdLine(argc, argv);
		Utilities::Title("Loader, " + Loader::version());
		pcl->usage(customUsage());
		Utilities::preface("Command Line: ");
		pcl->showCmdLine();
		Utilities::putline();
		if (pcl->parseError())
		{
			pcl->usage();
			std::cout << "\n\n  parseError";
		}

		//search files and filter files
		FileSystem::DirExplorerN de(pcl->path());
		for (auto patt : pcl->patterns())
		{
			de.addPattern(patt);
		}
		if (pcl->hasOption('s'))
		{
			de.recurse();
		}
		de.search();
		de.showStats();

		RegexFilter filter(de.getPath(), de.getNames());
		for (auto regex : pcl->regexes())
		{
			filter.addRegex(regex);
		}
		if (filter.getPaths().empty())
		{
			std::cout << "\n  Error no file found, will exit" << std::endl;
		}

		//load files
		loadAddresses(filter.getPaths(), filter.getNames());
	}

	// -----< load by paths and names >---------------
	void Loader::loadAddresses(const std::vector<std::string>& path_, const std::vector<std::string>& name_) 
	{
		if (size != 0) 
		{
			clean();
		}

		if (path_.size() == name_.size())
		{
			std::cout << "\n  load successifully!" << std::endl;
			size = path_.size();
		}
		else
		{
			std::cout << "\n path and name did not match!" << std::endl;
			clean();
		}

		filePath = path_;
		fileName = name_;
	}

	void Loader::loadFiles(const std::vector<std::string>& addresses_)
	{
		if (size != 0)
		{
			clean();
		}
		for (std::string address : addresses_) 
		{	
			int i = address.size();
			for (; i > 2; i--) {
				if (address[i] == '\\' || address[i] == '/') {
					break;
				}
			}
			filePath.push_back(address.substr(0, i));
			fileName.push_back(address.substr(i + 1));
			size++;
		}
	}

	// -----< clean up the loader >---------------
	void Loader::clean() 
	{
		filePath.clear();
		fileName.clear();
		size = 0;
	}


	// -----< all getters >---------------
	int Loader::getSize()
	{
		return size;
	}

	std::vector<std::string> Loader::getPath() 
	{
		return filePath;
	}

	std::vector<std::string> Loader::getName() 
	{
		return fileName;
	}

	std::vector<std::string> Loader::getAddresses()
	{
		std::vector<std::string> temp;
		for (int i = 0; i < size; ++i) {
			temp.push_back(filePath[i] + "/" + fileName[i]);
		}
		return temp;
	}

};
