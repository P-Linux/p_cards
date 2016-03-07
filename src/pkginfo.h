#ifndef PKGINFO_H
#define PKGINFO_H

#include "file_utils.h"
#include "pkgdbh.h"
#include "runtime_dependencies_utils.h"
#include "file_utils.h"

class Pkginfo : public Pkgdbh {
public:
	Pkginfo(const std::string& commandName);
	Pkginfo();
	virtual void run(int argc, char** argv);
	virtual void parseArguments(int argc, char** argv);
	virtual void run();
	virtual void finish();
	virtual void printHelp() const;

protected:
	std::string m_arg;
	int m_runtimedependencies_mode;
	int m_footprint_mode;
	int m_archiveinfo;
	int m_installed_mode;
	int m_list_mode;
	int m_owner_mode;
	int m_details_mode;
	int m_libraries_mode;
	int m_runtime_mode;
	int m_epoc;

};

#endif /* PKGINFO_H */

// vim:set ts=2 :
