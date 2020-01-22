#pragma once

#include "types.h"

#define ERROR_ARGUMENTCOUNT	"you have to pass exagtly one argument"
#define FILE_PEOPLES		"/People.csv"
#define ERROR_PEOPLES		"no People.csv file found"
#define FILE_TITLES			"/Titles.csv"
#define ERROR_TITLES		"no Titles.csv file found"
#define FILE_FIRSTNAMES		"/FirstNames.csv"
#define ERROR_FIRSTNAMES	"no FirstNames.csv file found"
#define FILE_LASTNAMES		"/LastNames.csv"
#define ERROR_LASTNAMES		"no LastNames.csv file found"
#define FILE_BLOODLINES		"/Bloodline.csv"
#define ERROR_BLOODLINES	"no Bloodline.csv file found"
#define FILE_RELATIONSHIPS	"/Relationships.csv"
#define ERROR_RELATIONSHIPS	"no Relationships.csv file found"

#define INPUTREQUEST		"Please input Person ID and distance: "
#define FAILEDINPUT			"your input Was denied please try again: "

#define COMMAND_EXIT		"exit"
#define COMMAND_SEXIT		"e"
#define COMMAND_QUIT		"quit"
#define COMMAND_SQUIT		"q"
#define COMMAND_HELP		"help"
#define COMMAND_SHELP		"h"
#define COMMAND_TREE		"tree"
#define COMMAND_PERSON		"person"

#define HELP_QUIT \
"syntax: \"exit\", \"e\", \"quit\", \"q\" | quits the programm."
#define HELP_TREE \
"syntax: \"tree [id] [distance]\" | prints the family tree from the person [id] onto the console"
#define HELP_PERSON \
"syntax: \"person [id]\"          | prints all information to a person"
#define HELP_HELP \
"syntax: \"help [command]\"       | prints the help to the [command]\n"\
"\"help\", \"h\"                    | prints this help\n"\
"\"exit\", \"e\", \"quit\", \"q\"       | quits the programm\n"\
"\"tree\"                         | returns a tree\n"\
"\"person\"                       | returns a person"

#define COM_NOT_FOUND		"command not found type \"help\" for more informations."
#define NOT_ENOUGH_PARAMETER	"not enough parameter"

