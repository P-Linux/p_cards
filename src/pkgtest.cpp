#include "pkgtest.h"

Pkgtest::Pkgtest()
	:Pkginfo("pkgtest"), Pkgrepo("/etc/cards.conf")
{
}
void Pkgtest::parseArguments(int argc, char** argv)
{
	m_root="/";
	m_epoc=1;
	m_arg="gcc";
}
void Pkgtest::printHelp() const
{
	cout << USAGE << m_utilName << " [options] <package>" << endl
	<< OPTIONS << endl
	<< "  -r, --root <path>   specify alternative installation root" << endl
	<< "  -v, --version       print version and exit" << endl
	<< "  -h, --help          print help and exit" << endl;

}
