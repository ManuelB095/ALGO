#include "HashTableEntry.h"

HashTableEntry::HashTableEntry()
{
    this->name = "EMPTY";
    this->wkn = "EMPTY";
    this->memoryLocation = -1;

}

HashTableEntry::HashTableEntry(std::string NAME, std::string WKN, int MEMLOC)
{
    this->name = NAME;
    this->wkn = WKN;
    this->memoryLocation = MEMLOC;
}

HashTableEntry::HashTableEntry(const HashTableEntry& other)
{
    this->name = other.name;
    this->wkn = other.wkn;
    this->memoryLocation = other.memoryLocation;

}

HashTableEntry::~HashTableEntry()
{

}

