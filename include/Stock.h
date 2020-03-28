#ifndef Stock_H
#define Stock_H

#include "DataSet.h"
#include <vector>
#include <string>

class Stock            // Data Structure to save Financial Data into.
{
    public:                     // Everything public so i don`t have to bother with GETTERs
        std::string name;
        std::string wkn;
        std::string kurzel;
        DataSet stockEntrys[30];
        int entrySize = sizeof(stockEntrys)/sizeof(stockEntrys[0]); // Tried with = 30, does not solve the problem

        Stock(const Stock& other);
        Stock();
        Stock(std::string NAME, std::string WKN, std::string KURZEL);
        Stock(std::string NAME, std::string WKN, std::string KURZEL, DataSet Entrys[]);
        virtual ~Stock();
};

#endif // Stock_H
