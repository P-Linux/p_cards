#ifndef DEPENDENCIES_UTILS_H
#define DEPENDENCIES_UTILS_H


#include "string_utils.h"
#include "elf_common.h"
#include "elf.h"

using namespace std;

int getRuntimeLibrariesList (set<string>& runtimeLibrariesList, const string& filename);

#endif /* DEPENDENCIES_UTILS_H */
// vim:set ts=2 :
