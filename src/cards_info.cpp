#include "cards_info.h"

Cards_info::Cards_info(const CardsArgumentParser& argParser, const std::string& configFileName)
	: Pkginfo("cards info"),Pkgrepo(configFileName), m_argParser(argParser)
{
	if (m_argParser.isSet(CardsArgumentParser::OPT_ROOT))
		m_root=m_argParser.getOptionValue(CardsArgumentParser::OPT_ROOT);

	if (m_root.empty())
		m_root="/";
	else
		m_root=m_root+"/";
	if ((m_argParser.command() == CardsArgumentParser::CMD_INFO) ) {
		if (m_argParser.isSet(CardsArgumentParser::OPT_BINARIES)) {
			getBinaryPackageInfo(m_argParser.otherArguments()[0]);
		} else if (m_argParser.isSet(CardsArgumentParser::OPT_PORTS)) {
			getPortInfo(m_argParser.otherArguments()[0]);
		} else {
			m_details_mode=1;
			m_arg=m_argParser.otherArguments()[0];
			run();
		}
	}
	if ((m_argParser.command() == CardsArgumentParser::CMD_LIST) ) {
		if (m_argParser.isSet(CardsArgumentParser::OPT_BINARIES)) {
			getBinaryPackageList();
		} else if (m_argParser.isSet(CardsArgumentParser::OPT_PORTS)) {
			getPortsList();
		} else {
			m_installed_mode=1;
			run();
		}
	}
	if ((m_argParser.command() == CardsArgumentParser::CMD_QUERY) ) {
		m_owner_mode=1;
		m_arg=m_argParser.otherArguments()[0];
		run();
	}
	if ((m_argParser.command() == CardsArgumentParser::CMD_FILES) ) {
		m_list_mode=1;
		m_arg=m_argParser.otherArguments()[0];
		run();		
	}
	if ((m_argParser.command() == CardsArgumentParser::CMD_SEARCH) ) {
		search(m_argParser.otherArguments()[0]);
	}
}
// vim:set ts=2 :
