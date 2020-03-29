#include "HashTable.h"
#include <iostream>

HashTable::HashTable()
{
    HashTableEntry EmptyEntry("EMPTY","EMPTY",-1);
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]);
    for(int i=0; i < arraySize;i++)
    {
        this->Elements[i] = EmptyEntry;
    }
}

HashTable::HashTable(const HashTable& other)
{
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]);
    for(int i=0; i < arraySize;i++)
    {
        this->Elements[i] = other.Elements[i];
    }
}

HashTable::~HashTable()
{
    //dtor
}
int HashTable::calculateHash(std::string entryName) // Calculates Hash-Key based on entry.name
{
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]); // To find out size of HashTable
    int seed = 131; // Random Seed; Found that 131 works quite goog ( tip from the internet )
    unsigned long hashValue = 0;
    for(int i = 0; i < entryName.length(); i++)
    {
      hashValue = (hashValue * seed) + entryName[i];
    }
    hashValue %= arraySize;
    std::cout << hashValue << std::endl;
    return hashValue;
}

int HashTable::FindEntryPos(std::string ENTRYNAME) // Returns -1 for ERROR;
{
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]);
    int KEY = calculateHash(ENTRYNAME);

    if(this->Elements[KEY].name == ENTRYNAME)
    {
        return KEY;
    }

    else if (this->Elements[KEY].name != ENTRYNAME)
    {
        int directionSwitch = 2;              // even numbers -> +1,+4,+9 uneven numbers -> -1,-4,-9
        int newPositionPositive = KEY;
        int newPositionNegative = KEY;
        int collisions = 0;

        while(collisions <= 30 ) // Break if successful OR after 30 collisions
        {
            collisions++;
            for(int i=0; i<2;i++) // Check both directions before increasing collusions
            {
                if(directionSwitch%2 == 0)
                {
                    newPositionPositive = newPositionPositive + 2* collisions -1;
                    newPositionPositive%=arraySize;
                    if (this->Elements[newPositionPositive].name == ENTRYNAME )
                    {
                        return newPositionPositive;
                    }
                }
                else if(directionSwitch%2 == 1)
                {
                    newPositionNegative = newPositionNegative - 2* collisions +1;
                    newPositionNegative%=arraySize;
                    newPositionNegative = newPositionNegative < 0 ? newPositionNegative+=arraySize : newPositionNegative;
                    if (this->Elements[newPositionNegative].name == ENTRYNAME )
                    {
                        return newPositionNegative;
                    }
                }
                // Increase this to switch between POSITIVE and NEGATIVE Directions.
                directionSwitch++;
            }
        } // End of WHILE
    } // End of IF/ELSE
    return -1;
}

int HashTable::FindEntryPosViaWKN(std::string WKN) // Returns -1 for ERROR;
{
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]);
    int KEY = calculateHash(WKN);

    if(this->Elements[KEY].wkn == WKN)
    {
        return KEY;
    }

    else if (this->Elements[KEY].wkn != WKN)
    {
        int directionSwitch = 2;              // even numbers -> +1,+4,+9 uneven numbers -> -1,-4,-9
        int newPositionPositive = KEY;
        int newPositionNegative = KEY;
        int collisions = 0;

        while(collisions <= 30 ) // Break if successful OR after 30 collisions
        {
            collisions++;
            for(int i=0; i<2;i++) // Check both directions before increasing collusions
            {
                if(directionSwitch%2 == 0)
                {
                    newPositionPositive = newPositionPositive + 2* collisions -1;
                    newPositionPositive%=arraySize;
                    if (this->Elements[newPositionPositive].wkn == WKN )
                    {
                        return newPositionPositive;
                    }
                }
                else if(directionSwitch%2 == 1)
                {
                    newPositionNegative = newPositionNegative - 2* collisions +1;
                    newPositionNegative%=arraySize;
                    newPositionNegative = newPositionNegative < 0 ? newPositionNegative+=arraySize : newPositionNegative;
                    if (this->Elements[newPositionNegative].wkn == WKN )
                    {
                        return newPositionNegative;
                    }
                }
                // Increase this to switch between POSITIVE and NEGATIVE Directions.
                directionSwitch++;
            }
        } // End of WHILE
    } // End of IF/ELSE
    return -1;
}

