#include "DataSet.h"
DataSet::DataSet()
{
    //ctor
}

DataSet::DataSet(std::string da, double op,double hi,double lo,double cl, double vo, double adjCl)
{
    this->date = da;
    this->open = op; this->high = hi; this->low = lo; this->close = cl; this->volume = vo; this->adjClose = adjCl;
}
DataSet::DataSet(const DataSet& other)
{
    this->date = other.date;
    this->open = other.open; this->high = other.high; this->low = other.low; this->close = other.close; this->volume = other.volume; this->adjClose = other.adjClose;
}

DataSet::~DataSet()
{
    //dtor
}
