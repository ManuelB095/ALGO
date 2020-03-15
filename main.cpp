#include <vector>
#include <string>
#include "HashTableEntry.h"
#include "HashTable.h"
#include "DataSet.h"
#include "Stock.h"
#include <iostream>
#include <sstream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

using std::ifstream;

/** MENU FUNCTIONS **/
void displayMenu()
{
    cout << "(0)ADD New Stock ( by Name )" << endl;
    cout << "(1)DELETE Stock" << endl;
    cout << "(2)Import Data For Stock" << endl;
    cout << "(3)Find/Display Stock Data ( by Name )" << endl;
    cout << "(4)Plot Stock Data" << endl;
    cout << "(5)Save/Export to File" << endl;
    cout << "(6) Load Table" << endl;
    cout << "(9)Exit Program" << endl;
}
void displayOperationEndLine()
{
    cout << "--------------------------------------------------" << endl;
    cout << endl;
}

/** FILE IMPORTS/EXPORTS**/
void importStockData(string filename, Stock& newStock, int MAXCOUNT)
{
    DataSet firstThirtySets[MAXCOUNT];

    string line;
    char separator = ',';           // How are the columns separated
    int columns = 7;                // How many columns do we expect to read in ?
    ifstream stockFile;
    stockFile.open(filename);

    // Everything below is for reading the column data into datasets. The first 30 lines ( 30 datasets ) will then be saved to StockEntry
    if(stockFile.is_open())
    {
        getline(stockFile,line); // Read in first line ( = Headlines of the columns ) and discard it.
        int counter = 0;

        while(getline(stockFile,line) && counter < MAXCOUNT) // !! Change to 30 when DONE !!
        {
            std::stringstream linestream(line); // What this does is basically this: stringstream takes a string ( here: line ) and
            string::size_type size_t;           // wraps it in an iostream. For example you could do: linestream << "addThisText"; and addThisText would be added to the line.
            DataSet temporarySet;

            for(int i=0; i < columns;i++)
            {
                string temp; // Temp saves every columns data ( open, high, low, date etc.) for EVERY Iteration different!
                if(i==6)     // Last column has no separator. Therefore: Read till we encounter \n
                {
                    getline(linestream,temp,'\n');
                }
                else {
                    getline(linestream,temp,separator); // separator = ','
                }

                switch(i)
                {
                case 0:
                    temporarySet.date = temp;
                    break;
                case 1:
                    temporarySet.open = std::stod(temp, &size_t);     // Converts string of data into a double      std::stod(getline(temp,&size_t));
                    break;
                case 2:
                    temporarySet.high = std::stod(temp, &size_t);
                    break;
                case 3:
                    temporarySet.low = std::stod(temp, &size_t);
                    break;
                case 4:
                    temporarySet.close = std::stod(temp, &size_t);
                    break;
                case 5:
                    temporarySet.volume = std::stod(temp, &size_t);
                    break;
                case 6:
                    temporarySet.adjClose = std::stod(temp, &size_t);
                    break;
                }
            }
            firstThirtySets[counter] = temporarySet;
            counter++;
        }
        // Write Data to Stock
        for(int i=0; i < MAXCOUNT; i++)
        {
            newStock.stockEntrys[i] = firstThirtySets[i];
        }
    }
}

int findNextAvailablePosition(Stock (&myStorageArray)[5])
{
    int arraySize = sizeof(myStorageArray)/sizeof(myStorageArray[0]);
    for(int i=0; i<arraySize;i++)
    {
        if(myStorageArray[i].name == "EMPTY" || myStorageArray[i].name == "DELETED")
        {
            return i;
        }
    }
    return -1;
}

int PutStockInMemory(Stock& myStock, Stock (&myStorageArray)[5])
{
    int nextAvailablePos = findNextAvailablePosition(myStorageArray);
    myStorageArray[nextAvailablePos] = myStock;
    return nextAvailablePos;
}

