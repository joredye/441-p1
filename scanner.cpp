#include <iostream>

#include "scanner.h"

string scanner::getLex()	{ return lex; }
int scanner::getCol()		{ return col; }
int scanner::getLine()		{ return line; }
int scanner::getLexCat()	{ return lexCat; }

string scanner::getErrMsg() { return errMsg; }


int scanner::openSource(string filename) {

	isErr = true;
	if (filename == "")
		errMsg = "No input file name given\n";
	else {
		f.open(filename);
		if (f.fail()){
			errMsg = "Error opening file " + filename + "\n";
                }
		else {

			errMsg = "";
			isErr = false;
			readNextChar();
			line = 1;
			col = 1;
		}
	}

	if (isErr){return 0;}
	return 1;

} // openSource()



//---------------------------------------------------------------------------------------
//                                     readNextChar
//---------------------------------------------------------------------------------------

void scanner::readNextChar() {

	if (isErr || f.fail() || isEOF){nextc = CC_EOF;}
	else {

		f.get(nextc);
		if (f.eof()) {
			isEOF = true;
			nextc = CC_EOF;
		}
		else {
			prevCol = col;
			prevLine = line;
			col++;
			if (nextc == '\n') {
				line++;
				col = 0;
			}
		}
	}

	ccat = charcat(nextc);

	//cout << "readNextChar(): " << nextc << "  ascii=" << ((int)nextc) << "  cat=" << getCCat(ccat) << endl;

} // readNextChar()



string scanner::getCCat(int x) {

	if (x >= 0 && x < NUM_CHAR_CATS){return CH_CAT[x];}
	return ("CH_???" + x);

} // getCCat()



string scanner::getFState(int x) {

	if (x >= 0 && x <= 22){return FS_STATE[x];}
	if (x == -1){return "FS_ERROR";}
	return "FS_???";

} // getFState()



int scanner::charcat(char c) {

	//const string simpleSymbols = "+-/[],;^";
	if (c=='\n')	return CC_EOL;
	if (c == CC_EOF) return CC_EOF;
	if (isalpha(c)) return CC_ALPHA;
	if (isdigit(c)) return CC_DIGIT;
	if (isspace(c)) return CC_WHITESP;
	if (c == '.')	return CC_PERIOD;
	if (c == '(')	return CC_LPAR;
	if (c == ')')	return CC_RPAR;
	if (c == '*')	return CC_STAR;
	if (c == ':')	return CC_COLON;
	if (c == '<')	return CC_LTHAN;
	if (c == '>')	return CC_GTHAN;
	if (c == '=')	return CC_EQUAL;
	if (c == '\'')	return CC_QUOTE;
	if (c == '+' || c == '-' || c == '/' || c == '[' || c == ']' || c == ',' || c == ';' || c == '^'){return CC_SYMBOL;}

	if (c >= ' ' && c < '~') return CC_OTHER;
	return CC_UNKNOWN;

} // charcat()



void scanner::setErrMsg(int & lexLine, int & lexCol, int prevState) {

	lexLine = line;
	lexCol = col;
	isErr = true;
	if (ccat == CC_UNKNOWN || ccat == CC_OTHER)
		errMsg = "Invalid character";
	else {
		switch (prevState) {
		case FS_IN_CHLIT:
		case FS_QUOTE:      lexLine--; lexCol = prevCol + 1;
			            errMsg = "End of string literal expected (')"; 
				    break;

		case FS_DEC_PT:     errMsg = "Digit expected"; break;
		case FS_END_COM:
		case FS_IN_COM:	    lexLine; lexCol = prevCol + 1;
				    errMsg = "End of comment expected "; break;

		default:            errMsg = "FSA Error: state=" + getFState(prevState) + " char='" + nextc + "'";

		}
	}
} // setErrMsg()



void scanner::addToLex(char nextc, int &lexCol, int &lexLine) {

	if (firstLexChar) {
		lexCol = col;
		lexLine = line;
		firstLexChar = false;
	}

	lex = lex + nextc;

} // addToLex()

void scanner::clearLex() {
	lex = "";
	firstLexChar = true;
}



int scanner::scanNextLex(int & lexLine, int & lexCol, int & lexcat) {
	clearLex();
	lexLine = line; lexCol = col; lexcat = 0;

	if (isEOF) return FS_EOF;
	if (isErr) return FS_ERROR;
	
        int state = FS_START, prevState = FS_START, prevCol=col;

	while ((state != FS_ERROR) && (state != FS_EOF) && (state != FS_END_LEX)) {

		//cout << "Nextc=" << nextc << " ascii=" << ((int)nextc) << "   State=" << getFState(state) << "  ccat=" << ccat << " Lex=" << lex << endl;

	    prevState = state;
	    state = FSA_TRANS[state][ccat];

		// now decide what to do with the char that got us to the new state
	    if (state == FS_END_LEX || state == FS_EOF) {
		// nextc is the first char of the NEXT lexeme. do not add to current lexeme
	    }
	    else if (state == FS_END_LEX2) {
	        // nextc is the last char of the current lexeme...add it & read next 
	        addToLex(nextc, lexCol, lexLine);
	        readNextChar();
		state = FS_END_LEX;
	    }
	    else if (state == FS_DEC_PT && f.peek() == '.') {
		// nextc='.', so next lex is '..'; end current lexeme now 
		state = FS_END_LEX;
	    }

	    else if (state == FS_START) {
			// comment or whitespace removed: discard and clear the lexeme
			clearLex();
			readNextChar();
	    }

	    else if (state == FS_ERROR) {
	        setErrMsg(lexLine, lexCol, prevState);
	    }

    	    else if (state == FS_IN_COM || state == FS_END_COM) {
			clearLex();
			if (isEOF) {
				setErrMsg(lexLine, lexCol, prevState);
				state = FS_ERROR;
			}
			else
				readNextChar();
	    }
	    else {

			// not an end state or special case; add nextc to lex and continue
			addToLex(nextc, lexCol, lexLine);
			readNextChar();

	    }
    }

    catLex();
    lexcat = lexCat;
    return state;

}



void scanner::catLex() {

	char f = lex[0];
	if (isalpha(f)) lexCat = LC_IDENT;
	else if (isdigit(f)) {

		bool isReal = false;
		for (int i = 0; i < lex.length(); i++){
		    if (lex[i] == '.') isReal = true;
		}

                if (isReal){lexCat = LC_REAL_LIT;}
		else{lexCat = LC_INT_LIT;}

	}

	else if (f == '\'') lexCat = LC_CHAR_LIT;

	else lexCat = LC_SYMBOL;

} // catLex()


