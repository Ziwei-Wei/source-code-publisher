///////////////////////////////////////////////////////////////////////
// Display.h  add buttons to source code to show/close code          //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////

#include "Display.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../AbstractSyntaxTree/AbstrSynTree.h"
#include <sstream>
#include <iostream>

using namespace Lexer;
using namespace CodeAnalysis;

namespace SourceCodePublisher {

	// -----< constructor and deconstructor >---------------

	Display::Display(int offset_) : offset(offset_) {}
	Display::~Display() {}

	// -----< add comment/function/class buttons to a list of files >---------------

	void Display::convertAll(const std::vector<std::string>& codepath_, const std::vector<std::string>& codename_, const std::vector<std::string>& path_, const std::vector<std::string>& name_)
	{
		if (codepath_.size() != path_.size() || codepath_.size() != name_.size() || codepath_.size() != codename_.size()) 
		{
			std::cout << "\n  Input did not match each other, please check input!" << std::endl;
			return;
		}
		singleCommentPosition.clear();
		multipleCommentPosition.clear();
		classPosition.clear();
		functionPosition.clear();

		std::cout << "\n  Adding display buttons";
		std::cout << "\n  ======================" << std::endl;

		for (std::size_t i = 0; i < codepath_.size(); ++i)
		{
			std::cout << "\n\n  <---" + codename_[i] + "--->";
			recordCommentPosition(codepath_[i], codename_[i]);
			convertComment(path_[i], name_[i]);
			recordScopePosition(codepath_[i], codename_[i]);
			convertScope(path_[i], name_[i]);
			
		}
	}

	// -----< add comment buttons >---------------

	void Display::convertComment(const std::string& path_, const std::string& name_)
	{
		std::cout << "\n\n  Adding buttons for comments, processing...";
		std::ifstream file(path_ + "\\" + name_);
		std::string str;
		std::string newHTML;
		int lineNum = 1;
		int Siter = 0;
		int Miter = 0;
		int Ssize = singleCommentPosition.size();
		int Msize = multipleCommentPosition.size();
		while (std::getline(file, str))
		{
			if (Siter < Ssize && singleCommentPosition[Siter] == lineNum) {
				int start = findFirst(str, "//");
				str = str.substr(0,start) + "<span class=\"toggleCommentDisplay\">" + str.substr(start) + "</span>";
				Siter++;
			}
			else if (Miter < Msize && multipleCommentPosition[Miter].start == lineNum) {
				int start = findFirst(str, "/*");
				str = str.substr(0, start) + "<span class=\"toggleCommentDisplay\">" + str.substr(start);
			}

			if (Miter < Msize && multipleCommentPosition[Miter].end == lineNum) {
				int start = findFirst(str, "*/");
				str = str.substr(0, start + 2) + "</span>" + str.substr(start + 2);
				Miter++;
			}
			newHTML += str + "\n";
			lineNum++;
		}
		std::ofstream newfile(path_ + "\\" + name_);
		newfile.flush();
		newfile << newHTML;
		newfile.close();
	}
	
	int Display::findFirst(const std::string& str_, const std::string& S)
	{
		
		int start = 0;
		if (!str_.empty()) {
			for (size_t i = 0; i < str_.size() - 1; ++i)
			{
				if (str_.substr(i, 2) == S)
				{
					start = i;
					break;
				}
			}
		}

		return start;
	}

	// -----< find position to add button for comment >---------------

	void Display::recordCommentPosition(const std::string& path_, const std::string& name_)
	{
		singleCommentPosition.clear();
		multipleCommentPosition.clear();
		Toker toker;
		toker.doReturnComments(true);

		std::string fqf = path_ + "\\" + name_;
		if (!toker.open(fqf))
		{
			std::cout << "\n can't open \"" << fqf << "\"\n";
			return;
		}
		else
		{
			std::cout << "\n  processing file: \"" << fqf << "\"";
		}

		int lastPosition = 0;
        int curPosition = 0;
		while (!toker.isDone())
		{
			Token tok = toker.getTok();
			curPosition = toker.lineCount();
			if (Toker::isNewLine(tok))
			{
				tok = "newline";
			}
			if (Toker::isMultipleLineComment(tok))
			{
				multipleCommentPosition.push_back(MLCPosition(lastPosition + offset, curPosition + offset));
				std::cout << "\n  found a multi line comment";
			}
			else if (Toker::isSingleLineComment(tok))
			{
				singleCommentPosition.push_back(curPosition + offset);
				std::cout << "\n  found a single line comment";
			}
			lastPosition = curPosition;
		}
		toker.close();
		std::cout << "\n";
	}

