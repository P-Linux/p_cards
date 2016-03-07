#ifndef CARDS_REMOVE_H
#define CARDS_REMOVE_H

#include "pkgrm.h"
#include "cards_argument_parser.h"

class Cards_remove: public Pkgrm
{
	public:
		Cards_remove(const std::string& commandName,
		const CardsArgumentParser& argParser,
		const std::string& configFileName);

	private:
		const CardsArgumentParser& m_argParser;
};

#endif /* CARDS_REMOVE_H */
// vim:set ts=2 :
