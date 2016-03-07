#include "pkgrm.h"
#include <unistd.h>
#include <stdio.h>

Pkgrm::Pkgrm ()
	: Pkgdbh("pkgrm")
{
}
void Pkgrm::run(int argc, char** argv)
{
	parseArguments(argc, argv);
	run();
	finish();
}
void Pkgrm::run()
{
	// Check UID
	if (getuid())
	{
		m_actualError = ONLY_ROOT_CAN_INSTALL_UPGRADE_REMOVE;
		treatErrors("");
	}

	Db_lock lock(m_root, true);

	// Get the list of installed packages
	getListOfPackageNames(m_root);

	// Retrieve info about all the packages
	buildDatabaseWithDetailsInfos(false);

	if (!checkPackageNameExist(m_packageName))
	{
		m_actualError = PACKAGE_NOT_INSTALL;
		treatErrors(m_packageName);
	}

	// Remove metadata about the package removed
	removePackageFilesRefsFromDB(m_packageName);

	// Remove the files on hd
	removePackageFiles(m_packageName);
}
void Pkgrm::printHelp() const
{
	cout << USAGE << m_utilName << " [options] <package>" << endl
	     << OPTIONS << endl
	     << "  -r, --root <path>   specify alternative installation root" << endl
	     << "  -v, --version       print version and exit" << endl
	     << "  -h, --help          print help and exit" << endl;
}
// vim:set ts=2 :
