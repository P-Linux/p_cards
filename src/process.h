#ifndef PROCESS_H
#define PROCESS_H

#include "system_utils.h"
  
/* To execute a process 
	Arguments:
	1. Application to run
	2. Arguments to pass to the application
	3. File descriptor of the log file 
*/

class process
{
public:
	process( const std::string& app, const std::string& args, int fileDescriptorLog=0 );
	/* execute the process
		return the exit status of the application */
	int execute();
	/* execute the process using the shell 
	return the exit status of the application */
	int executeShell();

private:

	int exec(const int argc, char** argv);
	int execLog(const int argc, char** argv);

	int execShell(const char* shell);
	int execShellLog(const char* shell);

	string application;
	string arguments;
	int fileDescriptorLog;
};

#endif /* _PROCESS_H_ */
// vim:set ts=2 :
