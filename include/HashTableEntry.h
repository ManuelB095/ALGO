#ifndef HASHTABLEENTRY_H
#define HASHTABLEENTRY_H

#include <vector>
#include <string>

class HashTableEntry            // Data Structure to save Financial Data into.
{
    public:
        std::string name;
        std::string wkn;
        std::string kurz;
        std::vector<std::string>data;   // Currently working with vectors, more because i want to learn how to use them.

        HashTableEntry();       // ToDo: Add empty constructor; DO NOT USE FOR NOW!
        HashTableEntry(std::string NAME, std::string WKN, std::string KURZ);
        HashTableEntry(std::string NAME, std::string WKN, std::string KURZ, std::vector<std::string>DATA );
        virtual ~HashTableEntry();
};

#endif // HASHTABLEENTRY_H
