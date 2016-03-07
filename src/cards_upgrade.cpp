#include "cards_upgrade.h"
Cards_upgrade::Cards_upgrade(const CardsArgumentParser& argParser,const std::string& configFileName)
	: Pkginst("cards upgrade",configFileName), m_argParser(argParser)
{
	if (m_argParser.isSet(CardsArgumentParser::OPT_ROOT))
		m_root=m_argParser.getOptionValue(CardsArgumentParser::OPT_ROOT);

	if (m_root.empty())
		m_root="/";
	else
		m_root=m_root+"/";

	if (getuid()) {
		m_actualError = ONLY_ROOT_CAN_INSTALL_UPGRADE_REMOVE;
		treatErrors("");
	}

	parsePkgRepoCollectionFile();
	buildDatabaseWithNameVersion();
	for (auto i : m_listOfInstPackages) {
		if (!checkBinaryExist(i.first)) {
			cout << i.first << " not exist" << endl;
			continue;
		}
		pair<string,time_t> packageNameBuildDate;
		packageNameBuildDate.first = i.first ;
		packageNameBuildDate.second = getBinaryBuildTime(i.first);
		if ( checkPackageNameBuildDateSame(packageNameBuildDate)) {
			continue;
		}
		m_ListOfPackages.insert(packageNameBuildDate);
	}
	if ( m_argParser.command() == CardsArgumentParser::CMD_UPGRADE) {
		if ( m_argParser.isSet(CardsArgumentParser::OPT_CHECK))
			Isuptodate();
		if ( m_argParser.isSet(CardsArgumentParser::OPT_SIZE))
			size();
		if ( (! m_argParser.isSet(CardsArgumentParser::OPT_SIZE)) &&
			(! m_argParser.isSet(CardsArgumentParser::OPT_CHECK)) )
			upgrade();
	}
	if ( m_argParser.command() == CardsArgumentParser::CMD_DIFF) {
		dry();
	}
}
void Cards_upgrade::size()
{
	cout << m_ListOfPackages.size() << endl;
}
void Cards_upgrade::Isuptodate()
{
	if ( m_ListOfPackages.size() == 0)
		cout << "no" << endl;
	else
		cout << "yes" << endl;
}
void Cards_upgrade::dry()
{
	for (auto i : m_ListOfPackages ) cout << i.first  << endl;
}
void Cards_upgrade::upgrade()
{
	for (auto i : m_ListOfPackages) generateDependencies(i);

	if (m_argParser.isSet(CardsArgumentParser::OPT_DRY))
		dry();
	else {
		for (auto i : m_dependenciesList) {
			m_packageArchiveName=getPackageFileName(i);
			if (checkPackageNameExist(i)) {
				m_upgrade=1;
			} else {
				m_upgrade=0;
			}
		run();
		}
	}
}
// vim:set ts=2 :
