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
    // this->stockData = new DataSet("2020-03-31",1,1,1,1,1,1); HOW to delete this without causing errors???
}
HashTableEntry::HashTableEntry(std::string NAME, std::string WKN, std::string KURZ, DataSet stockDa[5])
{
    this->name = NAME;
    this->wkn = WKN;
    this->kurz = KURZ;
    this->stockData[0] = stockDa[0];
    this->stockData[1] = stockDa[1];
    this->stockData[2] = stockDa[2];
    this->stockData[3] = stockDa[3];
    this->stockData[4] = stockDa[4];

}
HashTableEntry::HashTableEntry(const HashTableEntry& other)
{
    this->name = other.name;
    this->wkn = other.wkn;
    this->kurz = other.kurz;

    this->stockData[0] = other.stockData[0];
    this->stockData[1] = other.stockData[1];
    this->stockData[2] = other.stockData[2];
    this->stockData[3] = other.stockData[3];
    this->stockData[4] = other.stockData[4];

}

HashTableEntry::~HashTableEntry()
{

}

