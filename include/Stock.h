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
        DataSet stockEntrys[5]; // Change this to thirty when it works !
        int entrySize = sizeof(stockEntrys)/sizeof(stockEntrys[0]);

        Stock(const Stock& other);
        Stock();
        Stock(std::string NAME, std::string WKN, std::string KURZEL);
        Stock(std::string NAME, std::string WKN, std::string KURZEL, DataSet Entrys[]);
        virtual ~Stock();
};

#endif // Stock_H
