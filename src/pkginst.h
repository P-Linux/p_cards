#ifndef PKGINST_H
#define PKGINST_H

#include "pkgdbh.h"
#include "pkgadd.h"
#include "pkgrepo.h"
#include "process.h"

class Pkginst : public Pkgadd, public Pkgrepo {
public:
	Pkginst(const std::string& commandName,const std::string& configFileName);
	void generateDependencies(const pair<std::string,time_t>& packageName);
	void generateDependencies();

protected:
	vector<string> m_dependenciesList;
};
#endif /* PKGINST_H */
// vim:set ts=2 :
