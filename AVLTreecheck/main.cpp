#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>

#include "Lnode.h"
#include "Tnode.h"

// Use Clauses
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

// Helper Functions
void importTreeData(string filename, vector<int>& storVec );
bool alreadyInTree(int value, vector<int>& storVec);
// Important Globals
Lnode* head = createLHead(); // Initialise List with empty node
Tnode* treeTop = NULL;

int main() // int main (argc , char * argv[]) More on this at the Bottom of main.cpp
{
    /** Set Random Seed **/
    srand(time(0));

    /** Ask for Import File **/
    string inputFile; // treeData.csv
    cout << "Please specify the input file for treecheck: " << endl;
    cin >> inputFile;
    cout << endl;


    /** Import Data for Binary Tree **/
    vector<int> avlKeys;
    try{
        importTreeData(inputFile, avlKeys);
    }
    catch(std::exception& e)
    {
        cout << e.what() << endl;
        return 1;
    }

    for(vector<int>::iterator iter = avlKeys.begin(); iter != avlKeys.end(); ++iter)
    {
        treeTop = appendTree(treeTop, *iter);
    }


    /** Display Tree Elements via Linked List **/
    cout << "Elements in Descending Order: " << endl;
    treeToList(treeTop, head);
    displayList(head);
    cout << endl;


    /** Determine+Display Results **/
    cout << "Results: " << endl;
    if(isAVL(treeTop))
        cout << "|Avl: " << " YES";
    else{
        cout << "|Avl: " << " NO";
    }
    int minimum = treeTop->key;
    int maximum = treeTop->key;
    cout << " |(Used) MinMax-Recursive"; MinMaxRecurse(treeTop, minimum, maximum);
    cout << " |Min: " << minimum; // Old non-recursive Functions << findMin(treeTop);
    cout << " |Max: " << maximum; // Old non-recursive Functions << findMax(treeTop);
    cout << " |Average: " << findAverage(treeTop);  //(treeTop, 0) / (double)countElements(treeTop,0);
    cout << endl;


    /** Free Memory of List and Binary Tree **/
    freeMemory(head);
    freeTheTree(treeTop);

    return 0;
}

void importTreeData(string filename, vector<int>& storVec )
{
    ifstream treeFile;
    treeFile.open(filename);

    if(treeFile.fail())
    {
        throw std::runtime_error("Could not open file!");
    }

    if(treeFile.is_open())
    {
        int temp = 0;
        while(treeFile >> temp)
        {
            if(!alreadyInTree(temp, storVec))
            {
                storVec.push_back(temp);
            }
        }
    }
    treeFile.close();
}

bool alreadyInTree(int value, vector<int>& storVec)
{
    for(vector<int>::iterator i = storVec.begin(); i != storVec.end(); ++i )
    {
        if (*i == value)
        {
            return true;
        }
    }
    return false;

}


/**
Since we may or may not have to open the exe on the command line and enter arguments, I prepared a quick guide on how to
implement that.

First, change your main from this: int main() {
To this : int main (int argc, char * argv[]) {
This will allow the program to take values given by the console.

In the console, open the exe as follows:
/SomeFolders/AVLTreecheck.exe 1 treeData.csv // Or maybe "treeData.csv" haven`t tried it out yet.

This sets argumentCount ( argc to 1 ) and the filename (argv) to "treeData.csv"
With this, you can simply check if the right argument count is given ( if not prompt again for the filename ! ), parse the
char array to std::string ( for each character string += character ) and set
inputFile equal to that.

Now, with this, we should be Set.

!IMPORTANT! : You can still debug this. Got to Project->Set Program`s Arguments and select 'Debug'.
There, type the arguments like you would normally do in the console

 **/

