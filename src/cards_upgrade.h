#ifndef CARDS_UPGRADE_H
#define CARDS_UPGRADE_H
#include "pkginst.h"
#include "cards_argument_parser.h"

class Cards_upgrade : public Pkginst {
private:
	set<pair<string,time_t>> m_ListOfPackages;
	const CardsArgumentParser& m_argParser;
public:
	Cards_upgrade(const CardsArgumentParser& argParser,const std::string& configFileName);
	void upgradePackages();
	// show the packages that should be update without upgrade them
	void dry();
	
	// number of updates availables
	void size();
	
	// True if some updates availables
	void Isuptodate();
	void upgrade();
};
#endif /* CARDS_UPGRADE_H */
// vim:set ts=2 :
