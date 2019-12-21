///////////////////////////////////////////////////////////////////////
// RegexFilter.h filter that take filename to match regex expression //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Regular Expression filter                            //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////

#include "RegexFilter.h"
#include <iostream>

// -----< Construct RegexFilter using paths and filenames >---------------

RegexFilter::RegexFilter(const std::vector<std::string>& path, const std::vector<std::string>& filename)
{
	paths = path;
	names = filename;
	isFiltered = false;
}

// -----< Deconstructor >---------------

RegexFilter::~RegexFilter() {}

// -----< Filt all files out >---------------

void RegexFilter::run()
{
	if (!isFiltered)
	{
		if (regex.empty())
		{
			std::cout << "\n  no regex detected will return all input files" << std::endl;
			isFiltered = true;
			return;
		}

		std::cout << "\n  =============================================";
		std::cout << "\n  Filtering file names according to given regex";
		std::cout << "\n  =============================================";

		filteredNames.clear();
		filteredPaths.clear();
		std::regex reg(regex);
		for (int i = 0; i != names.size(); ++i)
		{
			if (std::regex_match(names[i], reg))
			{
				std::cout << "\n  " + names[i] + " matched regular expression " + regex;
				filteredNames.push_back(names[i]);
				filteredPaths.push_back(paths[i]);
			}
		}
		isFiltered = true;
		std::cout << "\n\n";
	}
}

// -----< Add new regex to collection >---------------

void RegexFilter::addRegex(const std::string& regex_) 
{
	if (!regex_.empty())
	{
		if (regex.empty())
		{
			regex = regex_;
		}
		else
		{
			regex += "|" + regex_;
		}
		isFiltered = false;
		std::cout << "\n  current regex is " + regex;
	}
}

// -----< add new files to filt >---------------

void RegexFilter::addNames(const std::string& path, const std::string& filename)
{
	paths.push_back(path);
	names.push_back(filename);
	isFiltered = false;
}

// -----< (re)set filenames >---------------

void RegexFilter::setNames(const std::vector<std::string>& path, const std::vector<std::string>& filename)
{
	paths = path;
	names = filename;
	isFiltered = false;
}

// -----< reset regular expression >---------------

void RegexFilter::setRegex(const std::string& regex_)
{
	regex = regex_;
	isFiltered = false;
}

// -----< function ... that does this and that >---------------

std::string RegexFilter::getReg() 
{
	return regex;
}

// -----< function ... that does this and that >---------------

std::vector<std::string> RegexFilter::getPaths()
{
	run();
	return regex.empty() ? paths : filteredPaths;
}

// -----< function ... that does this and that >---------------

std::vector<std::string> RegexFilter::getNames()
{
	run();
	return regex.empty() ? names : filteredNames;
}