#ifndef STRINGTABLE_H
#define STRINGTABLE_H

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

const int STRTBL_NUM_BUCKETS = 1000;

// A comment from github, detailing the reasoning behind 
// the dbj hash's most commonly used constants

/*
 *
 * DJBX33A (Daniel J. Bernstein, Times 33 with Addition)
 *
 * This is Daniel J. Bernstein's popular `times 33' hash function as
 * posted by him years ago on comp.lang.c. It basically uses a function
 * like ``hash(i) = hash(i-1) * 33 + str[i]''. This is one of the best
 * known hash functions for strings. Because it is both computed very
 * fast and distributes very well.
 *
 * The magic of number 33, i.e. why it works better than many other
 * constants, prime or not, has never been adequately explained by
 * anyone. So I try an explanation: if one experimentally tests all
 * multipliers between 1 and 256 (as RSE did now) one detects that even
 * numbers are not useable at all. The remaining 128 odd numbers
 * (except for the number 1) work more or less all equally well. They
 * all distribute in an acceptable way and this way fill a hash table
 * with an average percent of approx. 86%. 
 *
 * If one compares the Chi^2 values of the variants, the number 33 not
 * even has the best value. But the number 33 and a few other equally
 * good numbers like 17, 31, 63, 127 and 129 have nevertheless a great
 * advantage to the remaining numbers in the large set of possible
 * multipliers: their multiply operation can be replaced by a faster
 * operation based on just one shift plus either a single addition
 * or subtraction operation. And because a hash function has to both
 * distribute good _and_ has to be very fast to compute, those few
 * numbers should be preferred and seems to be the reason why Daniel J.
 * Bernstein also preferred it.
 *
 *
 *                  -- Ralf S. Engelschall <rse@engelschall.com>

*/


const int DBJ_MAGIC = 5381;
const int DBJ_2EXP = 7; // in this case, a = 129
 
// a node in a linked list
struct StringTableEntry {
	string data;
	StringTableEntry* next = NULL;
};

class StringTable {
public:
	StringTable();
	~StringTable(); //just invoke destruct
	StringTableEntry* insert(string item);
	StringTableEntry* search(string searchName);
	string       search(StringTableEntry* ref);
	void print();
        void destruct(); //deallocate all dynamic memory, set all buckets to NULL

private:
	StringTableEntry* bucket[STRTBL_NUM_BUCKETS];
        unsigned int dbj_hash(string item);
        
};



#endif
