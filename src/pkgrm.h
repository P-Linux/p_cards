#ifndef PKGRM_H
#define PKGRM_H

#include "pkgdbh.h"

class Pkgrm : public Pkgdbh {
public:
	Pkgrm(const std::string& commandName) : Pkgdbh(commandName) {}
	Pkgrm();
	void run();
	void run(int argc, char** argv);
	void printHelp() const;
};

#endif /* PKGRM_H */
// vim:set ts=2 :
