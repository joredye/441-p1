
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "scanner.h"
#include "StringTable.h"
#include "token.h"
using namespace std;

int main(int argc, char ** argv) {
	// get file name from command line
	string filename;
	int state = FS_START, c = 1;
	if (argc < 2)
		filename = "";
	else
		filename = argv[1];

	// create string table and scanner; open source file
	StringTable t;
	scanner s;
	if (!s.openSource(filename)) {
		cout << s.getErrMsg() << endl;
		system("pause");
		return 0;
	}

	
	token tok = s.getNextToken(t);
	while (tok.tokId != TOK_SCANERR && tok.tokId != TOK_ENDSRC) {
		printToken(tok);
		cout << endl;
		tok = s.getNextToken(t);
	}
	cout << "Ended with token:\n";
	printToken(tok);
	cout << endl << endl;

	t.print();

	system("pause");
	return 0;
}
