#include <list>
using namespace std;

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstdio>

#include "process.h"
#include "string_utils.h"

// using namespace StringHelper;

process::process( const string& app, const string& arguments, int fdlog )
	: application( app ), arguments( arguments ), fileDescriptorLog ( fdlog )
{
}

int process::execute()
{
	list<string> args;
	split( arguments, ' ', args, 0, false );

	const int argc = 1 + args.size() + 1; // app, args, NULL

	char** argv = new char*[argc];
	list<string>::iterator it = args.begin();

	int i = 0;
	argv[i] = const_cast<char*>( application.c_str() );
	for ( ; it != args.end(); ++it )
	{
		++i;
		argv[i] = const_cast<char*>( it->c_str() );
	}

	++i;
	assert( i+1 == argc );
	argv[i] = NULL;
	int status = 0;

	if ( fileDescriptorLog > 0 )
	{
		status = execLog(argc, argv);
	}
	else
	{
		status = exec(argc, argv);
	}
	delete [] argv;
	return status;
}

int process::execLog(const int argc, char** argv)
{
	int status = 0;
	int fdpipe[2];
	pipe( fdpipe );

	pid_t pid = fork();
	if ( pid == 0 )
	{
		// child process
		close( fdpipe[0] );
		dup2( fdpipe[1], STDOUT_FILENO );
		dup2( fdpipe[1], STDERR_FILENO );

		execv( application.c_str(), argv );
		_exit( EXIT_FAILURE );
	}
	else if ( pid < 0 )
	{
		// fork failed
		status = -1;
	}
	else
	{
		// parent process
		close( fdpipe[1] );

		char readbuf[1024];
		int bytes, wpval;

		while ( (wpval = waitpid ( pid, &status, WNOHANG )) == 0 )
		{
			while ( (bytes=read(fdpipe[0], readbuf, sizeof(readbuf)-1)) > 0 )
			{
				readbuf[bytes] = 0;
				printf("%s", readbuf);
				fflush(stdout);
				fflush(stderr);
				write( fileDescriptorLog, readbuf, bytes );
			}
		}
		close( fdpipe[0] );

		if ( wpval != pid )
		{
			status = -1;
  	}
  }
	return status;
}

int process::exec(const int argc, char** argv)
{
	int status = 0;
	pid_t pid = fork();
	if ( pid == 0 )
	{
		// child process
		execv( application.c_str(), argv );
		_exit( EXIT_FAILURE );
	}
	else if ( pid < 0 )
	{
		// fork failed
		status = -1;
	}
	else
	{
		// parent process
		if ( waitpid ( pid, &status, 0 ) != pid )
		{
			status = -1;
		}
	}
	return status;
}

int process::executeShell()
{
	// TODO: make shell exchangable
	static const char SHELL[] = "/bin/sh";
	int status = 0;
	if ( fileDescriptorLog > 0 )
	{
		status = execShellLog(SHELL);
	}
	else
	{
		status = execShell(SHELL);
	}
	return status;
}

int process::execShellLog(const char* SHELL)
{
	int status = 0;

	int fdpipe[2];
  pipe( fdpipe );

	pid_t pid = fork();
	if ( pid == 0 )
	{
		// child process
		close( fdpipe[0] );
		dup2( fdpipe[1], STDOUT_FILENO );
		dup2( fdpipe[1], STDERR_FILENO );

		execl( SHELL, SHELL, "-c", (application + " " + arguments).c_str(), NULL );
		_exit( EXIT_FAILURE );
	}
	else if ( pid < 0 )
	{
		// fork failed
		status = -1;
	}
	else
	{
		// parent process
		close( fdpipe[1] );

		char readbuf[1024];
		int bytes, wpval;

		while ( (wpval = waitpid ( pid, &status, WNOHANG )) == 0 )
		{
			while ( (bytes=read(fdpipe[0], readbuf, sizeof(readbuf)-1)) > 0 )
			{
				readbuf[bytes] = 0;
				printf("%s", readbuf);
				fflush(stdout);
				fflush(stderr);
				write( fileDescriptorLog, readbuf, bytes );
			}
		}
		close( fdpipe[0] );

		if ( wpval != pid )
		{
			status = -1;
		}
  }
	return status;
}

int process::execShell(const char* SHELL)
{
	int status = 0;

	pid_t pid = fork();
	if ( pid == 0 )
	{
		execl( SHELL, SHELL, "-c", (application + " " + arguments).c_str(), NULL );
		_exit( EXIT_FAILURE );
	}
	else if ( pid < 0 )
	{
		// fork failed
		status = -1;
	}
	else
	{
		// parent process
		if ( waitpid ( pid, &status, 0 ) != pid )
		{
			status = -1;
		}
	}
	return status;
}
// vim:set ts=2 :
