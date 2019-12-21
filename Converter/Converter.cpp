///////////////////////////////////////////////////////////////////////
// Converter.h convert .cpp and .h files to HTML                     //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////


#include "Converter.h"
#include <sstream>
#include <iostream>
#include <regex>

namespace SourceCodePublisher
{
	// -----< construct and deconstruct Converter >---------------

	Converter::Converter()
	{
		HTMLformat += "<!Doctype html>\n";
		HTMLformat += "<html>\n";
		HTMLformat += "<head>\n";
		HTMLformat += "  <style>\n";
		HTMLformat += "    body{\n";
		HTMLformat += "      padding: 15px 40px;\n";
		HTMLformat += "      font - family: Consolas;\n";
		HTMLformat += "      font - size: 1.25em;\n";
		HTMLformat += "      font - size: 1.25em;\n";
		HTMLformat += "      font - weight: normal;\n";
		HTMLformat += "    }\n";
		HTMLformat += "span{\n";
		HTMLformat += "  display:inline;\n";
		HTMLformat += "}\n";
		HTMLformat += "  </style>\n";
		HTMLformat += "  <script>\n";
		HTMLformat += "	function showHideClass(className) {\n";
		HTMLformat += "	let elems = document.getElementsByClassName(className);\n";
		HTMLformat += "	  if (elems === null) {\n";
		HTMLformat += "		  return;\n";
		HTMLformat += "	  }\n";
		HTMLformat += "	  for (let i = 0; i < elems.length; ++i) {\n";
		HTMLformat += "	  	  let displayProp = elems[i].style.display;\n";
		HTMLformat += "		  if (displayProp === 'none')\n";
		HTMLformat += "			  elems[i].style['display'] = \"inline\";\n";
		HTMLformat += "		  else\n";
		HTMLformat += "			  elems[i].style['display'] = \"none\";\n";
		HTMLformat += "	  }\n";
		HTMLformat += "}\n";
		HTMLformat += "  </script>\n";
		HTMLformat += "<head>\n";

		HTMLbutton += "  <button onclick = \"showHideClass(\'toggleCommentDisplay\')\">Show or Hide Comment Contents</button>\n";
		HTMLbutton += "  <button onclick = \"showHideClass(\'toggleClassDisplay\')\">Show or Hide Class Contents</button>\n";
		HTMLbutton += "  <button onclick = \"showHideClass(\'toggleFunctionDisplay\')\">Show or Hide Function Contents</button>\n";

		endHTML = "\n</pre>\n  </body>\n</html>";

		caculateOffset();

		outPath = FileSystem::Path::getFullFileSpec("..\\convertedPages");
	}

	Converter::~Converter() {}

	// -----< caculate offset created by current setting >---------------

	void Converter::caculateOffset()
	{
		offset = 0;
		std::string temp = HTMLformat + "<body>\n  <h3></h3>\n" + HTMLbutton + "<pre>\n";
		for (char ch : temp) {
			if (ch == '\n') {
				offset++;
			}
		}
	}

	// -----< change output address >---------------

	void Converter::setOutputAddress(const std::string& address)
	{
		outPath = FileSystem::Path::getFullFileSpec(address);
	}

	// -----< change format file of final output >---------------

	void Converter::setNewFormat(const std::string& path, const std::string& name)
	{
		std::ifstream formatAddress(FileSystem::Path::getFullFileSpec(path) + "//" + name);
		std::stringstream formatBuffer;
		formatBuffer << formatAddress.rdbuf();
		std::string format(formatBuffer.str());
		HTMLformat = format;
		caculateOffset();
	}

	// -----< convert source code to HTML >---------------

	void Converter::convertAll(const std::vector<std::string>& path_, const std::vector<std::string>& name_)
	{
		std::cout << "\n  Converting source code to HTML";
		std::cout << "\n  ==============================" << std::endl;
		names.clear();
		for (std::size_t i = 0; i != path_.size(); ++i)
		{
			convert(path_[i], name_[i]);
		}
	}

	void Converter::convert(const std::string& path_, const std::string& name_) 
	{
		std::ifstream input(path_ + "\\" + name_);
		std::stringstream bufferin;
		bufferin << input.rdbuf();
		std::string code(bufferin.str());
		std::string HTML;
		for (char ch : code)
		{
			if (ch == '<')
			{
				HTML += "&lt";
			}
			else if (ch == '>')
			{
				HTML += "&gt";
			}
			else
			{
				HTML += ch;
			}
		}

		names.push_back(name_ + ".html");
		std::string output = outPath + "\\" + name_ + ".html";
		std::string header = "<body>\n  <h3>" + name_ + "</h3>\n" + HTMLbutton + "<pre>\n";

		std::ofstream myfile;
		myfile.open(output);
		myfile.flush();
		myfile << HTMLformat << header << HTML << endHTML;
		myfile.close();

		std::cout << "\n  --   " + name_ + " --> " + output;
	}

	// -----< get vector of converted files >---------------


	int Converter::getOffset()
	{
		return offset;
	}

	std::vector<std::string> Converter::getOutPath()
	{
		std::vector<std::string> out;
		int size = names.size();
		for (int i = 0; i < size; ++i) 
		{
			out.push_back(outPath);
		}
		return out;
	}

	std::vector<std::string> Converter::getOutName()
	{
		return names;
	}

}