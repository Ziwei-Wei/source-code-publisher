#pragma once
///////////////////////////////////////////////////////////////
// IExecutive.h - Translates managed calls into native calls //
//                                                           //
// Ziwei Wei Spring 2019                                     //
///////////////////////////////////////////////////////////////

#include <vector>

struct IcodeConverter
{
	~IcodeConverter() {}
	virtual void convert(const std::vector<std::string>& addresses_, const std::string& output_, bool addDisplay_ = true, bool addDependency_ = true) = 0;
	virtual void convert(const std::string& path_, const std::string& output_, bool recurive_ = true, bool addDisplay_ = true, bool addDependency_ = true) = 0;
	virtual void demonstrate(const std::vector<std::string>& addresses_) = 0;
};

IcodeConverter* createCodeConverter();