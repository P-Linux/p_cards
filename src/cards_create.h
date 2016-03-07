#ifndef CARDS_CREATE_H
#define CARDS_CREATE_H

#include "pkginst.h"
#include "cards_argument_parser.h"

class Cards_create : public Pkginst
{
	public:
		Cards_create(const CardsArgumentParser& argParser,
			const std::string& configFileName,
			const std::vector<string>& listOfPackages);
		Cards_create(const CardsArgumentParser& argParser,
			const std::string& configFileName,
			const std::string& packageName);
		void parseArguments();
			
	private:
		void createBinaries(const string& configFileName,
			const string& packageName);
		const CardsArgumentParser& m_argParser;
};

#endif /* CARDS_CREATE_H */ 
