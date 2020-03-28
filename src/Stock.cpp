#include "Stock.h"

Stock::Stock()
{
    DataSet emptySet("EMPTY",0,0,0,0,0,0);

    this->name = "EMPTY";
    this->wkn = "EMPTY";
    this->kurzel = "EMPTY";
    for(int i=0; i < entrySize;++i)
    {
        this->stockEntrys[i] = emptySet;
    }
}

Stock::Stock(std::string NAME, std::string WKN, std::string KURZEL, DataSet Entrys[])
{
    this->name = NAME;
    this->wkn = WKN;
    this->kurzel = KURZEL;

    for(int i=0; i < this->entrySize;++i)
    {
        this->stockEntrys[i] = Entrys[i];
    }


}
Stock::Stock(std::string NAME, std::string WKN, std::string KURZEL)
{
    DataSet emptySet("EMPTY",0,0,0,0,0,0);

    this->name = NAME;
    this->wkn = WKN;
    this->kurzel = KURZEL;
    for(int i=0; i < entrySize;++i)
    {
        this->stockEntrys[i] = emptySet;
    }
}

Stock::Stock(const Stock& other)
{
    this->name = other.name;
    this->wkn = other.wkn;
    for(int i=0; i < this->entrySize;++i)
    {
        this->stockEntrys[i] = other.stockEntrys[i];
    }


}

Stock::~Stock()
{

}

