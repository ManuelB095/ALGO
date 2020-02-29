#include <vector>
#include <string>
#include "HashTableEntry.h"
#include "HashTable.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
//    string file_path = "./msft.csv";
//    char delimiter = ',';  // by default: ','
//    CSV csv = CSV(file_path);
//
//    // Read file
//    vector<vector<string>> data = csv.read();
//
//    // Write file
//    vector<string> row = { "r0c0", "r0c1" };
//    char method = 'w'; // 'w' - write data to a new file, by default
//    csv.write_row(row);
//
//    vector<vector<string>> rows = { { "r0c0", "r0c1" }, { "r1c0", "r1c1" } };
//    method = 'a'; // 'a' - append data to a file
//    csv.write_rows(rows, method);

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

    /** TEST: READ IN test Data into entry element ( pls do not change, need values for second test ! **/
    vector<string>testVector (7,"0");
    HashTableEntry testEntry("Test","0001","T1", testVector);

    /** TEST: READ HashTableEntrys into HashTable **/

    HashTable myTable(1001);

    myTable.Add(testEntry); // Puts testEntry on position 261 in table;
    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 262; Offset 2^0 = 1
    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 263; Offset 2^1 = 2
    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 265 ; Offset 2^2 = 4
    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 269 ; Offset 2^3 = 8
    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 277 ; Offset 2^4 = 16
    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 293 ; Offset 2^5 = 32
    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 325 ; Offset 2^6 = 64
    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 389 ; Offset 2^7 = 128
    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 517 ; Offset 2^8 = 256
    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 773 ; Offset 2^9 = 512
    myTable.Add(testEntry); // Tests quadratic probing: testEntry again on position 1285%1001 = 284 ; Offset 2^10 = 1024 CRITICAL SECTION HERE!

    /** All Tests up to here ran successfully ! **/









}
