#ifndef PKGTEST_H
#define PKGTEST_H

#include "pkginfo.h"
#include "pkgrepo.h"

class Pkgtest: public Pkginfo, public Pkgrepo
{
public:
	Pkgtest();
	void parseArguments(int argc, char** argv);
	void printHelp() const;
};

#endif /* PKGTEST_H */ 