int HashTable::FindByName(std::string ENTRYNAME) // Returns -1 for ERROR; Value between 0 and Stock Array Size for Memory Location
{
    int entryPosition = FindEntryPos(ENTRYNAME);
    if (entryPosition == -1)
    {
        std::cout << "ERROR: Could not find Stock '" << ENTRYNAME << "'" << std::endl;
        return -1;
    }
    else {
        std::cout << "Successfully found HashTableEntry with name -" << ENTRYNAME << " on position -> " << entryPosition << std::endl;
        return this->Elements[entryPosition].memoryLocation;
    }
}
int HashTable::FindByWKN(std::string WKN) // Returns -1 for ERROR; Value between 0 and Stock Array Size for Memory Location
{
    int entryPosition = FindEntryPosViaWKN(WKN);
    if (entryPosition == -1)
    {
        std::cout << "ERROR: Could not find Stock '" << WKN << "'" << std::endl;
        return -1;
    }
    else {
        std::cout << "Successfully found HashTableEntry with wkn -" << WKN << " on position -> " << entryPosition << std::endl;
        return this->Elements[entryPosition].memoryLocation;
    }
}

bool HashTable::alreadyContainsStock(std::string STOCKNAME)
{
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]);
    for(int i=0;i<arraySize;++i)
    {
        if(this->Elements[i].name == STOCKNAME)
        {
            return true;
        }
    }
    return false;
}
bool HashTable::alreadyContainsStockViaWKN(std::string WKN)
{
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]);
    for(int i=0;i<arraySize;++i)
    {
        if(this->Elements[i].wkn == WKN)
        {
            return true;
        }
    }
    return false;
}

int HashTable::FindPositionForEntry(int KEY)
{
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]);

    // IF: we have an available entry right at the KEY Position, simply return this one.
    /** TEST : Artificially put -1 on KEY Position **/
    if(this->Elements[KEY].name == "EMPTY" || this->Elements[KEY].name == "-1")
    {
        return KEY;
    }

    // ELSE: search in alternating directions ( quadratic probing ) for next available Position.
    else if (this->Elements[KEY].name != "EMPTY" && this->Elements[KEY].name != "-1")
    {
        int directionSwitch = 2;              // even numbers -> +1,+4,+9 uneven numbers -> -1,-4,-9
        int newPositionPositive = KEY;
        int newPositionNegative = KEY;
        int collisions = 0;

        while(collisions <= 30 ) // Break if successful OR after 30 collisions
        {
            collisions++;
            for(int i=0; i<2;i++) // Check both directions before increasing collusions
            {
                if(directionSwitch%2 == 0)
                {
                    newPositionPositive = newPositionPositive + 2* collisions -1;
                    newPositionPositive%=arraySize;
                    if (this->Elements[newPositionPositive].name == "EMPTY" )
                    {
                        return newPositionPositive;
                    }
                }
                else if(directionSwitch%2 == 1)
                {
                    newPositionNegative = newPositionNegative - 2* collisions +1;
                    newPositionNegative%=arraySize;
                    newPositionNegative = newPositionNegative < 0 ? newPositionNegative+=arraySize : newPositionNegative;
                    if (this->Elements[newPositionNegative].name == "EMPTY" )
                    {
                        return newPositionNegative;
                    }
                }
                // Increase this to switch between POSITIVE and NEGATIVE Directions.
                directionSwitch++;
            }
        } // End of WHILE
    } // End of IF/ELSE

    // IF: none of the above worked and no available Position was found return ERROR
    std::cout << "ERROR: No available position in the table!" << std::endl;
    return -1;

}

