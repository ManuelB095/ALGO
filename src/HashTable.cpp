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

}
HashTable::HashTable(const HashTable& other)
{
    this->tableSize = other.tableSize;
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]);
    for(int i=0; i < arraySize;i++)
    {
        this->Elements[i] = other.Elements[i];
    }
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
    bool exit = false;

    for(int i=0;i<arraySize;i++)
    {
        if(exit == true)
        {
            break;
        }

        if( i == key && this->Elements[i].name == "EMPTY") // We found the key AND Table Entry is Empty -> Paste our element here
        {
            this->Elements[i] = entry;
            std::cout << "Successfully put HashTableEntry with name -" << entry.name << " on position -" << i << std::endl;
            break;
        }
        else if ( i == key && this->Elements[i].name != "EMPTY") // We found the key BUT Table Entry is NOT Empty -> Quadratic Probing
        {
            int alternator = 2;     // even numbers -> +1,+4,+9 uneven numbers -> -1,-4,-9
            int newPositionPositive = key;  // initialise to key
            int newPositionNegative = key;
            int collisions = 0;


            while(collisions <= 30 ) // Break if successfull OR after 30 collisions
            {
                if(exit==true)
                {
                    break;
                }


                collisions++;
                for(int i=0; i<2;i++) // Check both directions before increasing collusions
                {
                    if(alternator%2 == 0)
                    {
                        newPositionPositive = newPositionPositive + 2* collisions -1;
                        newPositionPositive%=arraySize;
                        if (this->Elements[newPositionPositive].name == "EMPTY" )
                        {
                            this->Elements[newPositionPositive] = entry;
                            std::cout << "Successfully put HashTableEntry with name -" << entry.name << " on (quadratic probing )position -" << newPositionPositive << std::endl;
                            exit = true;
                            break;// SUCCESS -> Exit Loop
                        }
                    }
                    else if(alternator%2 == 1)
                    {
                        newPositionNegative = newPositionNegative - 2* collisions +1;
                        newPositionNegative%=arraySize;
                        newPositionNegative = newPositionNegative < 0 ? newPositionNegative+=arraySize : newPositionNegative;
                        if (this->Elements[newPositionNegative].name == "EMPTY" )
                        {
                            this->Elements[newPositionNegative] = entry;
                            std::cout << "Successfully put HashTableEntry with name -" << entry.name << " on (quadratic probing )position -" << newPositionNegative << std::endl;
                            exit = true;
                            break; // SUCCESS -> Exit Loop
                        }
                    }
                    // Increase alternator if one of the if-Statements failed
                    alternator++;
                }
            }
        } // End of ( if key element of table is not empty -> begin quadratic probing )
    } // End of for Loop
}
