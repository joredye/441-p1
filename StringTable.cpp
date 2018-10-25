/*
    Author: Joshua Dyer
    Date:   25 Sept. 2018
    Project: CS441 Project 2
    
    StringTable.cpp: implements a simple
    string table using a hash function and
    linked list with constructor, destructor,
    name-based and reference-based searches,
    and prints hashing results and collision
    percentage.

*/

#include "StringTable.h"

/*
----------------------------
    default constructor
----------------------------
initializes all buckets to null.
We assume we will only be using 1
string hash table (i.e. 1 object of
our class StringTable
*/
StringTable::StringTable(){
    for(int i = 0; i < STRTBL_NUM_BUCKETS; i++){
        bucket[i] = NULL;   
    }   
}




/*
--------------------------
    default destructor
--------------------------
just invokes destruct() (see below)
*/
StringTable::~StringTable(){
    destruct();
}




/*
------------------
    destruct()
------------------
Deallocate all dynamic memory, and set all buckets to null.
*/
void StringTable::destruct(){
    
    // each bucket potentially holds a linked list
    for(int i = 0; i < STRTBL_NUM_BUCKETS; i++){
        
        StringTableEntry* entry_ref = bucket[i];
        StringTableEntry* temp = NULL;

        while(entry_ref != NULL){
            // cache pointer to next entry_ref
            temp = entry_ref->next;
            // deallocate memory used for entry_ref
            delete entry_ref;                       
            // set entry_ref so that loop runs length of linked list deallocating entries
            entry_ref = temp;                       
        }
        
        // bucket[i] doesn't automatically point to NULL after deletion:
        // what it was pointing to is deallocated, but it now points somewhere 
        // undetermined. Rectified manually.
        bucket[i] = NULL; 
    }   
}




/*
--------------
    hash()
--------------
Arguments:  string (ostensibly to be interted into hash table)
Returns:    interger index of location in hash table (array) where item is to be inserted 
Note:       implementation of Daniel J. Bernstein's 'times 33' or 'djb2' hash function
*/
unsigned int StringTable::dbj_hash(string item){
    
    if(item.length() == 0){
        return 0;
    }
    
    //see header for explanation of magic numbers
    unsigned int hash = DBJ_MAGIC;
    unsigned int ascii;

    //size t for good habits...
    for (size_t i = 0; i < item.length(); i++){
        
        // cast char in string to ascii 
        ascii = (unsigned int)item[i];
        
        // hash = (2^DBJ_2EXP + 1)*hash + ascii
        hash = ((hash << DBJ_2EXP) + hash) + ascii;
    }
    
    return(hash % STRTBL_NUM_BUCKETS);
}




/*
----------------
    insert()
----------------
Arguments:  item: a string to be inserted into the string table
Returns:    a reference to the location where the string is stored

*/
StringTableEntry* StringTable::insert(string item){
    
    // hash index
    unsigned int index = dbj_hash(item);
    
    // check bucket
    StringTableEntry* entry_ref = bucket[index];
    
    // if bucket is empty
    if(entry_ref == NULL){
        
        // create entry_ref
        StringTableEntry* new_entry_ref = new StringTableEntry;
        new_entry_ref->data = item;
        new_entry_ref->next = NULL;
        
        // insert it
        bucket[index] = new_entry_ref;
        return new_entry_ref;
    }
    // if item is hashed to an occupied bucket... 
    
    else{
        
        // look through entries in bucket (similar idiom as in destruct())
        while(entry_ref != NULL){
            
            // check if item is already stored
            if(entry_ref->data == item){
                return entry_ref;
            }
            // HAVE to check if there's a next entry before reassigning,
            // or could lead to segmentation fault
            if(entry_ref->next != NULL){
                entry_ref = entry_ref->next;
            }
            //if final entry_ref and item not found, insert at end
            //if(entry_ref->next == NULL){
            else{  
                StringTableEntry* new_entry_ref = new StringTableEntry;
                new_entry_ref->data = item;
                new_entry_ref->next = NULL;
                entry_ref->next = new_entry_ref;
                    
                return new_entry_ref;
            }
        }
    }
}




/*
------------------------
    search by string
------------------------
Arguments:  searchName: a string used as the key for the search
Returns:    a reference to a StringTableEntry stuct n, with n->data == searchName,
            or a pointer to NULL if no such struct is found  
*/
StringTableEntry* StringTable::search(string searchName){

    int index = dbj_hash(searchName);
    
    // go to bucket that will be holding the struct with data searchName
    StringTableEntry* entry_ref = bucket[index];
    
    // search bucket (possibly multiple StringTableEntries    
    while(entry_ref != NULL){
        if(entry_ref->data == searchName){
            return entry_ref;
        }
        if(entry_ref->next != NULL){
            entry_ref = entry_ref->next;
        }
    }
    // if bucket is empty or string is not found, will skip/exit while loop and just return NULL
    return NULL;    
    
}





/* 
---------------------------
    search by reference
---------------------------
Arguments:  ref: a pointer to a StringTableEntry struct to be found
Returns:    a string, data, held by the StringTableEntry pointed at
            by ref, or the empty string if said struct is not found 
*/
string StringTable::search(StringTableEntry* ref){
    string empty = "";
    
    if(ref == NULL){
        return empty;
    }
    else{
        return ref->data;
    }
}




/*
---------------
    print()
---------------
*/
void StringTable::print(){
    unsigned int num_collisions = 0;
    unsigned int num_entries = 0; 
    float col_percent = 0.0;
    StringTableEntry* entry_ref = NULL;
    
    for(int i = 0; i < STRTBL_NUM_BUCKETS; i++){
        entry_ref = bucket[i];
        
        //ignore empty buckets
        if(entry_ref != NULL){
            num_entries++;
            
            // bucket index and first entry data
            cout << "[" << setw(5) << i << "]:\t" << entry_ref->data << endl;
            
            //collisions (if any)
            entry_ref = entry_ref->next;
            while(entry_ref != NULL){
                num_entries++;
                num_collisions++;
                
                cout << setw(5) << "\t" << entry_ref->data << endl;
            
                entry_ref = entry_ref->next;
            }
        }
    }
    
    // prevent div by 0 error if no entries at all
    if(num_entries != 0){
        col_percent = ((float)num_collisions / (float)num_entries) * 100;
    
        cout << "collision percentage: " << setw(5) << col_percent << endl;   
    }
    else{
        cout << "no table entries. " << endl;
    }
}           

