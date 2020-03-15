#ifndef HASHTABLEENTRY_H
#define HASHTABLEENTRY_H

#include "DataSet.h"
#include <vector>
#include <string>

class HashTableEntry            // Data Structure to save Financial Data into.
{
    public:                     // Everything public so i don`t have to bother with GETTERs
        std::string name;
        std::string wkn;
        int memoryLocation;

        HashTableEntry();
        HashTableEntry(const HashTableEntry& other);
        HashTableEntry(std::string NAME, std::string WKN, int MEMLOC);
        virtual ~HashTableEntry();
};

#endif // HASHTABLEENTRY_H
