#ifndef CARDS_INFO_H
#define CARDS_INFO_H

#include "pkginfo.h"
#include "pkgrepo.h"
#include "cards_argument_parser.h"

class Cards_info: public Pkginfo, public Pkgrepo
{
	public:
		Cards_info(const CardsArgumentParser& argParser,const std::string& configFileName);
			
	private:
		const CardsArgumentParser& m_argParser;
};

#endif /* CARDS_INFO_H */
// vim:set ts=2 :
