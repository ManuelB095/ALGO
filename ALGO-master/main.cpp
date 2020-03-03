#include <vector>
#include <string>
#include "HashTableEntry.h"
#include "HashTable.h"
#include "DataSet.h"
#include <iostream>
#include <sstream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;

using std::ifstream;

int main()
{
    /** TO DO: IMPORT Data from csv file ( in current folder ) into a VECTOR with type string.
               ALSO Add NAME, WKN, and KURZ ( = Kürzel ) to every line in the csv.
               SAVE every string ( from NAME to the DATA like Date, Open, High, Low into a class obect like this:
               HashTableEntry newEntry("NAME","WKN(as String!), "KURZ", dataVector)

               I would THEN suggest, we make an array of HashTableEntrys like so:
               HashTableEntry allEntrys[numberOfEntrys];
               WHICH we fill with all our entrys.

               LASTLY Just make a for loop and for every element type: myTable.Add(allEntrys[i]).
               The table will take care of saving and searching by itself

    **/

    HashTable csvTestTable(1001);                                      // Array of all HashTableEntrys
    DataSet* firstThirtySets = NULL;                                   // This class is for the WHOLE Data accompanying the stocks.
    firstThirtySets = new DataSet[5];                                // Save the first 30 datasets in array; ( 5 now for debugging reasons.

    string line;
    char separator = ',';           // How are the columns separated
    int columns = 7;                // How many columns do we expect to read in ?
    ifstream stockFile;
    stockFile.open("msft.csv");

    // This is for testing the PLOT Function
    DataSet set1("2020-03-01",10,10,10,10,10,10); // Format : JAHR/MONAT/TAG
    DataSet set2("2020-03-02",20,20,20,20,20,20);
    DataSet set3("2020-03-03",30,30,30,30,30,30);
    DataSet set4("2020-03-04",40,40,40,40,40,40);
    DataSet set5("2020-03-05",50,50,50,50,50,50);

    DataSet setVektor[5];
    setVektor[0] = set1;
    setVektor[1] = set2;
    setVektor[2] = set3;
    setVektor[3] = set4;
    setVektor[4] = set5;

    HashTableEntry testingThis("Microsoft","001","ST1", setVektor);

    cout << testingThis.stockData[0].open << endl;
    cout << testingThis.stockData[3].open << endl;
    cout << testingThis.stockData[0].date << endl<<endl;

    //PLOT Function
    for(int i=0;i<5;i++)
    {
        cout << testingThis.stockData[i].date << ": |";

        double z=1;
        while(z <=testingThis.stockData[i].open)
        {
            cout << "|";
            z=z+1;

        }
        cout << endl;
    }

    cout << endl;




    HashTableEntry StockEntry("Microsoft","0001","ST1"); /** Warning: This causes potential memory leaks **/

    // Everything below is for reading the column data into datasets. The first 30 lines ( 30 datasets ) will then be saved to StockEntry
    if(stockFile.is_open())
    {
        getline(stockFile,line); // Read in first line ( = Headlines of the columns ) and discard it.
        int counter = 0;

        while(getline(stockFile,line) && counter < 5)
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
            cout << temporarySet.date << " " << temporarySet.close << " " << temporarySet.high << " " << temporarySet.adjClose << endl;
            firstThirtySets[counter] = temporarySet;
            counter++;
        }
        // Now that firstThirtySets is full ( hopefully ), lets add it to our table.
        StockEntry.stockData[0] = firstThirtySets[0];
        StockEntry.stockData[1] = firstThirtySets[1];
        StockEntry.stockData[2] = firstThirtySets[2];
        StockEntry.stockData[3] = firstThirtySets[3];
        StockEntry.stockData[4] = firstThirtySets[4];

        csvTestTable.Add(StockEntry); // Test Hash Table Adding System
        csvTestTable.Add(StockEntry);
        csvTestTable.Add(StockEntry);
        csvTestTable.Add(StockEntry);
        csvTestTable.Add(StockEntry);

        stockFile.close();
    }

    // To Do: Memory De-Allocation AT THE END OF THE PROGRAM.
    delete[] firstThirtySets;







    /** TEST: READ IN test Data into entry element ( pls do not change, need values for second test ! **/
    HashTableEntry testEntry("Test","0001","T1");

    /** TEST: READ HashTableEntrys into HashTable **/

//    HashTable myTable(1001);
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

    /** All Tests up to here ran successfully ! **/









}
