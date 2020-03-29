#include <vector>
#include <string>
#include "HashTableEntry.h"
#include "HashTable.h"
#include "DataSet.h"
#include "Stock.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>    // Needed for Random Generator ( Dummy Fill ) -> Random Seed
#include <cstdlib>  // Needed for Random Generator ( Dummy Fill )

using std::cout;
using std::cin;
using std::endl;
using std::string;

using std::ifstream;

/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX**/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX**/

/** BEGINNING OF FUNCTIONS BLOCK **/

/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX**/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX**/


/** ////////////////////////////////////////////////////////////////////////////// **/

/** MENU FUNCTIONS **/

/** ////////////////////////////////////////////////////////////////////////////// **/
void displayMenu()
{
    cout << "(0)ADD New Stock ( by Name )" << endl;
    cout << "(1)DELETE Stock" << endl;
    cout << "(2)Import Data For Stock" << endl;
    cout << "(3)Find/Display Stock Data ( by Name )" << endl;
    cout << "(4)Plot Stock Data" << endl;
    cout << "(5)Save/Export to File" << endl;
    cout << "(6)Load Table" << endl;
    cout << "(7)DummyFill" << endl;
    cout << "(9)Exit Program" << endl;
}
void displayOperationEndLine()
{
    cout << "--------------------------------------------------" << endl;
    cout << endl;
}
/** ////////////////////////////////////////////////////////////////////////////// **/

/** FILE IMPORTS/EXPORTS **/

/** ////////////////////////////////////////////////////////////////////////////// **/
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

        while(getline(stockFile,line) && counter < MAXCOUNT)
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
    else{
        cout << "ERROR: Could not find/open file !" << endl;
    }
}

/** ////////////////////////////////////////////////////////////////////////////// **/

/** STOCK MEMORY FUNCTIONS **/

/** ////////////////////////////////////////////////////////////////////////////// **/

int findNextAvailablePosition(Stock* myStorageArray, int arrLength) // Searches for available Memory for the data of a new Stock
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

/** PLOT FUNCTIONS **/

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

/** ////////////////////////////////////////////////////////////////////////////// **/

/**SAVE AND LOAD TABLE FUNCTIONS **/

/** ////////////////////////////////////////////////////////////////////////////// **/

//Save Funktionen

void save(HashTable* hashTable,HashTable* wknTable, Stock* stockTable, int stockTableLength)
{
     //HashTable save
     std::ofstream hashFile;
     hashFile.open ("HashSave.csv");
      for(int i = 0; i<2011;i++)
      {
        hashFile << hashTable->Elements[i].name<< "," << hashTable->Elements[i].wkn << ","<< hashTable->Elements[i].memoryLocation<< endl;
      }
        hashFile.close();
     //WKN-HashTable save
     std::ofstream wknFile;
     wknFile.open ("WKNSave.csv");
      for(int i = 0; i<2011;i++)
      {
        wknFile << wknTable->Elements[i].name<< "," << wknTable->Elements[i].wkn << ","<< wknTable->Elements[i].memoryLocation<< endl;
      }
        wknFile.close();
    //Stocklist save
    std::ofstream stockFile;
    stockFile.open ("StockSave.csv");
        for(int i=0;i<stockTableLength;i++)
        {
            stockFile<< stockTable[i].name << "," << stockTable[i].wkn << "," << stockTable[i].kurzel << endl;
            for(int y=0;y<stockTable->entrySize;y++)
            {
                stockFile<< stockTable[i].stockEntrys[y].date <<","<< stockTable[i].stockEntrys[y].open <<","<<stockTable[i].stockEntrys[y].high <<","<<stockTable[i].stockEntrys[y].low <<","<<stockTable[i].stockEntrys[y].close <<","<<stockTable[i].stockEntrys[y].volume <<","<<stockTable[i].stockEntrys[y].adjClose<< endl;
            }
        }
        stockFile.close();
}

//Import-Funktion

