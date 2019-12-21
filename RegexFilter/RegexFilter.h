#pragma once
///////////////////////////////////////////////////////////////////////
// RegexFilter.h filter that take filename to match regex expression //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Regular Expression filter                            //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package will take two vector input paths and filenames plus regexes
 * and return a filtered path and filenames according to regex on filenames.
 *
 * Required Files:
 * ---------------
 * RegexFilter.h
 * RegexFilter.cpp
 * 
 * Maintenance History:
 * --------------------
 * 01 Feb, 2019
 */


#include <vector>
#include <regex>

class RegexFilter
{
public:

	static std::string version() { return "ver 1.0"; }

	// constructor and deconstructor

	RegexFilter(const std::vector<std::string>& path, const std::vector<std::string>& filename);
	~RegexFilter();

	// set input file names and regex to be used

	void setNames(const std::vector<std::string>& path, const std::vector<std::string>& filename);
	void setRegex(const std::string& regex_);
	
	// add input file names and regex to be used

	void addRegex(const std::string& regex_);
	void addNames(const std::string& path, const std::string& filename);

	// get the regex it is using

	std::string getReg();

	// get filtered file paths and names

	std::vector<std::string> getPaths();
	std::vector<std::string> getNames();


private:

	void run();
	bool isFiltered;
	std::string regex;

	std::vector<std::string> paths;
	std::vector<std::string> filteredPaths;
	std::vector<std::string> names;
	std::vector<std::string> filteredNames;
};
