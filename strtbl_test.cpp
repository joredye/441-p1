#include "StringTable.h"

int main(int argc, char** argv) {
	{ // extra block to test the destructor
		StringTable t;
		string filename, aline, cmd;
		char ccmd;
                StringTableEntry* p;

		// open the input file
		if (argc < 2) return 0;
		filename = argv[1];
		ifstream f;
		f.open(filename);
		if (f.fail()) return 0;

		// read test data and insert into string table, one line per item
		while (!f.eof() && !f.fail()) {
			getline(f, aline);
			t.insert(aline);
		}
		f.close();
		t.print();

		ccmd = '?';
		while (ccmd != 'X' && ccmd != 'E') {
			cout << "Insert, Search, Print or Exit (I,S,P,X): ";
			getline(cin, cmd);
			ccmd = toupper(cmd[0]);
			switch (ccmd) {
			case 'I': cout << "Enter string: ";
				getline(cin, aline);
				t.insert(aline);
				break;
			case 'S': cout << "Enter string: ";
				getline(cin, aline);
				p = t.search(aline);
				if (p) {
					cout << "Found search 1: " << p->data << std::endl;;
					aline = t.search(p);
					cout << "Found search 2: " << aline << std::endl;;
				}
				else
					cout << "Not found\n";
				break;
			case 'P': t.print(); break;
			case 'X': cout << "Testing destruct...\n";
				      t.destruct();
					  t.print();
					  break;
			default:  cout << "Invalid input. Enter I,S,P or X\n";
			}
		}
	}
	system("pause");
	return 0;
}
