#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <fstream>

using namespace std;

class scanner {
public:

	int openSource(string filename);
	int scanNextLex(int & lexLine, int & lexCol, int & lexCat);
	string getLex();
	string getErrMsg();
	int getCol();
	int getLine();
	int getLexCat();
	string getFState(int x);
	string getCCat(int x);

private:

	ifstream f;
	string lex = "";
	string errMsg = "Scanner not initialized\n";
	int line = 1, col = 0;
	bool isErr = true;
	bool firstLexChar = true;
	bool isEOF = false;
	char nextc = '\0';
	int  ccat, lexCat;
	int  prevCol = 0, prevLine = 0;
	void readNextChar();
	int charcat(char c);
	void clearLex();
	void setErrMsg(int & lexLine, int & lexCol, int prevState);
	void addToLex(char nextc, int &lexCol, int &lexLine);
	void catLex();

};



// lexeme categories

int const LC_IDENT    = 1;
int const LC_SYMBOL   = 2;
int const LC_INT_LIT  = 3;
int const LC_REAL_LIT = 4;
int const LC_CHAR_LIT = 5;



// Character Categories: the alphabet of the FSA

int const CC_WHITESP = 0;	// other than newline and EOF
int const CC_PERIOD  = 1;	// single symbols
int const CC_LPAR    = 2;	
int const CC_RPAR    = 3;	
int const CC_STAR    = 4;	
int const CC_COLON   = 5;	
int const CC_LTHAN   = 6;	
int const CC_GTHAN   = 7;	
int const CC_EQUAL   = 8;	
int const CC_QUOTE   = 9;	
int const CC_EOL     = 10;	  // '\n' - end of line
int const CC_EOF     = 11;	  // end of file; not actually returned by iostream getc()
int const CC_ALPHA   = 12;	  // 'a'..'z','A'..'Z'
int const CC_DIGIT   = 13;	  // '0'..'9'
int const CC_SYMBOL  = 14;	  // issymbol() other than those listed above
int const CC_OTHER   = 15;    // c >= ' ' && c < '~' (ASCII 32-125. '~'=126, used to test invalid char

int const CC_UNKNOWN = 16;
const int NUM_CHAR_CATS = 17;

const string CH_CAT[NUM_CHAR_CATS] = {
"CC_WHITESP", "CC_PERIOD","CC_LPAR","CC_RPAR","CC_STAR","CC_COLON","CC_LTHAN","CC_GTHAN",
"CC_EQUAL","CC_QUOTE","CC_EOL","CC_EOF","CC_ALPHA","CC_DIGIT","CC_SYMBOL","CC_OTHER","CC_UNKNOWN" };

// FSA States

const int FS_ERROR = -1;
const int FS_START = 0;
const int FS_IN_COM = 1;
const int FS_END_COM = 2;
const int FS_QUOTE = 3;
const int FS_DEC_PT = 4;
const int FS_IN_CHLIT = 5;
const int FS_DOT1 = 6;
const int FS_DOT2 = 7;
const int FS_LPAR = 8;
const int FS_COLON = 9;
const int FS_ASSIGN = 10;
const int FS_END_CHLIT = 11;
const int FS_IDENT = 12;
const int FS_FRAC = 13;
const int FS_INT_LIT = 14;
const int FS_SYMBOL = 15;
const int FS_LTHAN = 16;
const int FS_LTHANEQ = 17;
const int FS_GTHAN = 18;
const int FS_GTHANEQ = 19;
const int FS_END_LEX = 20;
const int FS_EOF = 21;
const int FS_END_LEX2 = 22;
const int FS_NUM_STATES = 23;



const string FS_STATE[FS_NUM_STATES] = {

"FS_START",  "FS_IN_COM",  "FS_END_COM",  "FS_QUOTE",  "FS_DEC_PT",  "FS_IN_CHLIT",  

"FS_DOT1",  "FS_DOT2",  "FS_LPAR",  "FS_COLON",  "FS_ASSIGN",  "FS_END_CHLIT",  

"FS_IDENT",  "FS_FRAC",  "FS_INT_LIT",  "FS_SYMBOL",  "FS_LTHAN",  "FS_LTHANEQ",  

"FS_GTHAN",  "FS_GTHANEQ",  "FS_END_LEX",  "FS_EOF", "FS_END_LEX2"};



// FSA State Transitions