void import(HashTable* hashTable, HashTable* wknTable, Stock* stockTable, int stockTableLength)
{
    string line;
    char separator = ',';
    int columns = 3;
    ifstream saveFile;
    saveFile.open("HashSave.csv");
    int counter=0;

    // Load Data For Name Hash-Table

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

    // Load Data for WKN Hash-Table

    line = "";
    separator = ',';
    columns = 3;
    ifstream saveWKNFile;
    saveWKNFile.open("WKNSave.csv");
    counter=0;

    if (saveWKNFile.is_open() )
    {
        while( getline(saveWKNFile,line)&& counter<2011)
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
                         wknTable->Elements[counter].name = temp;
                         break;
                    }
                    case(1):
                    {
                         wknTable->Elements[counter].wkn = temp;
                         break;
                    }
                    case(2):
                    {
                         wknTable->Elements[counter].memoryLocation = std::stod(temp, &size_t);
                         break;
                    }
                }
            }
            counter++;
        }
        saveWKNFile.close();
    }

    ifstream stockFile;
    saveFile.open("StockSave.csv");
    counter=0;
    DataSet firstThirtySets[30];
    int stockCounter=0;
    int dataSetCounter=0;

        if (saveFile.is_open() )
    {
            while( getline(saveFile,line)&& counter<(2011*31)) // ( 30 for Stock Data + 1 for Stock Info times 2011 for all possible Entrys )
            {
                std::stringstream linestream(line);
                string::size_type size_t;
                columns =3;

                if(counter%31==0)
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
                     if(dataSetCounter%30==0)
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

/** ////////////////////////////////////////////////////////////////////////////// **/

/** DUMMY FILL **/

/** ////////////////////////////////////////////////////////////////////////////// **/

void dummyFill(HashTable* myTable,HashTable* mySecondTable, Stock* myStorageArray, int storArrLength)
{
    for(int i=0; i < 1500; i++ ) // Make 1500 random dummy entrys
    {
        string istring = "";
        string wstring = "";
        for(int j=0; j<5;j++) // WKN and Name consist of random ASCII chars
        {
            int randomNumber = std::rand() % 26 + 65;
            char randomAscii = (char)randomNumber;
            istring = istring + randomAscii;

            int randomWKN = std::rand() %26 + 65;
            char randomWKNchar = (char)randomWKN;
            wstring = wstring + randomWKNchar;
        }

          // Add Stock to Memory
            string counterString = std::to_string(i);
            Stock newStock(istring,wstring,counterString);
            int positionInMemory = PutStockInMemory(newStock,myStorageArray, storArrLength);
            if(positionInMemory == -1)
            {
                cout << "ERROR: Dummy Fill threw an error while writing Data into Memory !";
            }
          // Add Stock to Name Hash Table
            HashTableEntry temp(istring,wstring,i);
            myTable->Add(temp);
          // Add Stock to WKN Hash Table
            mySecondTable->AddViaWKN(temp);
    }
}

/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX**/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX**/

/** END OF FUNCTIONS BLOCK **/

/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX**/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX**/


int main()
{
    std::srand(std::time(nullptr)); // Generates Random Seed for rand() function to work properly
    int stockDataSize = 2011;       // Size of Memory Array ( depending on HashTable Size )

    Stock* stockStorageArray = new Stock[stockDataSize]; // Memory Storage for Stocks and their Course Data
    HashTable* nameTable = new HashTable;                // Hash Table for Names
    HashTable* wknTable = new HashTable;                 // Hash Table for WKN

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

                // Add Stock to WKN-Table
                wknTable->AddViaWKN(newEntry);

                //cout << "Successfully added new Stock: " << stockStorageArray[0].name << endl;
                displayOperationEndLine();
                break;
            }
        case 1:         // Delete Stock
            {
                cout << "Info: WKN and Name needed since BOTH Tables AND Memory has to be deleted.." << endl
                     << ".. in order to ensure a safe deletion mechanism." << endl;
                string name;
                cout << "Please enter the name of the Stock: ";
                cin >> name;
                string wkn;
                cout << "Please enter the wkn of the Stock: ";
                cin >> wkn;

                // Delete From Memory
                int stockLocationInMemory = nameTable->FindByName(name);
                if(stockLocationInMemory != -1)
                {
                    deleteStockDataSets(stockStorageArray[stockLocationInMemory]);
                }
                 // Delete From HashTable
                nameTable->DeleteFromTable(name);
                 // Delete From WknTable
                wknTable->DeleteFromTableViaWKN(wkn);
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
                        importStockData(fileName, stockStorageArray[stockLocationInMemory],30); // Writes DIRECTLY into the given STOCK
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
                cout << "(1) Find by Name" << endl;
                cout << "(2) Find by WKN" << endl;
                int opFind;
                cin >> opFind;
                if(opFind == 1)
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
                        cout << "The stock with name " << name << " has already been deleted from the Table." << endl;
                    }
                }
                else if(opFind == 2)
                {
                    string wkn;
                    cout << "Please enter the WKN of the Stock: ";
                    cin >> wkn;

                    int stockLocationInMemory = wknTable->FindByWKN(wkn);
                    // Print everything thats in "Stock"
                    if(stockLocationInMemory != -1)
                    {
                        printStockDataSets(stockStorageArray[stockLocationInMemory]);
                    }
                    else if(stockLocationInMemory == -1)
                    {
                        cout << "The stock with WKN " << wkn << " has already been deleted from the Table." << endl;
                    }
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
                save(nameTable, wknTable, stockStorageArray, stockDataSize);
                cout<<"Successfully saved Data!"<<endl;
            }
            break;
        case 6:     // LOAD Table
            {
                import(nameTable, wknTable, stockStorageArray, stockDataSize);
                cout<<"Successfully loaded Data!"<<endl;
            }
            break;
        case 7:     // Dummy Fill
            dummyFill(nameTable,wknTable, stockStorageArray,stockDataSize);
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
    } // -> END OF PROGRAM WHILE LOOP
    // -> END OF MAIN :
    return 0;
}
