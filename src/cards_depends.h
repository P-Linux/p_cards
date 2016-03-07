#ifndef CARDSDEPENDS_H
#define CARDSDEPENDS_H

#include <locale.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

#include <dirent.h>
#include "string_utils.h"
#include "pkgdbh.h"
#include "cards_argument_parser.h"
#include "compile_dependencies_utils.h"

struct LevelName {
	int l;
	std::string name;
};

class CardsDepends: public Pkgdbh
{
public:

	CardsDepends (const CardsArgumentParser& argParser);

	void parseArguments();

	virtual void treatErrors(const std::string& s) const;

	void showDependencies();
	void showLevel();
	
	std::vector<string>& getDependencies();
	std::vector<string>& getNeededDependencies();
	std::vector<LevelName>& getLevel();

	int deptree();

private:
	/*
	* Populate the List of dependance for each found package.
	* We need to check if each dependance exist if yes add the index reference to the list
	* if not printout a warning message
	* We check for TWO deps files, it's need because some binaries need manual add of deps like
	* xorg-server: xorg-font, may be some perl module, some icons theme what ever those are not
	* found automatically
	* kde: all the necessary apps
	* xfce4: same
	*/
	depList *readDependenciesList(itemList *filesList, unsigned int nameIndex);

	int depends();
	int level();

	std::vector<string> m_dependenciesList;
	std::vector<string> m_neededDependenciesList;
	std::vector<LevelName> m_levelList;
	std::set<string> m_missingDepsList;
	
	const CardsArgumentParser& m_argParser;
	const char* m_packageName;
	error m_actualError;
};
#endif
// vim:set ts=2 :
