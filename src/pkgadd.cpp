#include "file_utils.h"
#include "pkgadd.h"
#include "process.h"

#include <algorithm>

#include <fstream>
#include <iterator>
#include <cstdio>
#include <regex.h>
#include <unistd.h>

Pkgadd::Pkgadd()
	: Pkgdbh("pkgadd"),
	m_runPrePost(true),
	m_upgrade(false),
	m_force(false)
{
}
Pkgadd::Pkgadd(const string& commandName)
	: Pkgdbh(commandName),
	m_runPrePost(true),
	m_upgrade(false),
	m_force(false)
{
}
void Pkgadd::run(int argc, char** argv)
{
	parseArguments(argc, argv);
	run();
	finish();
}
void Pkgadd::parseArguments(int argc, char** argv)
{
	for (int i = 1; i < argc; i++) {
		string option(argv[i]);
		if (option == "-r" || option == "--root") {
			assertArgument(argv, argc, i);
			m_root = argv[i + 1];
			i++;
		} else if (option == "-i" || option == "--ignore") {
			m_runPrePost = false;
		} else if (option == "-u" || option == "--upgrade") {
			m_upgrade = true;
		} else if (option == "-f" || option == "--force") {
			m_force = true;
		} else if (option[0] == '-' || !m_packageArchiveName.empty()) {
			throw runtime_error("invalid option " + option);
		} else {
			m_packageArchiveName = option;
		}
	}
	if (m_packageArchiveName.empty()) {
		m_actualError = OPTION_MISSING;
		treatErrors("");
	}
	if (m_root.empty())
		m_root="/";
	else
		m_root=m_root+"/";

	// Check UID
	if (getuid())
	{
		m_actualError = ONLY_ROOT_CAN_INSTALL_UPGRADE_REMOVE;
		treatErrors("");
	}

}
void Pkgadd::preRun()
{
	// Check UID
	if (getuid())
	{
		m_actualError = ONLY_ROOT_CAN_INSTALL_UPGRADE_REMOVE;
		treatErrors("");
	}
	extractAndRunPREfromPackage(m_packageArchiveName);
}
void Pkgadd::run()
{
	// Get the list of installed packages
	getListOfPackageNames(m_root);

	// Retrieving info about all the packages
	buildDatabaseWithDetailsInfos(false);

	// Reading the archiving to find a list of files
	pair<string, pkginfo_t> package = openArchivePackage(m_packageArchiveName);

	// Checking the rules
	readRulesFile();

	bool installed = checkPackageNameExist(package.first);
	if (installed && !m_upgrade)
	{
		m_actualError = PACKAGE_ALLREADY_INSTALL;
		treatErrors (package.first);
	}
	else if (!installed && m_upgrade)
	{
		m_actualError = PACKAGE_NOT_PREVIOUSLY_INSTALL;
		treatErrors(package.first);
	}

	set<string> non_install_files = applyInstallRules(package.first, package.second, m_actionRules);
	if (!m_upgrade) {
#ifndef NDEBUG
		cerr << "Run extractAndRunPREfromPackage without upgrade" << endl;
#endif
		if (m_runPrePost) preRun();
	}
	set<string> conflicting_files = getConflictsFilesList(package.first, package.second);
	if (!conflicting_files.empty()) {
		if (m_force) {
			Db_lock lock(m_root, true);
			set<string> keep_list;
			if (m_upgrade) // Don't remove files matching the rules in configuration
				keep_list = getKeepFileList(conflicting_files, m_actionRules);
			removePackageFilesRefsFromDB(conflicting_files, keep_list); // Remove unwanted conflicts
		} else {
			copy(conflicting_files.begin(), conflicting_files.end(), ostream_iterator<string>(cerr, "\n"));
			m_actualError = LISTED_FILES_ALLREADY_INSTALLED;
			treatErrors("'" + package.first + "'" +": listed file(s) already installed (use -f to ignore and overwrite)");
		}
	}

	set<string> keep_list;
	if (m_upgrade) {
		Db_lock lock(m_root, true);
		removePackageFilesRefsFromDB(package.first);	// Remove metadata about the package removed
		keep_list = getKeepFileList(package.second.files, m_actionRules);
		removePackageFiles(package.first, keep_list);

#ifndef NDEBUG
		cerr << "Run extractAndRunPREfromPackage after upgrade" << endl;
#endif
	}
	if (m_upgrade) {
		if (m_runPrePost) preRun();
	}
	{
		Db_lock lock(m_root, true);
		// Installation progressInfo of the files on the HD
		installArchivePackage(m_packageArchiveName, keep_list, non_install_files);

		// Add the metadata about the package to the DB
		moveMetaFilesPackage(package.first,package.second);

		// Add the info about the files to the DB
		addPackageFilesRefsToDB(package.first, package.second);
	}
	if (m_runPrePost) postRun();
}
void Pkgadd::postRun()
{
	if (checkFileExist(PKG_POST_INSTALL))
	{
		m_actualAction = PKG_POSTINSTALL_START;
		progressInfo();
		process postinstall(SHELL,PKG_POST_INSTALL, 0 );
		if (postinstall.executeShell()) {
			cerr << "WARNING Run post-install FAILED. continue" << endl;
		}
		m_actualAction = PKG_POSTINSTALL_END;
		progressInfo();
		removeFile(m_root,PKG_POST_INSTALL);
	}
}
void Pkgadd::printHelp() const
{
	cout << USAGE << m_utilName << " [options] <file>" << endl
	     << OPTIONS << endl
	     << "  -i, --ignore        do not execute pre/post install scripts" << endl
	     << "  -u, --upgrade       upgrade package with the same name" << endl
	     << "  -f, --force         force install, overwrite conflicting files" << endl
	     << "  -r, --root <path>   specify alternative installation root" << endl
	     << "  -v, --version       print version and exit" << endl
	     << "  -h, --help          print help and exit" << endl;
}

