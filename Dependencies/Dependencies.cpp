///////////////////////////////////////////////////////////////////////
// Dependencies.h add hyper link to source file to link each other   //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////

#include "Dependencies.h"
#include <sstream>
#include <iostream>

using namespace Lexer;
using namespace FileSystem;

namespace SourceCodePublisher {
	// -----< construct and deconstruct Dependencies >---------------

	Dependencies::Dependencies(int offset_) : offset(offset_) {}

	Dependencies::~Dependencies() {}


	// -----< add hyper links for a list of files >---------------

	void Dependencies::convertAll(const std::vector<std::string>& codepath_, const std::vector<std::string>& codename_, const std::vector<std::string>& path_, const std::vector<std::string>& name_)
	{
		if (codepath_.size() != path_.size() || codepath_.size() != name_.size() || codepath_.size() != codename_.size())
		{
			std::cout << "\n  Input did not match each other, please check input!" << std::endl;
			return;
		}
		position.clear();

		for (std::size_t i = 0; i != path_.size(); ++i)
		{
			recordPosition(codepath_[i], codename_[i]);
			convert(path_[i], name_[i]);
		}
	}

	// -----< record position to add hyper link >---------------

	void Dependencies::recordPosition(const std::string& codepath_, const std::string& codename_)
	{
		std::cout << "\n\n  <---" + codename_ + "--->";
		position.clear();
		Toker toker;

		std::string fqf = codepath_ + "\\" + codename_;  
		if (!toker.open(fqf))
		{
			std::cout << "\n can't open \"" << fqf << "\"\n";
			return;
		}
		else
		{
			std::cout << "\n\n  Processing file: \"" << fqf << "\"";
		}

		while (!toker.isDone())
		{
			Token tok = toker.getTok();
			if (tok == "include") {
				position.push_back(toker.lineCount() + offset);
			}
		}
		toker.close();
		std::cout << "\n";
	}

	// -----< add hyper links for a file >---------------

	void Dependencies::convert(const std::string& path_, const std::string& name_)
	{
		std::ifstream file(path_ + "\\" + name_);
		std::string str;
		int lineNum = 1;
		int iter = 0;
		int size = position.size();
		std::string newHTML;
		while (std::getline(file, str))
		{
			if (iter < size && position[iter] == lineNum) {
				std::string s;
				bool isName = false;
				bool isRef = true;
				for (size_t i = 0; i < str.size(); ++i) {
					if (isName) {
						s += str.at(i);
					}
					
					if (str.at(i) == '\"') {
						isName = !isName;
					}

					if (str.at(i) == '/') {
						isName = true;
						s.clear();
					}

					if (str.at(i) == '&') 
					{
						isRef = false;
						break;
					}
				}
				if (isRef && s.size() > 1) 
				{
					s.pop_back();
					std::string ref = path_ + "\\" + s + ".html";
					FileInfo fi(ref );
					if (fi.good())
					{
						std::cout << "\n  adding dependencies to " << ref;
						str = "<a href=\"" + ref + "\">" + str + "</a>";
					}
				}
				iter++;
			}
			newHTML += str + "\n";
			lineNum++;
		}
		std::ofstream newfile(path_ + "\\" + name_);
		newfile << newHTML;
		newfile.close();
	}
};
