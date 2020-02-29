#include "HashTableEntry.h"

HashTableEntry::HashTableEntry()
{
    //ctor
}
HashTableEntry::HashTableEntry(std::string NAME, std::string WKN, std::string KURZ)
{
    this->name = NAME;
    this->wkn = WKN;
    this->kurz = KURZ;
    std::vector<std::string> generic = {"2015-03-03","43.56","43.83","43.09","43.28","31897900","43.28"};
    this->data = generic;
}
HashTableEntry::HashTableEntry(std::string NAME, std::string WKN, std::string KURZ, std::vector<std::string>DATA )
{
    this->name = NAME;
    this->wkn = WKN;
    this->kurz = KURZ;
    this->data = DATA;
}

HashTableEntry::~HashTableEntry()
{
    //dtor
}

