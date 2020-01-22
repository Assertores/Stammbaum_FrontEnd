#pragma once

#include "types.h"

cString ERROR_ARGUMENTCOUNT = "you have to pass exagtly one argument";
cString FILE_PEOPLES = "/People.csv";
cString ERROR_PEOPLES = "no People.csv file found";
cString FILE_TITLES ="/Titles.csv";
cString ERROR_TITLES = "no Titles.csv file found";
cString FILE_FIRSTNAMES = "/FirstNames.csv";
cString ERROR_FIRSTNAMES = "no FirstNames.csv file found";
cString FILE_LASTNAMES = "/LastNames.csv";
cString ERROR_LASTNAMES = "no LastNames.csv file found";
cString FILE_BLOODLINES = "/Bloodline.csv";
cString ERROR_BLOODLINES = "no Bloodline.csv file found";
cString FILE_RELATIONSHIPS = "/Relationships.csv";
cString ERROR_RELATIONSHIPS = "no Relationships.csv file found";

cString INPUTREQUEST = "Please input Person ID and distance: ";
cString FAILEDINPUT = "your input Was denyed please try again: ";

cString COMMAND_EXIT = "exit";
cString COMMAND_SEXIT = "e";
cString COMMAND_QUIT = "quit";
cString COMMAND_SQUIT = "q";
cString COMMAND_HELP = "help";
cString COMMAND_SHELP = "h";
cString COMMAND_TREE = "tree";
cString COMMAND_PERSON = "person";

cString HELP_QUIT =
"quits the programm.";
cString HELP_TREE =
"syntax: \"tree [id] [distance]\" | prints the family tree from the person [id] onto the console";
cString HELP_PERSON =
"syntax: \"person [id]\"          | prints all information to a person";
cString HELP_HELP =
"syntax: \"help [command]\"       | prints the help to the [command]\n"
"\"help\", \"h\"                    | prints this help\n"
"\"exit\", \"e\", \"quit\", \"q\"       | quits the programm\n"
"\"tree\"                         | returns a tree\n"
"\"person\"                       | returns a person"
;

cString COM_NOT_FOUND = "command not found type \"help\" for more informations.";
