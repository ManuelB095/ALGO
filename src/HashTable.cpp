#include "HashTable.h"
#include <iostream>

HashTable::HashTable(int TABLESIZE)
{
    HashTableEntry EmptyEntry("EMPTY","WKN","KURZ");
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]);
    for(int i=0; i < arraySize;i++)
    {
        this->Elements[i] = EmptyEntry;
    }
}

HashTable::~HashTable()
{
    //dtor
}

int HashTable::calculateHash(HashTableEntry entry) // Calculates Hash-Key based on entry.name
{
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]); // To find out size of HashTable

    std::hash<std::string> hasher;
    auto hashed = hasher(entry.name);
    std::cout << "Hash-Value: " << hashed << std::endl;
    hashed %= arraySize;
    return hashed;
}

int HashTable::getExponential(int base, int expo)
{
    if (expo == 0)
    {
        return 1;
    }
    int result = 1;
    for(int i=0; i < expo; i++)
    {
        result *= base;
    }
    return result;
}


void HashTable::Add(HashTableEntry entry) // Checks if HashTableEntry element can be added at its hash position.
{
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]);
    int key = calculateHash(entry); std::cout << "Key: " << key << std::endl;

    for(int i=0;i<arraySize;i++)
    {
        if( i == key && this->Elements[i].name == "EMPTY") // We found the key AND Table Entry is Empty -> Paste our element here
        {
            this->Elements[i] = entry;
            std::cout << "Successfully put HashTableEntry with name -" << entry.name << " on position -" << i << std::endl;
            break;
        }
        else if ( i == key && this->Elements[i].name != "EMPTY") // We found the key BUT Table Entry is NOT Empty -> Quadratic Probing
        {
            int probingOffset = 1;
            int newPosition = probingOffset + i;
            int exponent = 0;

            while(this->Elements[newPosition].name != "EMPTY")
            {
                probingOffset = getExponential(2,exponent); // Example: 2^1 = 2; 2^2 = 4 and so on..
                newPosition = probingOffset + i;
                newPosition %= arraySize;                 // Make sure that key ( key == i here ) + offset DO NOT exceed the limits of our table. key + offset = newPosition
                std::cout << "Exponential: " << probingOffset << std::endl;
                exponent++;                                 // Increase exponent in case loop needs to reiterate once more.

            }

            std::cout << this->Elements[newPosition].name << std::endl;

            if (this->Elements[newPosition].name == "EMPTY" )
            {
                this->Elements[newPosition] = entry;
                std::cout << "Successfully put HashTableEntry with name -" << entry.name << " on (quadratic probing )position -" << newPosition << std::endl;
            }


            // Quadratische Sondierung
        }
    }
}
