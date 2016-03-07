#include "cards_remove.h"
#include "pkgrepo.h"

Cards_remove::Cards_remove(const string& commandName,
	const CardsArgumentParser& argParser,
	const std::string& configFileName)
	: Pkgrm(commandName),m_argParser(argParser)
{
	if (m_argParser.isSet(CardsArgumentParser::OPT_ROOT))
		m_root=m_argParser.getOptionValue(CardsArgumentParser::OPT_ROOT);

	if (m_root.empty())
		m_root="/";
	else
		m_root=m_root+"/";

	if (!m_argParser.isSet(CardsArgumentParser::OPT_ALL)){
		set<string> basePackagesList;
		Config config;
		Pkgrepo::parseConfig(configFileName, config);
		for (auto i : config.baseDir) {
			if ( findFile(basePackagesList, i) != 0 ) {
				m_actualError = CANNOT_READ_DIRECTORY;
				treatErrors(i);
			}
		}	
		if (basePackagesList.empty())
			throw runtime_error("No package found for the base System" );
		
		for ( auto i : m_argParser.otherArguments() ) {
			bool found = false;
			for (auto j : basePackagesList) {
				if ( i == j) {
					found = true;
					break;
				}
			}
			if (found){	
				cout << "The package '" << i 
					<< "' is in the base list" << endl;
				cout << "   specify -a to remove it anyway" << endl;  
				continue;
			}
			
			m_packageName = i;
			run();
		}
	} else {
		for ( auto i : m_argParser.otherArguments() ) {
			m_packageName = i;
			run();
		}
	}
	finish();
}
