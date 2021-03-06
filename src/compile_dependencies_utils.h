#ifndef CARDS_DEPENDS_H
#define CARDS_DEPENDS_H

#include <string>
#include <list>
#include <map>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <locale.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

#include <dirent.h>
#include "string_utils.h"
#include "cards_argument_parser.h"

/* depList is a dependances List */
typedef struct
{
	unsigned int *depsIndex;
	int *niveau; /* To show a nice incrementation */
	unsigned int count;
	unsigned int decrement; /* number of removed dep when searching them */
	int decount;
} depList;

/* pkgInfo is the name of a package and the dependencies itemList */
typedef struct
{
	unsigned int nameIndex;
	depList *dependences;
	int niveau;
} pkgInfo;

typedef struct
{
	pkgInfo **pkgs;
	unsigned int count;
} pkgList;


/*** depList: Create the list, Add dependence to the list, free the list  ***/
depList *initDepsList(void);
void addDepToDepList(depList *list, unsigned int nameIndex, int niveau);
void freeDepList(depList *list);

/*** pkgInfo: create the pkg, Add info, free the pkgInfo  ***/
pkgInfo *initPkgInfo(void);
pkgInfo *addInfoToPkgInfo(unsigned int nameIndex);
void freePkgInfo(pkgInfo *package);

/*** pkgList: create the pkgList, add pkgs, free the pkgList ***/
pkgList *initPkgList(void);
void addPkgToPkgList(pkgList *list, pkgInfo *package);
void freePkgList(pkgList *packagesList);

int deps_direct (itemList *filesList, pkgList *packagesList, depList *dependenciesList,unsigned int niveau);
int deps_direct (itemList *filesList, pkgList *packagesList, depList *dependenciesList,const char* pkgName, unsigned int niveau);

void generate_level ( itemList *filesList, pkgList *packagesList, unsigned int *niveau);

char *getLongPackageName(itemList *filesList, const char * packageName);
#endif
// vim:set ts=2 :
