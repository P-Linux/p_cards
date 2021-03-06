#include "pkginst.h"

Pkginst::Pkginst(const string& commandName,const string& configFileName)
	: Pkgadd(commandName), Pkgrepo(configFileName)
{
}
void Pkginst::generateDependencies(const pair<string,time_t>& packageName)
{
	m_packageName=packageName.first;
	generateDependencies();
}
void Pkginst::generateDependencies()
{
	vector< pair<string,time_t> > dependenciesWeMustAdd,depencenciestoSort;
	pair<string,time_t> PackageTime;
	PackageTime.first=m_packageName;
	PackageTime.second=0;
	dependenciesWeMustAdd.push_back(PackageTime);	// Insert the final package first
	dependenciesWeMustAdd.push_back(PackageTime);
	std::vector< pair<string,time_t> >::iterator vit;
	std::set< pair<string,time_t> >::iterator sit;
	while ( ! dependenciesWeMustAdd.empty() ) { // Main WHILE
#ifndef NDEBUG
		for (auto i : dependenciesWeMustAdd) cerr << i.first << " " << i.second << endl;
#endif
		vit = dependenciesWeMustAdd.begin();
		m_packageName = vit->first;
		PackageTime = *vit;
		dependenciesWeMustAdd.erase(vit);   // Erase the current treated package name
		set< pair<string,time_t> > directDependencies;
		if ( m_listOfDepotPackages.find(m_packageName) != m_listOfDepotPackages.end() ) {
#ifndef NDEBUG
			cerr << m_packageName << " found in m_listOfDepotPackages" << endl;
#endif
			directDependencies = m_listOfDepotPackages[m_packageName].dependencies;
#ifndef NDEBUG
			for (auto i : directDependencies ) cerr << i.first << i.second << " ";
#endif
		} else {
#ifndef NDEBUG
			cerr << m_packageName << " not found in m_listOfDepotPackages" << endl;
#endif
			if ( checkBinaryExist(m_packageName)) { // directs deps if not yet availables
#ifndef NDEBUG
				cerr << m_packageName << " binary found " << endl;
#endif
				m_packageFileName = getPackageFileName(m_packageName);
#ifndef NDEBUG
				cerr << m_packageFileName << " archive found " << endl;
#endif
			}
			if ( ! checkFileExist(m_packageFileName)) // Binary Archive not yet downloaded
				downloadPackageFileName(m_packageName); // Get it
#ifndef NDEBUG
			cerr << "getPackageDependencies(" << m_packageFileName << ")" << endl;
#endif
			directDependencies = getPackageDependencies(m_packageFileName);
#ifndef NDEBUG
			for (auto i : directDependencies ) cerr << i.first << " ";
#endif
		}
		if ( ! checkPackageNameBuildDateSame(PackageTime)) // If not yet install or not up to dated
		{
#ifndef NDEBUG
			cerr << "checkPackageNameBuildDateSame no:" <<PackageTime.first << PackageTime.second << endl;
#endif
			depencenciestoSort.push_back(PackageTime); // Add it
		}
#ifndef NDEBUG
			 else
		{
			cerr << "checkPackageNameBuildDateSame yes: " << PackageTime.first << PackageTime.second << endl;
		}
#endif
		for ( sit = directDependencies.begin(); sit != directDependencies.end();sit++) {
			if ( sit->first == PackageTime.first )
				continue;
			for ( vit = dependenciesWeMustAdd.begin(); vit != dependenciesWeMustAdd.end();++vit) {
				if ( *sit == *vit) {
					dependenciesWeMustAdd.erase(vit);
					break;
				}
			}
		}
		for ( sit = directDependencies.begin(); sit != directDependencies.end();sit++) {
			if ( PackageTime.first != sit->first ) {
				if ( ! checkPackageNameBuildDateSame(*sit))
					dependenciesWeMustAdd.push_back(*sit);
			}
		}
	}
	bool found = false ;
	for ( std::vector<pair <string,time_t> >::reverse_iterator vrit = depencenciestoSort.rbegin(); vrit != depencenciestoSort.rend();++vrit) {
		found = false ;
		for (vector<string>::const_iterator i = m_dependenciesList.begin();i != m_dependenciesList.end();i++) {
			if (*i == vrit->first) {
				found = true ;
				break;
			}
		}
		if (!found) {
#ifndef NDEBUG
			cerr << "m_dependenciesList.push_back " << vrit->first << endl;
#endif
			m_dependenciesList.push_back(vrit->first);
		}
#ifndef NDEBUG
		else cerr << "no deps founds" << endl;
#endif
	}
}
// vim:set ts=2 :
