#ifndef CARDS_BASE_H
#define CARDS_BASE_H


#include "pkgdbh.h"
#include "cards_argument_parser.h"

class Cards_base : public Pkgdbh
{
private:
	const CardsArgumentParser& m_argParser;

public:
	Cards_base(const CardsArgumentParser& argParser);
	void run(int argc, char** argv);
	void printHelp() const;
};
#endif /* CARDS_BASE_H */
// vim:set ts=2 :
