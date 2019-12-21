/////////////////////////////////////////////////////////////////
// Translator.cpp - Translates managed calls into native calls //
//                                                             //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2019   //
/////////////////////////////////////////////////////////////////

#include "ITranslator.h"
#include "../NativeCpp/INativeCpp.h"
#include "../Executive/IExecutive.h"

using namespace System;
using namespace System::Text;

public ref class Translator : ITranslator
{
public:
	Translator()
	{
		pCodeConverter = createCodeConverter();
	}
	~Translator()
	{
		delete pCodeConverter;
		pCodeConverter = nullptr;
	}

	void convert(List<String^>^ addresses_, String^ output_, bool addDisplay_, bool addDependency_) override {
		pCodeConverter->convert(mToN(addresses_), mToN(output_), addDisplay_, addDependency_);
	}
	void convert(String^ path_, String^ output_, bool recurive_, bool addDisplay_, bool addDependency_) override {
		pCodeConverter->convert(mToN(path_), mToN(output_), recurive_, addDisplay_, addDependency_);
	}
	void demonstrate(List<String^>^ addresses_) override {
		pCodeConverter->demonstrate(mToN(addresses_));
	}
private:
	std::string mToN(String^ str);
	String^ nToM(const std::string& str);
	std::vector<double> mToN(List<double>^ listDbls);
	List<double>^ nToM(const std::vector<double>& vecDbls);
	std::vector<std::string> mToN(List<String^>^ listStr);
	List<String^>^ nToM(const std::vector<std::string>& vecStr);

	IcodeConverter* pCodeConverter = nullptr;
};

ITranslator^ TranslatorFactory::createTranslator()
{
	return gcnew Translator();
}

std::string Translator::mToN(String^ str)
{
	std::string temp;
	for (int i = 0; i < str->Length; ++i)
		temp += char(str[i]);
	return temp;
}

String^ Translator::nToM(const std::string& str)
{
	StringBuilder^ sb = gcnew StringBuilder();
	for (size_t i = 0; i < str.size(); ++i)
		sb->Append((wchar_t)str[i]);
	return sb->ToString();
}

std::vector<double> Translator::mToN(List<double>^ dbls)
{
	std::vector<double> temp;
	for (int i = 0; i < dbls->Count; ++i)
		temp.push_back(dbls[i]);
	return temp;
}

List<double>^ Translator::nToM(const std::vector<double>& dbls)
{
	List<double>^ temp = gcnew List<double>();
	for (size_t i = 0; i < dbls.size(); ++i)
		temp->Add(dbls[i]);
	return temp;
}

std::vector<std::string> Translator::mToN(List<String^>^ listStr) {
	std::vector<std::string> temp;
	int i = 0;
	String^ str;
	std::string tempstr;
	for (i = 0; i < listStr->Count; ++i)
		str = listStr[i];
		tempstr.clear();
		for (int j = 0; j < str->Length; ++j)
			tempstr += char(str[j]);
		temp.push_back(tempstr);
	return temp;
}
List<String^>^ Translator::nToM(const std::vector<std::string>& vecStr) {
	List<String^>^ temp = gcnew List<String^>();
	StringBuilder^ sb = gcnew StringBuilder();
	size_t i = 0;
	for (i = 0; i < vecStr.size(); ++i)
		sb->Clear();
		for (size_t j = 0; j < vecStr[i].size(); ++j)
			sb->Append((wchar_t)vecStr[i][j]);
		temp->Add(sb->ToString());
	return temp;
}

#include <iostream>

int main(array<System::String ^> ^args)
{
	return 0;
}
