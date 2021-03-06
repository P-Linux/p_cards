#include "string_utils.h"
#include <iostream>
#include <cctype>
#include <fstream>
#include <sys/stat.h>

using namespace std;

void *Malloc(size_t s)
{
	void *p;
	if ( ! ( p = malloc(s) ) ) {
		fprintf(stderr,"Failled to malloc\n");
		if ( errno ) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
	return p;
}


itemList *initItemList(void)
{
	itemList *list = (itemList*)Malloc(sizeof *list);
	list->items = (char **)Malloc(sizeof (*list->items));
	list->count = 0;
	return list;
}

void addItemToItemList(itemList *list, const char *item)
{
	char **realloc_tmp;
	realloc_tmp = (char **)realloc( list->items, sizeof *list->items * (list->count + 1) );
	if ( realloc_tmp == NULL ) {
		return;
	}
	list->items = realloc_tmp;
	list->items[ list->count ] = strdup(item);
	++list->count;
}

void freeItemList(itemList *list)
{
	for (unsigned int i=0; i < list->count;i++) {
		free(list->items[i]);
	}
	free(list->items);
	free(list);
}

keyValue splitKeyValue(string s, char delimiter)
{
	keyValue pv;
	string entry;
  size_t found =  s.find(delimiter);
  if (found != string::npos)
  {
		entry = s;
		entry.erase(s.find(delimiter),s.size());
    pv.parameter=stripWhiteSpace(entry);
		entry = s;
    entry.erase(0,s.find(delimiter)+sizeof(char));
		pv.value=stripWhiteSpace(entry);
  }
  else
  {
    pv.value = "";
  }
  return pv;
}

set<string> getKeysList(string file, string delimiter)
{
  set<string> parameter_list;
  ifstream in(file.c_str());
  string line, property;
  if (in) {
    while (!in.eof()) {
      getline(in, line);
      if ((line[0] != '#' ) && ( line.find(delimiter) > 0) && ( line.size() > 0)) {
        property = line;
        property.erase(property.find(delimiter),property.size());
        parameter_list.insert(property);
      }
    }
  }
  return parameter_list;
}

string getValueOfKey(string file, char delimiter,string parameter)
{
  map<string,string> property_list;
  ifstream in(file.c_str());
  string line;
  keyValue pv;
  if (in) {
    while (!in.eof()) {
      getline(in, line);
			
      if ((line[0] != '#' ) && ( line.find(delimiter) > 0) && ( line.size() > 0)) {
        pv = splitKeyValue(stripWhiteSpace(line),delimiter);
        property_list[pv.parameter]=pv.value;
      }
    }
  }
  return stripWhiteSpace(property_list[parameter]);
}
string getValue( const string& s, char delimiter )
{
	string::size_type pos = s.find( delimiter );
	if ( pos != string::npos && pos+1 < s.length() ) {
		return s.substr( pos + 1 );
	}
	return "";
}
string getValueBefore( const string& s, char del )
{
	string::size_type pos = s.find( del );
	if ( pos != string::npos ) {
		return s.substr( 0, pos );
	}
	return s;
}
string itos(unsigned int value)
{
  static char buf[20];
  sprintf(buf, "%u", value);
  return buf;
}

string ultos(unsigned long int value)
{
	static char buf[20];
	sprintf(buf, "%lu", value);
	return buf;
}
string mtos(mode_t mode)
{
  string s;

  // File type
  switch (mode & S_IFMT) {
        case S_IFREG:  s += '-'; break; // Regular
        case S_IFDIR:  s += 'd'; break; // Directory
        case S_IFLNK:  s += 'l'; break; // Symbolic link
        case S_IFCHR:  s += 'c'; break; // Character special
        case S_IFBLK:  s += 'b'; break; // Block special
        case S_IFSOCK: s += 's'; break; // Socket
        case S_IFIFO:  s += 'p'; break; // Fifo
        default:       s += '?'; break; // Unknown
        }

  // User permissions
        s += (mode & S_IRUSR) ? 'r' : '-';
        s += (mode & S_IWUSR) ? 'w' : '-';
        switch (mode & (S_IXUSR | S_ISUID)) {
        case S_IXUSR:           s += 'x'; break;
        case S_ISUID:           s += 'S'; break;
        case S_IXUSR | S_ISUID: s += 's'; break;
        default:                s += '-'; break;
        }

        // Group permissions
  s += (mode & S_IRGRP) ? 'r' : '-';
        s += (mode & S_IWGRP) ? 'w' : '-';
        switch (mode & (S_IXGRP | S_ISGID)) {
        case S_IXGRP:           s += 'x'; break;
        case S_ISGID:           s += 'S'; break;
  case S_IXGRP | S_ISGID: s += 's'; break;
        default:                s += '-'; break;
        }

        // Other permissions
        s += (mode & S_IROTH) ? 'r' : '-';
        s += (mode & S_IWOTH) ? 'w' : '-';
        switch (mode & (S_IXOTH | S_ISVTX)) {
        case S_IXOTH:           s += 'x'; break;
        case S_ISVTX:           s += 'T'; break;
        case S_IXOTH | S_ISVTX: s += 't'; break;
        default:                s += '-'; break;
        }

  return s;
}
string getFirstValueOfKeyAfterDelim(const string& s, char delimiter)
{
	string::size_type pos = s.find( delimiter );
	if ( pos != string::npos && pos+1 < s.length() )
		return s.substr( pos + 1 );
	return "";
}
string getFirstValueOfKeyBeforeDelim(const string& s, char delimiter)
{
	string::size_type pos = s.find( delimiter );
	if ( pos != string::npos )
		return s.substr( 0, pos );
	return s;
}
vector<string> parseDelimitedList(const string& s, const char delimiter)
{
	vector<string> depList;
	if ( s.empty() )
		return depList;
	string::size_type start = 0, end = 0;
	while (  (end = s.find(delimiter,start)) < string::npos   ) 
	{
		end = s.find(delimiter,start );
		depList.push_back(s.substr( start, end - start ));
		start = end +1;
	}
	depList.push_back(s.substr(start));
	return depList;
}
		
string stripWhiteSpace(const string& s)
{
	if ( s.empty() )
		return s;
	int pos = 0;
	string line = s;
	int len = line.length();
	while ( pos < len && isspace( line[pos] ) ) {
		++pos;
	}
	line.erase( 0, pos );
	pos = line.length()-1;
	while ( pos > -1 && isspace( line[pos] ) ) {
		--pos;
	}
	if ( pos != -1 ) {
		line.erase( pos+1 );
	}
	return line;
}
bool startsWithNoCase(const string& s1, const string& s2)
{
	string::const_iterator p1 = s1.begin();
	string::const_iterator p2 = s2.begin();

	while ( p1 != s1.end() && p2 != s2.end() ) {
		if ( toupper( *p1 ) != toupper( *p2 ) ) {
			return false;
		}
		++p1;
		++p2;
	}
	if ( p1 == s1.end() && p2 != s2.end() ) {
		return false;
	}
	return true;
}
string convertToLowerCase(const string& s)
{
	string result = "";
	for ( string::size_type i = 0; i < s.length(); ++i ) {
		result += tolower( s[i] );
	}
	return result;
}
string convertToUpperCase(const string& s)
{
	string result = "";
	for ( string::size_type i = 0; i < s.length(); ++i ) {
		result += toupper( s[i] );
	}
	return result;
}
string replaceAll( string& in, const string& oldString, const string& newString )
{
	size_t pos;
	while ( (pos = in.find( oldString )) != string::npos ) {
		in = in.replace( pos, oldString.length(), newString );
	}
	return in;
}
// vim:set ts=2 :