const int FSA_TRANS[FS_NUM_STATES][NUM_CHAR_CATS] = {

	/*                 CC_WHITESP   CC_PERIOD    CC_LPAR      CC_RPAR      CC_STAR     CC_COLON     CC_LTHAN     CC_GTHAN     CC_EQUAL     CC_QUOTE      CC_EOL      CC_EOF      CC_ALPHA     CC_DIGIT     CC_SYMBOL    CC_OTHER     CC_UNKNOWN  */

	/* FS_START*/    { FS_START,    FS_DOT1,     FS_LPAR,     FS_SYMBOL,   FS_SYMBOL,  FS_COLON,    FS_LTHAN,    FS_GTHAN,    FS_SYMBOL,   FS_QUOTE,     FS_START,   FS_EOF,     FS_IDENT,    FS_INT_LIT,  FS_SYMBOL,   FS_ERROR,    FS_ERROR },

	/* FS_IN_COM*/   { FS_IN_COM,   FS_IN_COM,   FS_IN_COM,   FS_IN_COM,   FS_END_COM, FS_IN_COM,   FS_IN_COM,   FS_IN_COM,   FS_IN_COM,   FS_IN_COM,    FS_IN_COM,  FS_ERROR,   FS_IN_COM,   FS_IN_COM,   FS_IN_COM,   FS_IN_COM,   FS_ERROR },

	/* FS_END_COM*/  { FS_IN_COM,   FS_IN_COM,   FS_IN_COM,   FS_START,    FS_END_COM, FS_IN_COM,   FS_IN_COM,   FS_IN_COM,   FS_IN_COM,   FS_IN_COM,    FS_IN_COM,  FS_ERROR,   FS_IN_COM,   FS_IN_COM,   FS_IN_COM,   FS_IN_COM,   FS_ERROR },

	/* FS_QUOTE*/    { FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT,FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT, FS_END_CHLIT, FS_ERROR,   FS_ERROR,   FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT, FS_ERROR },

	/* FS_DEC_PT*/   { FS_ERROR,    FS_ERROR,    FS_ERROR,    FS_ERROR,    FS_ERROR,   FS_ERROR,    FS_ERROR,    FS_ERROR,    FS_ERROR,    FS_ERROR,     FS_ERROR,   FS_ERROR,   FS_ERROR,    FS_FRAC,     FS_ERROR,    FS_ERROR,    FS_ERROR },

	/* FS_IN_CHLIT*/ { FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT,FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT, FS_END_CHLIT, FS_ERROR,   FS_ERROR,   FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT, FS_IN_CHLIT, FS_ERROR },

	/* FS_DOT1*/     { FS_END_LEX,  FS_END_LEX2, FS_END_LEX,  FS_END_LEX,  FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,   FS_END_LEX, FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_ERROR },

	/* FS_DOT2*/     { FS_END_LEX2, FS_END_LEX2, FS_END_LEX2, FS_END_LEX2, FS_END_LEX2,FS_END_LEX2, FS_END_LEX2, FS_END_LEX2, FS_END_LEX2, FS_END_LEX2,  FS_END_LEX2,FS_END_LEX2,FS_END_LEX2, FS_END_LEX2, FS_END_LEX2, FS_END_LEX,  FS_ERROR },

	/* FS_LPAR*/     { FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_IN_COM,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,   FS_END_LEX, FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_ERROR },

	/* FS_COLON*/    { FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_ASSIGN,   FS_END_LEX,   FS_END_LEX, FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_ERROR },

	/* FS_ASSIGN*/   { FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,   FS_END_LEX, FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_ERROR },

	/* FS_END_CHLIT*/{ FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_IN_CHLIT,  FS_END_LEX, FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_ERROR },

	/* FS_IDENT*/    { FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,   FS_END_LEX, FS_END_LEX, FS_IDENT,    FS_IDENT,    FS_END_LEX,  FS_END_LEX,  FS_ERROR },

	/* FS_FRAC*/     { FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,   FS_END_LEX, FS_END_LEX, FS_END_LEX,  FS_FRAC,     FS_END_LEX,  FS_END_LEX,  FS_ERROR },

	/* FS_INT_LIT*/  { FS_END_LEX,  FS_DEC_PT,   FS_END_LEX,  FS_END_LEX,  FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,   FS_END_LEX, FS_END_LEX, FS_END_LEX,  FS_INT_LIT,  FS_END_LEX,  FS_END_LEX,  FS_ERROR },

	/* FS_SYMBOL*/   { FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,   FS_END_LEX, FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_ERROR },

	/* FS_LTHAN*/    { FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_LTHANEQ,  FS_LTHANEQ,  FS_END_LEX,   FS_END_LEX, FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_ERROR },

	/* FS_LTHANEQ*/  { FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,   FS_END_LEX, FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_ERROR },

	/* FS_GTHAN*/    { FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_GTHANEQ,  FS_END_LEX,   FS_END_LEX, FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_ERROR },

	/* FS_GTHANEQ*/  { FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,   FS_END_LEX, FS_END_LEX, FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_END_LEX,  FS_ERROR }

};

#endif


