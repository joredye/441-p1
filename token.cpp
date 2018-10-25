#include <iostream>

#include "token.h"



//------------------------------------------------------------------------------------
//                                     printToken()
//------------------------------------------------------------------------------------
// Given a token, prints a string equivalent of the int Token ID. When the token is
// an Identifier or Literal, also prints its String Table value.
//------------------------------------------------------------------------------------

void printToken(token tok) {
    int id = tok.tokId;
    
    //reserved words
    if (id >= 0 && id <= NUM_RES_WORDS){
        std::cout << RES_WORDS[id];
    }
    else if (id < 0 && id > -NUM_OTHER_TOKIDS) {
        std::cout << OTHER_TOKIDS[-id];    

        // a literal: print its value from the string table
        if (id <= TOK_IDENT) {
            if (tok.sref){
                std::cout << "=[[" << tok.sref->data << "]]";
	    }
            else{std::cout << "=[[SREF=NULL!]]";}
	}
    }

    else{std::cout << "INVALID_TOK_ID=" << id;}

} // printToken()
