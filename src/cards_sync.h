#ifndef CARDS_SYNC_H
#define CARDS_SYNC_H

#include <curl/curl.h>
#include "cards_argument_parser.h"
class Cards_sync
{
public:
	Cards_sync (const CardsArgumentParser& argParser);
	Cards_sync (const CardsArgumentParser& argParser,
		const std::string& url,
		const std::string& directory,
		const std::string& repoFile);
	virtual void treatErrors(const string& s) const;

	void run();
	void purge();
	static const std::string DEFAULT_REPOFILE;
 
	
private:

	unsigned int getLocalPackages(const string& path);
	unsigned int getRemotePackages(const string& pkgrepoFile);

	void deleteFolder(const string& folderName);

	set<string> m_localPackagesList;
	set<string> m_remotePackagesList;
	const std::string m_baseDirectory;
	const std::string m_remoteUrl;
	std::string m_repoFile;
	error m_actualError;

	const CardsArgumentParser& m_argParser;
	
};
#endif /* CARDS_SYNC_H */
// vim:set ts=2 :
