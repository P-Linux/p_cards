#ifndef CARDS_ARGUMENT_PARSER_H
#define CARDS_ARGUMENT_PARSER_H

#include "argument_parser.h"

class CardsArgumentParser : public ArgParser
{
	public:
		CardsArgumentParser();
		virtual ~CardsArgumentParser() {};

		static ArgParser::APCmd CMD_HELP;
		static ArgParser::APCmd CMD_CONFIG;
		static ArgParser::APCmd CMD_BASE;
		static ArgParser::APCmd CMD_FILES;
		static ArgParser::APCmd CMD_SYNC;
		static ArgParser::APCmd CMD_INFO;
		static ArgParser::APCmd CMD_QUERY;
		static ArgParser::APCmd CMD_LIST;
		static ArgParser::APCmd CMD_INSTALL;
		static ArgParser::APCmd CMD_DEPCREATE;
		static ArgParser::APCmd CMD_CREATE;
		static ArgParser::APCmd CMD_REMOVE;
		static ArgParser::APCmd CMD_DIFF;
		static ArgParser::APCmd CMD_LEVEL;
		static ArgParser::APCmd CMD_DEPENDS;
		static ArgParser::APCmd CMD_DEPTREE;
		static ArgParser::APCmd CMD_SEARCH;
		static ArgParser::APCmd CMD_PURGE;
		static ArgParser::APCmd CMD_UPGRADE;

		static ArgParser::APOpt OPT_CHECK;
		static ArgParser::APOpt OPT_SIZE;

		static ArgParser::APOpt OPT_FORCE;
		static ArgParser::APOpt OPT_UPDATE;

		static ArgParser::APOpt OPT_INSTALLED;
		static ArgParser::APOpt OPT_BINARIES;
		static ArgParser::APOpt OPT_PORTS;

		static ArgParser::APOpt OPT_IGNORE;

		static ArgParser::APOpt OPT_DRY;
		static ArgParser::APOpt OPT_REMOVE;
		static ArgParser::APOpt OPT_ALL;
		static ArgParser::APOpt OPT_LEVEL_SILENCE;

		static ArgParser::APOpt OPT_ROOT;
		static ArgParser::APOpt OPT_CONFIG_FILE;

		std::string getAppIdentification() const
		{
			return std::string("cards ")  + VERSION + "\n";
		}
};

#endif
// vim:set ts=2 :
