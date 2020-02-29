#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
#include <functional>
#include "HashtableEntry.h"

using std::vector;
using std::string;

class HashTable
{
    int calculateHash(HashTableEntry entry); // Private Function: Sub Function of Add; No User Access necessary!
    int getExponential(int base, int expo);  // Intern Function to get exponential for quadratic probing!
    public:
        int tableSize;                       // ToDO: Add Getter in the future and move this one to private.
        HashTableEntry Elements[1001];       // Array of HashTableEntrys represents actual table; Hardcoded for now!!

        HashTable(int TABLESIZE);            // ToDo: Make TABLESIZE actually matter!
        virtual ~HashTable();

        // METHODEN

        void Add(HashTableEntry entry);      // Adds own Data Type of HashTableEntrys

};

#endif // HASHTABLE_H