	// -----< add buttons for classes and functions >---------------

	void Display::convertScope(const std::string& path_, const std::string& name_)
	{
		std::cout << "\n\n  Adding buttons for classes and functions, processing...";
		std::ifstream file(path_ + "\\" + name_);
		std::string str;
		std::string newHTML;
		int lineNum = 1;
		int Citer = 0;
		int Fiter = 0;
		int Csize = classPosition.size();
		int Fsize = functionPosition.size();
		while (std::getline(file, str))
		{
			if (Citer < Csize && classPosition[Citer].start == lineNum) {
				str = "<span class=\"toggleClassDisplay\">" + str;
			}
			else if (Fiter < Fsize && functionPosition[Fiter].start == lineNum) {
				str = "<span class=\"toggleFunctionDisplay\">" + str;
			}
			if (Citer < Csize && classPosition[Citer].end == lineNum) {
				str = str + "</span>";
				Citer++;
			}
			else if (Fiter < Fsize && functionPosition[Fiter].end == lineNum) {
				str = str + "</span>";
				Fiter++;
			}
			newHTML += str + "\n";
			lineNum++;
		}
		std::ofstream newfile(path_ + "\\" + name_);
		newfile.flush();
		newfile << newHTML;
		newfile.close();
	}

	// -----< find position to add button for class and function >---------------

	void Display::recordScopePosition(const std::string& path_, const std::string& name_)
	{
		classPosition.clear();
		functionPosition.clear();
		std::string fileSpec = FileSystem::Path::getFullFileSpec(path_ + "\\" + name_);
		std::string msg = "Processing file" + fileSpec;

		ConfigParseForCodeAnal configure;
		Parser* pParser = configure.Build();

		std::string name;

		try
		{
			if (pParser)
			{
				name = FileSystem::Path::getName(path_ + "\\" + name_);
				if (!configure.Attach(fileSpec))
				{
					std::cout << "\n  could not open file " << name << std::endl;
					return;
				}
			}
			else
			{
				std::cout << "\n\n  Parser not built\n\n";
				return;
			}

			// save current package name

			Repository* pRepo = Repository::getInstance();
			pRepo->package() = name;

			// parse the package

			while (pParser->next())
			{
				pParser->parse();
			}
			std::cout << "\n  finished parse";

			// final AST operations
			ASTNode* pGlobalScope = pRepo->getGlobalScope();

			// Walk AST
			WalkAST(pGlobalScope);
		}
		catch (std::exception& ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
			std::cout << "\n  exception caught at line " << __LINE__ << " ";
			std::cout << "\n  in package \"" << name << "\"";
		}
		std::cout << "\n";
	}

	//----< record infomation from every node >---------------------------------

	void Display::recordScope(ASTNode* pItem)
	{
		if (pItem->type_ == "class")
		{
			std::cout << "\n  found class " << pItem->name_;
			classPosition.push_back(MLCPosition(pItem->startLineCount_ + offset, pItem->endLineCount_ + offset));
		}
		else if (pItem->type_ == "function")
		{
			std::cout << "\n  found class " << pItem->name_;
			functionPosition.push_back(MLCPosition(pItem->startLineCount_ + offset, pItem->endLineCount_ + offset));
		}
	}

	//----< walk the AST tree >---------------------------------

	void Display::WalkAST(ASTNode* pItem)
	{
		recordScope(pItem);
		//std::cout << "\n  "  << pItem->show();
		auto iter = pItem->children_.begin();
		while (iter != pItem->children_.end())
		{
			WalkAST(*iter);
			++iter;
		}
	}

};