set<string> Pkgadd::getKeepFileList(const set<string>& files,
	const vector<rule_t>& rules)
{
	set<string> keep_list;
	vector<rule_t> found;

	getInstallRulesList(rules, UPGRADE, found);

	for (auto i : files) {
		for (vector<rule_t>::reverse_iterator j = found.rbegin(); j != found.rend(); j++) {
			if (checkRuleAppliesToFile(*j, i)) {
				if (!(*j).action)
					keep_list.insert(keep_list.end(), i);

				break;
			}
		}
	}

#ifndef NDEBUG
	cerr << "Keep list:" << endl;
	for (auto j : keep_list) cerr << "   " << j << endl;
	cerr << endl;
#endif
	return keep_list;
}

set<string> Pkgadd::applyInstallRules(const string& name,
	pkginfo_t& info,
	const vector<rule_t>& rules)
{
	// TODO: better algo(?)
	set<string> install_set;
	set<string> non_install_set;
	vector<rule_t> found;

	getInstallRulesList(rules, INSTALL, found);

	for (auto i : info.files) {
		bool install_file = true;
		for (vector<rule_t>::reverse_iterator j = found.rbegin(); j != found.rend(); j++) {
			if (checkRuleAppliesToFile(*j, i)) {
				install_file = (*j).action;
				break;
			}
		}
		if (install_file)
			install_set.insert(install_set.end(), i);
		else
			non_install_set.insert(i);
	}
	info.files.clear();
	info.files = install_set;

#ifndef NDEBUG
	cerr << "Install set:" << endl;
	for  (auto j : info.files) cerr << "   " << j << endl;
	cerr << endl;
	cerr << "Non-Install set:" << endl;
	for (auto j : non_install_set) cerr << "   " << j << endl;
	cerr << endl;
#endif

	return non_install_set;
}
void Pkgadd::getInstallRulesList(const vector<rule_t>& rules,
	rule_event_t event, 
	vector<rule_t>& found) const
{
	for (auto i : rules ) {
		if (i.event == event)
			found.push_back(i);
	}
}
// vim:set ts=2 :
