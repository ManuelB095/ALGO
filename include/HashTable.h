#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
#include <functional>
#include "HashTableEntry.h"

class HashTable // !! IMPOTANT ! Choose size with m = 4*j + 3, where m is PRIME !!
{
    int calculateHash(std::string entryName);           // Turn string into a hash
    bool alreadyContainsStock(std::string STOCKNAME);   // Returns true if Table Already contains stock.
    bool alreadyContainsStockViaWKN(std::string WKN);
    int FindEntryPos(std::string ENTRYNAME);            // Searches for specific Entry and returns its position
    int FindEntryPosViaWKN(std::string WKN);
    int FindPositionForEntry(int KEY);                  // Finds EMPTY entrys OR deleted/"-1" entrys to store entry in
    int FindPositionForEntryViaWKN(int KEY);

    public:
        HashTableEntry Elements[2011];             // 2011 is prime (2011-3)/4 = 502, so checks out !
        HashTable();
        HashTable(int TABLESIZE);
        HashTable(const HashTable& other);
        virtual ~HashTable();

        // METHODEN
        int FindByName(std::string NAME);    // returns MemoryLocation of Stock Data
        int FindByWKN(std::string WKN);
        void Add(HashTableEntry entry);      // Adds own Data Type of HashTableEntrys
        void AddViaWKN(HashTableEntry entry);
        void DeleteFromTable(std::string ENTRYNAME);   // Deletes entry from HashTable and replaces Entry-Name with "-1"
        void DeleteFromTableViaWKN(std::string WKN);
        void printAllEntrys();      //Prints all NON-EMPTY Entrys ( pls use wisely ! )
};

#endif // HASHTABLE_H