int HashTable::FindPositionForEntryViaWKN(int KEY)
{
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]);

    // IF: we have an available entry right at the KEY Position, simply return this one.
    /** TEST : Artificially put -1 on KEY Position **/
    if(this->Elements[KEY].wkn == "EMPTY" || this->Elements[KEY].wkn == "-1")
    {
        return KEY;
    }

    // ELSE: search in alternating directions ( quadratic probing ) for next available Position.
    else if (this->Elements[KEY].wkn != "EMPTY" && this->Elements[KEY].wkn != "-1")
    {
        int directionSwitch = 2;              // even numbers -> +1,+4,+9 uneven numbers -> -1,-4,-9
        int newPositionPositive = KEY;
        int newPositionNegative = KEY;
        int collisions = 0;

        while(collisions <= 30 ) // Break if successful OR after 30 collisions
        {
            collisions++;
            for(int i=0; i<2;i++) // Check both directions before increasing collusions
            {
                if(directionSwitch%2 == 0)
                {
                    newPositionPositive = newPositionPositive + 2* collisions -1;
                    newPositionPositive%=arraySize;
                    if (this->Elements[newPositionPositive].wkn == "EMPTY" )
                    {
                        return newPositionPositive;
                    }
                }
                else if(directionSwitch%2 == 1)
                {
                    newPositionNegative = newPositionNegative - 2* collisions +1;
                    newPositionNegative%=arraySize;
                    newPositionNegative = newPositionNegative < 0 ? newPositionNegative+=arraySize : newPositionNegative;
                    if (this->Elements[newPositionNegative].wkn == "EMPTY" )
                    {
                        return newPositionNegative;
                    }
                }
                // Increase this to switch between POSITIVE and NEGATIVE Directions.
                directionSwitch++;
            }
        } // End of WHILE
    } // End of IF/ELSE

    // IF: none of the above worked and no available Position was found return ERROR
    std::cout << "ERROR: No available position in the table!" << std::endl;
    return -1;

}

void HashTable::Add(HashTableEntry entry) // Checks if HashTableEntry element can be added at its hash position.
{
    int key = calculateHash(entry.name);
    if(alreadyContainsStock(entry.name))
    {
        std::cout << "This Stock already exists !" << std::endl;
    }
    else {
        int nextEmptyEntry = FindPositionForEntry(key);
        if(nextEmptyEntry != -1)
        {
            this->Elements[nextEmptyEntry] = entry;
            std::cout << "Successfully put HashTableEntry with name -" << entry.name << " on position -> " << nextEmptyEntry << std::endl;
        }
    }
}
void HashTable::AddViaWKN(HashTableEntry entry)
{
    int key = calculateHash(entry.wkn);
    if(alreadyContainsStockViaWKN(entry.wkn))
    {
        std::cout << "This Stock already exists !" << std::endl;
    }
    else {
        int nextEmptyEntry = FindPositionForEntry(key);
        if(nextEmptyEntry != -1)
        {
            this->Elements[nextEmptyEntry] = entry;
            std::cout << "Successfully put HashTableEntry with wkn -" << entry.wkn << " on position -> " << nextEmptyEntry << std::endl;
        }
    }
}

void HashTable::DeleteFromTable(std::string ENTRYNAME)
{
    int entryPosition = FindEntryPos(ENTRYNAME);
    if (entryPosition == -1)
    {
        std::cout << "ERROR: Could not find/delete Stock '" << ENTRYNAME << "'" << std::endl;
    }
    else {
        this->Elements[entryPosition].name = "EMPTY";
        std::cout << "Successfully deleted HashTableEntry with name -" << ENTRYNAME<< " on position -> " << entryPosition << std::endl;
    }
}
void HashTable::DeleteFromTableViaWKN(std::string WKN)
{
    int entryPosition = FindEntryPosViaWKN(WKN);
    if (entryPosition == -1)
    {
        std::cout << "ERROR: Could not find/delete Stock '" << WKN << "'" << std::endl;
    }
    else {
        this->Elements[entryPosition].wkn = "EMPTY";
        std::cout << "Successfully deleted HashTableEntry with wkn -" << WKN<< " on position -> " << entryPosition << std::endl;
    }
}

void HashTable::printAllEntrys()
{
    int arraySize = sizeof(this->Elements)/sizeof(this->Elements[0]);
    int countedEntrys = 0;
    for(int i=0; i < arraySize;i++)
    {
        if(this->Elements[i].name != "EMPTY" && this->Elements[i].name != "-1")
        {
            countedEntrys++;
            std::cout << "Position-" << i << std::endl;
            std::cout << "+NAME " << Elements[i].name << " +WKN " << Elements[i].wkn << " +MEMLOC " << Elements[i].memoryLocation << std::endl;
        }
    }
    if(countedEntrys > 1000)
    {
        std::cout << std::endl << "WARNING: HashTable filled >50%!" << std::endl;
    }
}
