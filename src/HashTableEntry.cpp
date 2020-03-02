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
    this->stockData = new DataSet("2020-03-31",1,1,1,1,1,1); // HOW to delete this without causing errors???
}
HashTableEntry::HashTableEntry(std::string NAME, std::string WKN, std::string KURZ, DataSet& stockDa)
{
    this->name = NAME;
    this->wkn = WKN;
    this->kurz = KURZ;
    this->stockData = &stockDa;

}
HashTableEntry::HashTableEntry(const HashTableEntry& other)
{
    this->name = other.name;
    this->wkn = other.wkn;
    this->kurz = other.kurz;

    this->stockData = other.stockData;
}

HashTableEntry::~HashTableEntry()
{

}