void printStockDataSets(Stock& myStock)
{
    int dataSetCounter = 0;
    for(int i=0; i< myStock.entrySize; i++)
    {
        if(myStock.stockEntrys[i].date !="EMPTY")
        {
            dataSetCounter++;
            cout << "Entry Nr." << (i+1) << ": " << "Date -> " << myStock.stockEntrys[i].date << endl;
            cout << "Open: " << myStock.stockEntrys[i].open << "High: " << myStock.stockEntrys[i].high
                 << "Low: "  << myStock.stockEntrys[i].low  << "Close: "<< myStock.stockEntrys[i].close
                 << "Volume: " << myStock.stockEntrys[i].volume << "AdjClose: " << myStock.stockEntrys[i].adjClose << endl;
        }
    }
    if(dataSetCounter == 0)
    {
        cout << "No available Data for " << myStock.name << " yet." << endl;
    }
}
void deleteStockDataSets(Stock& myStock)
{
    DataSet EmptySet("EMPTY",0,0,0,0,0,0);

    myStock.name = "DELETED";
    myStock.wkn = "DELETED";
    myStock.kurzel = "DELETED";

    for(int i=0; i<myStock.entrySize;++i)
    {
        myStock.stockEntrys[i] = EmptySet;
    }
}

int main()
{
    /** TO DO: Implement stockStorageArray and HashTable on the HEAP instead of the STACK.
        Other Functions will have to be adjusted a bit for that to work ( pass by reference for example with : *&myArray )

        TO DO: Implement Plotting Function ( just copy paste if you already have that, should work fine )

        TO DO: Implement LOAD/SAVE Table -> The only REAL Work still left to do. This one might get on our nerves.
               I have a basic import function for Stock Data in Place already, which might be useful.
     **/
    Stock stockStorageArray[5];
    HashTable nameTable;

    int opNumber = -1;

    while(opNumber != 9)
    {
        displayMenu();
        cout << ">> ";
        cin >> opNumber;

        switch(opNumber)
        {
        case 0:         // Add New Stock
            {
                string name,wkn,kurz;
                cout << "NAME of new Stock: ";
                cin >> name;
                cout << "WKN of new Stock: ";
                cin >> wkn;
                cout << "KURZEL of new Stock: ";
                cin >> kurz;

                // Add Stock to Memory
                Stock newStock(name,wkn,kurz);
                int positionInMemory = PutStockInMemory(newStock,stockStorageArray);

                // Add Stock to HashTable
                HashTableEntry newEntry(name,wkn,positionInMemory);
                nameTable.Add(newEntry);
                cout << "Successfully added new Stock: " << stockStorageArray[0].name << endl;
                displayOperationEndLine();
                break;
            }
        case 1:         // Delete Stock
            {
                string name;
                cout << "Please enter the name of the Stock: ";
                cin >> name;

                // Delete From Memory
                int stockLocationInMemory = nameTable.FindByName(name);
                if(stockLocationInMemory != -1)
                {
                    deleteStockDataSets(stockStorageArray[stockLocationInMemory]);
                }
                 // Delete From HashTable
                nameTable.DeleteFromTable(name);

                displayOperationEndLine();
                break;
            }
        case 2:         // Import Data For Stock
            {
                string name;
                string fileName;
                cout << "Please enter the name of the ( already existing! ) Stock: ";
                cin >> name;
                cout << "Please enter the ( full ) filename with your course data: ";
                cin >> fileName;

                // If STOCK Exists -> Write
                int stockLocationInMemory = nameTable.FindByName(name);
                if(stockLocationInMemory != -1)
                {
                    try {
                        importStockData(fileName, stockStorageArray[stockLocationInMemory],5); // Writes DIRECTLY into the given STOCK
                    }
                    catch(...) {
                        cout << "File not found/or could not be read" << endl;
                    }
                }
                else if(stockLocationInMemory == -1)
                {
                    cout << "The stock with name " << name << " has been deleted from the Table." << endl;
                }
                displayOperationEndLine();
                break;
            }
        case 3:         // Find/Display Stock Data (by Name)
            {
                string name;
                cout << "Please enter the name of the Stock: ";
                cin >> name;

                int stockLocationInMemory = nameTable.FindByName(name);
                // Print everything thats in "Stock"
                if(stockLocationInMemory != -1)
                {
                    printStockDataSets(stockStorageArray[stockLocationInMemory]);
                }
                else if(stockLocationInMemory == -1)
                {
                    cout << "The stock with name " << name << " has been deleted from the Table." << endl;
                }
                displayOperationEndLine();
            }
            break;
        case 4:     // PLOT Stock Data
            break;
        case 5:     // SAVE/EXPORT To File
            break;
        case 6:     // LOAD Table
            break;
        case 7:     // Currently Unused
            break;
        case 8:     // Currently Unused
            break;
        case 9:     // EXIT Program
            return 0;
        }
        if(opNumber > 9 || opNumber < 0)
        {
            cout << "Something went wrong." << endl;
        }
    }


/**$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  TESTING AREA - NOT RELEVANT ANYMORE $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$**/
/** Test: Import Stock Data and Add new Stock to Memory AND Table **/

//    int MAXCOUNT = 5; // Change to 30 when done
//
//    Stock microsoftStock("Microsoft","0001","ST1");
//
//    /** Test: Artificially insert Stock to test program **/
//    Stock teslaStock("Tesla","0002","ST2");
//    stockStorageArray[0] = teslaStock;
//
//    int nextAvailablePosition = findNextAvailablePosition(stockStorageArray);
//    if(nextAvailablePosition == -1)
//    {
//        return 1;
//    }
//    cout << stockStorageArray[nextAvailablePosition].name;
//    stockStorageArray[nextAvailablePosition] = microsoftStock;
//    cout << stockStorageArray[nextAvailablePosition].name;
//
//    importStockData("msft.csv", stockStorageArray[nextAvailablePosition], MAXCOUNT);
//
//    for(int i=0; i < MAXCOUNT; i++)
//    {
//        cout << stockStorageArray[0].name << endl;
//        cout << stockStorageArray[0].stockEntrys[i].date << " ";
//        cout << stockStorageArray[0].stockEntrys[i].close << " ";
//        cout << stockStorageArray[0].stockEntrys[i].high << " ";
//        cout << stockStorageArray[0].stockEntrys[i].adjClose << endl;
//    }
//
//    HashTableEntry csvEntry("Microsoft","0001", nextAvailablePosition);
//    cout << "Memory Location: " << csvEntry.memoryLocation << endl;
//
//    csvTable.Add(csvEntry);
//    csvTable.FindByName(csvEntry.name);


/**$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$**/

    /** TEST: READ IN test Data into entry element **/
//    HashTableEntry testEntry("Microsoft","001", 5);
//    HashTableEntry testEntry2("Tesla", "002", 6);

    /** TEST: READ Stocks into HashTable **/

//    HashTable myTable;
//
//    myTable.Add(testEntry); // Puts testEntry on position 261 in table;
//    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 262; Offset 2^0 = 1
//    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 263; Offset 2^1 = 2
//    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 265 ; Offset 2^2 = 4
//    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 269 ; Offset 2^3 = 8
//    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 277 ; Offset 2^4 = 16
//    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 293 ; Offset 2^5 = 32
//    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 325 ; Offset 2^6 = 64
//    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 389 ; Offset 2^7 = 128
//    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 517 ; Offset 2^8 = 256
//    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 773 ; Offset 2^9 = 512
//    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 1285%1001 = 284 ; Offset 2^10 = 1024 CRITICAL SECTION HERE!

//    myTable.Add(testEntry2);
//
//    myTable.FindByName(testEntry.name);
//    myTable.FindByName(testEntry2.name);
//    myTable.DeleteFromTable(testEntry);
//    myTable.DeleteFromTable(testEntry); // This should produce an ERROR
//    myTable.FindByName(testEntry.name); // This should produce an ERROR
//    myTable.Add(testEntry);
//    myTable.FindByName(testEntry.name);
//
//    myTable.printAllEntrys();

    /** All Tests up to here ran successfully ! **/
    return 0;
}
