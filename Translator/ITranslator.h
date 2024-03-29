#pragma once
/////////////////////////////////////////////////////////////////
// ITranslator.h - Translates managed calls into native calls  //
//                                                             //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2019   //
/////////////////////////////////////////////////////////////////
/*
 * This package is responsible for translating managed types into
 * native types and for delegating managed calls to native calls.
 *
 * This file declares an interface and object factory for C# clients
 * to use, isolating them from the Translator implementation.
 * 
 * For C# clients to use this package it needs to be built as a dll,
 * and clients need to make a reference to the Translator project.
 *
 * In order to create a C++\CLI project you need to have installed
 * C++\CLI support.  See CSE687\Presentations\CreatingCppCli.pdf.
 */
using namespace System;
using namespace System::Collections::Generic;

public ref class ITranslator abstract
{
public:
  virtual void convert(List<String^>^ addresses_, String^ output_, bool addDisplay_, bool addDependency_) = 0;
  virtual void convert(String^ path_, String^ output_, bool recurive_, bool addDisplay_, bool addDependency_) = 0;
  virtual void demonstrate(List<String^>^ addresses_) = 0;
};

public ref class TranslatorFactory
{
public:
  static ITranslator^ createTranslator();
};

