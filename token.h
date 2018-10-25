#pragma once

//------------------------------------------------------------------
//                             token.h
//------------------------------------------------------------------
// structure declaration and constants for a token

#include <string>
#include "StringTableEntry.h"

// token: represents a single word/symbol/identifier/literal from the source.
struct token {
	int	tokId;	          // token identifier: one of the TOK_ constants below
	StringTableRef	sref; // reference to an entry in the String Table
};

// prototype for printToken() function
void printToken(token tok);



// other Token Ids (TOK# = 0 refers to TOK_AND)
const int NUM_OTHER_TOKIDS = 7;

const std::string OTHER_TOKIDS[NUM_OTHER_TOKIDS] = {
	"_uh_oh_zero", "_SCANERR", "_ENDSRC", "_IDENT", "_INT_LIT", "_REAL_LIT", "_CHAR_LIT"
};

const int TOK_SCANERR = -1;
const int TOK_ENDSRC = -2;
const int TOK_IDENT = -3;
const int TOK_INT_LIT = -4;
const int TOK_REAL_LIT = -5;
const int TOK_CHAR_LIT = -6;



// Reserved Words & Tokens

const int NUM_RES_WORDS = 70;

const std::string RES_WORDS[NUM_RES_WORDS] = {
	"AND", "ARRAY", "BEGIN", "BOOLEAN", "CASE", "CHAR", "CONST", "DIV", "DO",
	"DOWNTO", "ELSE", "END", "EOF", "FALSE", "FILE", "FOR", "FUNCTION", "GOTO",
	"IF", "IN", "INTEGER", "LABEL", "MAXINT", "MOD", "NIL", "NOT", "OF", "OR",
	"OUTPUT", "PACK", "PACKED", "PROCEDURE", "PROGRAM", "READ", "READLN", "REAL",
	"RECORD", "REPEAT", "SET", "THEN", "TO", "TRUE", "TYPE", "UNTIL", "VAR",
	"WHILE", "WITH", "WRITE", "WRITELN",
	".", "(", ")", "*", ":", "<", ">", "=", "+", "-", "/", "[", "]", ",", ";", "^"
	"<>", "<=", ">=", ":=", ".."
};

const int TOK_AND = 0;
const int TOK_ARRAY = 1;
const int TOK_BEGIN = 2;
const int TOK_BOOLEAN = 3;
const int TOK_CASE = 4;
const int TOK_CHAR = 5;
const int TOK_CONST = 6;
const int TOK_DIV = 7;
const int TOK_DO = 8;
const int TOK_DOWNTO = 9;
const int TOK_ELSE = 10;
const int TOK_END = 11;
const int TOK_EOF = 12;
const int TOK_FALSE = 13;
const int TOK_FILE = 14;
const int TOK_FOR = 15;
const int TOK_FUNCTION = 16;
const int TOK_GOTO = 17;
const int TOK_IF = 18;
const int TOK_IN = 19;
const int TOK_INTEGER = 20;
const int TOK_LABEL = 21;
const int TOK_MAXINT = 22;
const int TOK_MOD = 23;
const int TOK_NIL = 24;
const int TOK_NOT = 25;
const int TOK_OF = 26;
const int TOK_OR = 27;
const int TOK_OUTPUT = 28;
const int TOK_PACK = 29;
const int TOK_PACKED = 30;
const int TOK_PROCEDURE = 31;
const int TOK_PROGRAM = 32;
const int TOK_READ = 33;
const int TOK_READLN = 34;
const int TOK_REAL = 35;
const int TOK_RECORD = 36;
const int TOK_REPEAT = 37;
const int TOK_SET = 38;
const int TOK_THEN = 39;
const int TOK_TO = 40;
const int TOK_TRUE = 41;
const int TOK_TYPE = 42;
const int TOK_UNTIL = 43;
const int TOK_VAR = 44;
const int TOK_WHILE = 45;
const int TOK_WITH = 46;
const int TOK_WRITE = 47;
const int TOK_WRITELN = 48;
const int TOK_PERIOD = 49;
const int TOK_LEFTPAR = 50;
const int TOK_RIGHTPAR = 51;
const int TOK_STAR = 52;
const int TOK_COLON = 53;
const int TOK_LTHAN = 54;
const int TOK_GTHAN = 55;
const int TOK_EQUAL = 56;
const int TOK_PLUS = 57;
const int TOK_MINUS = 58;
const int TOK_SLASH = 59;
const int TOK_LBRKT = 60;
const int TOK_RBRKT = 61;
const int TOK_COMMA = 62;
const int TOK_SEMIC = 63;
const int TOK_HAT = 64;
const int TOK_NOT_EQ = 65;
const int TOK_LT_EQ = 66;
const int TOK_GT_EQ = 67;
const int TOK_ASSIGN = 68;
const int TOK_DOTDOT = 69;
