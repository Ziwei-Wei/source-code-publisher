/////////////////////////////////////////////////////////////////////
// DirExplorerN.cpp - Naive directory explorer                     //
// ver 1.2                                                         //
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018         //
/////////////////////////////////////////////////////////////////////
//#define TEST_DIREXPLORERN 
#ifdef TEST_DIREXPLORERN  // only compile the following when defined

#include "DirExplorerN.h"
#include "StringUtilities.h"
#include "CodeUtilities.h"



using namespace Utilities;
using namespace FileSystem;

ProcessCmdLine::Usage customUsage()
{
  std::string usage;
  usage += "\n  Command Line: path [/option]* [/pattern]*";
  usage += "\n    path is relative or absolute path where processing begins";
  usage += "\n    [/option]* are one or more options of the form:";
  usage += "\n      /s - walk directory recursively";
  usage += "\n    [pattern]* are one or more pattern strings of the form:";
  usage += "\n      *.h *.cpp *.cs *.txt or *.*";
  usage += "\n";
  return usage;
}

int main(int argc, char *argv[])
{
  Title("Demonstrate DirExplorer-Naive, " + DirExplorerN::version());

  ProcessCmdLine pcl(argc, argv);
  pcl.usage(customUsage());

  preface("Command Line: ");
  pcl.showCmdLine();
  putline();

  if (pcl.parseError())
  {
    pcl.usage();
    std::cout << "\n\n";
    return 1;
  }

  DirExplorerN de(pcl.path());
  for (auto patt : pcl.patterns())
  {
    de.addPattern(patt);
  }

  if (pcl.hasOption('s'))
  {
    de.recurse();
  }

  de.search();
  de.showStats();

  std::cout << "\n\n";
  system("pause");

  std::vector<std::string> paths = de.getPath();
  std::vector<std::string> names = de.getNames();
  for (unsigned int i = 0; i < paths.size(); ++i)
  {
	  std::cout << "\n  saved " + paths[i] + "\\" + names[i] << std::endl;
  }

  std::cout << "\n\n";
  std::cout << "\n  Demonstrating end";
  std::cout << "\n  =================";
  system("pause");
  return 0;
}

#endif