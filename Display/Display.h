#pragma once
///////////////////////////////////////////////////////////////////////
// Display.h  add buttons to source code to show/close code          //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher                                //
// Author:      Ziwei Wei                                            //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This Package takes addresses of .cpp.html and .h.html files and their
 * correspounding sourcefile as input, and produce web pages with buttons in it.
 *
 * Required Files:
 * ---------------
 * Display.h  Display.cpp
 * Parser.h  Parser.cpp
 * Toker.h  Toker.cpp
 * FileSystem.h  FileSystem.cpp
 * AbstrSynTree.h AbstrSynTree.cpp
 * ActionsAndRules.h
 * ConfigureParser.h
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 01 Mar, 2019
 */

#include "../Parser/Parser.h"
#include "../Tokenizer/Toker.h"
#include "../FileSystem/FileSystem.h"
#include "../AbstractSyntaxTree/AbstrSynTree.h"

using namespace CodeAnalysis;

namespace SourceCodePublisher {

	// MLC means multiple line count position
	struct MLCPosition
	{
		int start;
		int end;
		MLCPosition(int start_, int end_) : start(start_), end(end_) {}
	};

	class Display
	{
	public:
		static std::string version() { return "ver 1.1"; }

		Display(int offset_);
		~Display();

		// convert function

		void convertAll(const std::vector<std::string>& codepath_, const std::vector<std::string>& codename_, const std::vector<std::string>& path_, const std::vector<std::string>& name_);
		void convertComment(const std::string& path_, const std::string& name_);
		void convertScope(const std::string& path_, const std::string& name_);

		// record function

		void recordCommentPosition(const std::string& path_, const std::string& name_);
		void recordScopePosition(const std::string& path_, const std::string& name_);
		void recordScope(ASTNode* pItem);
		void WalkAST(ASTNode* pItem);

	private:
		//helper functiion
		int findFirst(const std::string& str_, const std::string& S);

		int offset;
		std::vector<MLCPosition> classPosition;
		std::vector<MLCPosition> functionPosition;
		std::vector<int> singleCommentPosition;
		std::vector<MLCPosition> multipleCommentPosition;
	};
};
