#ifndef PKGADD_H
#define PKGADD_H

#include "string_utils.h"
#include "pkgdbh.h"

class Pkgadd : public Pkgdbh {
public:
	Pkgadd();
	Pkgadd(const std::string& commandName);
	void parseArguments(int argc, char** argv);
	void preRun();
	void postRun();
	virtual void run();
	virtual void run(int argc, char** argv);
	virtual void printHelp() const;

protected:
	bool m_runPrePost;
	bool m_upgrade;
	bool m_force;
private:
	set<string> getKeepFileList(const set<string>& files,
		const vector<rule_t>& rules);
	set<string> applyInstallRules(const string& name,
		pkginfo_t& info,
		const vector<rule_t>& rules);
	void getInstallRulesList(const vector<rule_t>& rules,
		rule_event_t event,
		vector<rule_t>& found) const;
};

#endif /* PKGADD_H */
// vim:set ts=2 :
