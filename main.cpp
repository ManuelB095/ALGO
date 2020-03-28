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
    cout << "(6)Load Table" << endl;
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

int findNextAvailablePosition(Stock* myStorageArray, int arrLength)
{
    for(int i=0; i<arrLength;i++)
    {
        if(myStorageArray[i].name == "EMPTY" || myStorageArray[i].name == "DELETED")
        {
            return i;
        }
    }
    return -1;
}

int PutStockInMemory(Stock& myStock, Stock* myStorageArray, int storageArrayLength)
{
    int nextAvailablePos = findNextAvailablePosition(myStorageArray, storageArrayLength);
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
            cout << "Open: " << myStock.stockEntrys[i].open << " High: " << myStock.stockEntrys[i].high
                 << " Low: "  << myStock.stockEntrys[i].low  << " Close: "<< myStock.stockEntrys[i].close
                 << " Volume: " << myStock.stockEntrys[i].volume << " AdjClose: " << myStock.stockEntrys[i].adjClose << endl;
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

//Plotfunktionen
double getMax(Stock& myStock, int wert)
{
    double maxWert;
    //maxWert auf den ersten eintrag setzen
    switch(wert)
    {
    case 0:
        {
            maxWert = myStock.stockEntrys[0].open;
        }
    case 1:
        {
            maxWert = myStock.stockEntrys[0].high;
        }
    case 2:
        {
            maxWert = myStock.stockEntrys[0].low;
        }
    case 3:
        {
            maxWert = myStock.stockEntrys[0].close;
        }
    case 4:
        {
            maxWert = myStock.stockEntrys[0].volume;
        }
    case 5:
        {
            maxWert = myStock.stockEntrys[0].adjClose;
        }
    }
    //Max-Wert finden
    for(int i=1; i<myStock.entrySize; i++)
    {
        if(myStock.stockEntrys[i].date != "EMPTY")
        {
            switch(wert)
            {
            case 0:
                {
                    if(myStock.stockEntrys[i].open>maxWert)
                    {
                        maxWert=myStock.stockEntrys[i].open;
                    }
                    break;
                }
            case 1:
                {
                    if(myStock.stockEntrys[i].high>maxWert)
                    {
                        maxWert=myStock.stockEntrys[i].high;
                    }
                    break;
                }
            case 2:
                {
                    if(myStock.stockEntrys[i].low>maxWert)
                    {
                        maxWert=myStock.stockEntrys[i].low;
                    }
                    break;
                }
            case 3:
                {
                    if(myStock.stockEntrys[i].close>maxWert)
                    {
                        maxWert=myStock.stockEntrys[i].close;
                    }
                    break;
                }
            case 4:
                {
                    if(myStock.stockEntrys[i].volume>maxWert)
                    {
                        maxWert=myStock.stockEntrys[i].volume;
                    }
                    break;
                }
            case 5:
                {
                    if(myStock.stockEntrys[i].adjClose>maxWert)
                    {
                        maxWert=myStock.stockEntrys[i].adjClose;
                    }
                    break;
                }
            }
        }
    }
    return maxWert;
}

void plot(Stock& myStock, int wert)
{
   double maxWert = getMax(myStock, wert);
   int dataSetCounter=0;

    for(int i=0; i<myStock.entrySize; i++)
    {
        if(myStock.stockEntrys[i].date != "EMPTY")
        {
            dataSetCounter++;
            double z=0;
            cout << myStock.stockEntrys[i].date << ": ";

            switch(wert)
            {
            case 0:
                {
                    double compare = myStock.stockEntrys[i].open / maxWert * 100;
                    while(z <=compare)
                    {
                        cout << "|";
                        z++;
                    }
                    cout << endl << endl;
                    break;
                }
            case 1:
                {
                    double compare = myStock.stockEntrys[i].high / maxWert * 100;
                    while(z <=compare)
                    {
                        cout << "|";
                        z++;
                    }
                    cout << endl << endl;
                    break;
                }
            case 2:
                {
                    double compare = myStock.stockEntrys[i].low / maxWert * 100;
                    while(z <=compare)
                    {
                        cout << "|";
                        z++;
                    }
                    cout << endl << endl;
                    break;
                }
            case 3:
                {
                    double compare = myStock.stockEntrys[i].close / maxWert * 100;
                    while(z <=compare)
                    {
                        cout << "|";
                        z++;
                    }
                    cout << endl << endl;
                    break;
                }
            case 4:
                {
                    double compare = myStock.stockEntrys[i].volume / maxWert * 100;
                    while(z <=compare)
                    {
                        cout << "|";
                        z++;
                    }
                    cout << endl << endl;
                    break;
                }
            case 5:
                {
                    double compare = myStock.stockEntrys[i].adjClose / maxWert * 100;
                    while(z <=compare)
                    {
                        cout << "|";
                        z++;
                    }
                    cout << endl << endl;
                    break;
                }
            }
        }
    }
   if(dataSetCounter == 0)
    {
        cout << "No available Data for " << myStock.name << " yet." << endl;
    }

}

//Save Funktionen

void save(HashTable* hashTable, Stock* stockTable, int stockTableLength)
{
     //HashTable save
     std::ofstream hashFile;
     hashFile.open ("HashSave.csv");
      for(int i = 0; i<2011;i++)
      {
        hashFile << hashTable->Elements[i].name<< "," << hashTable->Elements[i].wkn << ","<< hashTable->Elements[i].memoryLocation<< endl;
      }
        hashFile.close();
    //Stocklist save
    std::ofstream stockFile;
    stockFile.open ("StockSave.csv");
        for(int i=0;i<stockTableLength;i++)
        {
            stockFile<< stockTable[i].name << "," << stockTable[i].wkn << "," << stockTable[i].kurzel << endl;
            //stockFile<< "Date,Open,High,Low,Close,Volume,Adj Close"<< endl;
            //cout << stockTable->entrySize;
            for(int y=0;y<stockTable->entrySize;y++) /** Hardcoded because for some reason stockTable->entrySize is always equal to five **/
            {
                stockFile<< stockTable[i].stockEntrys[y].date <<","<< stockTable[i].stockEntrys[y].open <<","<<stockTable[i].stockEntrys[y].high <<","<<stockTable[i].stockEntrys[y].low <<","<<stockTable[i].stockEntrys[y].close <<","<<stockTable[i].stockEntrys[y].volume <<","<<stockTable[i].stockEntrys[y].adjClose<< endl;
            }
        }
        stockFile.close();
}

//Import-Funktion

void import(HashTable* hashTable, Stock* stockTable, int stockTableLength) //change to 30 when done
{
    string line;
    char separator = ',';
    int columns = 3;
    ifstream saveFile;
    saveFile.open("HashSave.csv");
    int counter=0;

    if (saveFile.is_open() )
    {
        while( getline(saveFile,line)&& counter<2011)
        {
            std::stringstream linestream(line);
            string::size_type size_t;

            for(int i=0;i<columns;i++)
            {
                string temp;
                if(i==2)
                {
                    getline(linestream,temp,'\n');
                }
                else
                {
                    getline(linestream,temp,separator);
                }

                switch(i)
                {
                    case(0):
                    {
                         hashTable->Elements[counter].name = temp;
                         break;
                    }
                    case(1):
                    {
                         hashTable->Elements[counter].wkn = temp;
                         break;
                    }
                    case(2):
                    {
                         hashTable->Elements[counter].memoryLocation = std::stod(temp, &size_t);
                         break;
                    }
                }
            }
            counter++;
        }
        saveFile.close();
    }

    ifstream stockFile;
    saveFile.open("StockSave.csv");
    counter=0;
    DataSet firstThirtySets[30]; //change to 30? when done
    int stockCounter=0;
    int dataSetCounter=0;

        if (saveFile.is_open() )
    {
            while( getline(saveFile,line)&& counter<(2011*6))//Change this to 2011*6 once done
            {
                std::stringstream linestream(line);
                string::size_type size_t;
                columns =3;

                if(counter%6==0)
                {
                     for(int i=0;i<columns;i++)
                    {
                    string temp;
                    if(i==2)
                    {
                        getline(linestream,temp,'\n');
                    }
                    else
                    {
                        getline(linestream,temp,separator);
                    }

                    switch(i)
                    {
                        case(0):
                        {
                            stockTable[stockCounter].name = temp;
                            break;
                        }
                        case(1):
                        {
                            stockTable[stockCounter].wkn = temp;
                            break;
                        }
                        case(2):
                        {
                            stockTable[stockCounter].kurzel = temp;
                            break;
                        }
                    }
                    }
                    stockCounter++;
                }
                else
                {

                    //DataSet temporarySet;
                     if(dataSetCounter%30==0) //change this to 30 when done
                    {
                        dataSetCounter=0;
                    }
                    columns = 7;
                    for(int i=0; i < columns;i++)
                    {
                        string temp;
                        if(i==6)
                    {
                        getline(linestream,temp,'\n');
                    }
                    else
                    {
                        getline(linestream,temp,separator);
                    }

                    switch(i)
                    {
                    case 0:
                        stockTable[stockCounter-1].stockEntrys[dataSetCounter].date =temp;
                        break;
                    case 1:
                        stockTable[stockCounter-1].stockEntrys[dataSetCounter].open = std::stod(temp, &size_t);
                        break;
                    case 2:
                        stockTable[stockCounter-1].stockEntrys[dataSetCounter].high = std::stod(temp, &size_t);
                        break;
                    case 3:
                        stockTable[stockCounter-1].stockEntrys[dataSetCounter].low = std::stod(temp, &size_t);
                        break;
                    case 4:
                        stockTable[stockCounter-1].stockEntrys[dataSetCounter].close = std::stod(temp, &size_t);
                        break;
                    case 5:
                        stockTable[stockCounter-1].stockEntrys[dataSetCounter].volume = std::stod(temp, &size_t);
                        break;
                    case 6:
                        stockTable[stockCounter-1].stockEntrys[dataSetCounter].adjClose = std::stod(temp, &size_t);
                        break;
                    }
                    }

            dataSetCounter++;
            }

            counter++;
            }

        saveFile.close();
    }
}

int main()
{
    /** TO DO: Implement stockStorageArray and HashTable on the HEAP instead of the STACK.
        Other Functions will have to be adjusted a bit for that to work ( pass by reference for example with : *&myArray )

        TO DO: Implement LOAD/SAVE Table -> The only REAL Work still left to do. This one might get on our nerves.
               I have a basic import function for Stock Data in Place already, which might be useful.
     **/

    int stockDataSize = 2011;

    Stock* stockStorageArray = new Stock[stockDataSize];
    HashTable* nameTable = new HashTable;

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
                int positionInMemory = PutStockInMemory(newStock,stockStorageArray, stockDataSize);

                // Add Stock to HashTable
                HashTableEntry newEntry(name,wkn,positionInMemory);
                nameTable->Add(newEntry);
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
                int stockLocationInMemory = nameTable->FindByName(name);
                if(stockLocationInMemory != -1)
                {
                    deleteStockDataSets(stockStorageArray[stockLocationInMemory]);
                }
                 // Delete From HashTable
                nameTable->DeleteFromTable(name);
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
                int stockLocationInMemory = nameTable->FindByName(name);
                if(stockLocationInMemory != -1)
                {
                    try {
                        importStockData(fileName, stockStorageArray[stockLocationInMemory],stockDataSize); // Writes DIRECTLY into the given STOCK
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

                int stockLocationInMemory = nameTable->FindByName(name);
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
            {

                string name;
                int wert;
                cout << "Please enter the name of the Stock: ";
                cin >> name;
                cout << "(0)Get the OPEN Data" << endl;
                cout << "(1)Get the HIGH Data" << endl;
                cout << "(2)Get the LOW Data" << endl;
                cout << "(3)Get the CLOSE Data" << endl;
                cout << "(4)Get the VOLUME Data" << endl;
                cout << "(5)Get the ADJCLOSE Data" << endl;
                cin >> wert;

                if(wert > 5 || wert < 0)
                {
                    cout << "Something went wrong." << endl;
                }
                int stockLocationInMemory = nameTable->FindByName(name);

                if(stockLocationInMemory != -1)
                {
                    plot(stockStorageArray[stockLocationInMemory], wert);
                }

                if(stockLocationInMemory == -1)
                {
                    cout << "The stock with name " << name << " has been deleted from the Table." << endl;
                }
                displayOperationEndLine();
            }
            break;
        case 5:     // SAVE/EXPORT To File
            {
                cout << stockStorageArray->entrySize << endl;
                save(nameTable, stockStorageArray, stockDataSize);
                cout<<"done!"<<endl;
            }
            break;
        case 6:     // LOAD Table
            {
                import(nameTable, stockStorageArray, stockDataSize);
                cout<<"done!"<<endl;
            }
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
