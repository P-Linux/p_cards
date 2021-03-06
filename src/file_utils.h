#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "md5.h"
#include "string_utils.h"
#include "system_utils.h"

#include <fstream>
#include <cstdio>
#include <ext/stdio_filebuf.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/param.h>
#include <libgen.h>
#include <unistd.h>
#include <dirent.h>
#include <regex.h>
#include <err.h>

#define S_CARDS_MODE  0755

#define WS_NONE         0
#define WS_RECURSIVE    (1 << 0)
#define WS_DEFAULT      WS_RECURSIVE
#define WS_FOLLOWLINK   (1 << 1)        /* follow symlinks */
#define WS_DOTFILES     (1 << 2)        /* per unix convention, .file is hidden */
#define WS_MATCHDIRS    (1 << 3)        /* if pattern is used on dir names too */

enum {
        WALK_OK = 0,
        WALK_BADPATTERN,
        WALK_NAMETOOLONG,
        WALK_BADIO
};

struct InfoFile
{
	std::string url;
	std::string filename;
	std::string dirname;
	std::string md5sum;
	long int filetime;
	utimbuf acmodtime;
	FILE *stream;
};

struct DirUrl {
	std::string Dir;
	std::string Url;
};

struct Config {
	Config() {}
	std::string collection;
	std::string name;
	std::string version;
	std::string arch;
	std::string logdir;
	std::vector<std::string> locale;
	std::vector<DirUrl> dirUrl;
	std::vector<std::string> baseDir;
};

using namespace std;
int getConfig(const string& fileName, Config& config);
FILE *openFile(const char *fileName);
void * getDatas ( void * var, FILE * file, long offset, size_t size, size_t nmemb);
string trimFileName(const string& filename);
string modifyTimeFile(const string& filename);
bool checkFileExist(const string& filename);
bool checkFileEmpty(const string& filename);
bool checkRegularFile(const string& filename);
bool checkFilesEqual(const string& file1, const string& file2);
bool checkPermissionsEqual(const string& file1, const string& file2);
bool createRecursiveDirs(const string& pathname);
void cleanupMetaFiles(const string& basedir);
void removeFile(const string& basedir, const string& filename);
int copyFile(const char *  destFile, const char *  origFile);
int findFile(set<string>& filesList, const string& basedir);
int findDir(itemList *filenameList, const char *path);
int findRecursiveFile(set<string>& filenameList, char *filename, regex_t *reg, int spec);
int readFileStripSpace(itemList *fileContent, const char *fileName);
int readFile(itemList *fileContent, const char *fileName);
int parseFile(set<string>& fileContent, const char* fileName);
int parseFile(vector<string>& fileContent, const char* fileName);
bool findMD5sum(const string& fileName, unsigned char* result);
bool checkMD5sum(const char * fileName, const char * MD5Sum);
/* read a file
   return it into a template container */
template <class T>
int parseFile( T& target, const char* fileName)
{
	FILE *fp = NULL;
	if (( fp = openFile (fileName)) == NULL ) {
		return -1;
	}
	const int length = BUFSIZ;
	char input[length];
	string line;
	while (fgets(input, length, fp)) {
		input[strlen(input)-1] = '\0';
		line = input;
		target.push_back(line);
	}
	fclose(fp);
	return 0;
}


#endif /* FILE_UTILS_H */
// vim:set ts=2 :
