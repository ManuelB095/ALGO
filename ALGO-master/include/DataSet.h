#ifndef DATASET_H
#define DATASET_H

#include <string>

class DataSet
{
public:
    std::string date;
    double open,high,low,close,volume,adjClose;

    DataSet();
    DataSet(const DataSet& other);
    DataSet(std::string da, double op,double hi,double lo,double cl, double vo, double adjCl);
    virtual ~DataSet();
};

#endif // DATASET_H
