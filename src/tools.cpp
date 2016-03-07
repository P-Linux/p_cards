#if (__GNUC__ < 4)
#error This program requires GCC 4.x to compile.
#endif

#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <libgen.h>
#include "pkgdbh.h"
#include "pkgadd.h"
#include "pkgrm.h"
#include "pkginfo.h"

using namespace std;

Pkgdbh* select_utility(const string& name)
{
	if (name == "pkgadd")
		return new Pkgadd;
	else if (name == "pkgrm")
		return new Pkgrm;
	else if (name == "pkginfo")
		return new Pkginfo;
	else	
		throw runtime_error("command not supported by cards");
}

int main(int argc, char** argv)
{
	string name = basename(argv[0]);

	try {
		unique_ptr<Pkgdbh> util(select_utility(name));

		// Handle common options
		for (int i = 1; i < argc; i++) {
			string option(argv[i]);
			if (option == "-v" || option == "--version") {
				util->print_version();
				return EXIT_SUCCESS;
			} else if (option == "-h" || option == "--help") {
				util->printHelp();
				return EXIT_SUCCESS;
			}
		}
		util->run(argc, argv);

	} catch (runtime_error& e) {
		cerr << name <<  " " << VERSION << ": " << e.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
// vim:set ts=2 :
