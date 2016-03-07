#ifndef CARDS_INSTALL_H
#define CARDS_INSTALL_H

#include "pkginst.h"
#include "cards_argument_parser.h"

class Cards_install: public Pkginst
{
	public:
		Cards_install(const CardsArgumentParser& argParser,
			const std::string& configFileName);

		/* To install the dependencies of a package
		 * created with cards create command
		 */
		Cards_install(const CardsArgumentParser& argParser,
			const std::string& configFileName,
			const std::vector<string>& listOfPackages);
			
	private:
		const CardsArgumentParser& m_argParser;
		void parseArguments();
		void getLocalePackagesList();
		Config m_config;

};

#endif /* CARDS_INSTALL_H */ 
