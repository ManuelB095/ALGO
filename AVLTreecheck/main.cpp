#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>

#include "Lnode.h"
#include "Tnode.h"

using namespace std;

int importTreeData(string filename, vector<int>& storVec )
{
    ifstream treeFile;
    treeFile.open(filename);

    if(treeFile.is_open())
    {
        int temp = 0;
        while(treeFile >> temp)
        {
            storVec.push_back(temp);
        }
    }
    treeFile.close();
}

Lnode* head = createLHead(); // Initialise List with empty node
Tnode* treeTop = NULL;

int main()
{
    srand(time(0));
    vector<int> avlKeys;
    importTreeData("treeData.csv", avlKeys);

    for(vector<int>::iterator iter = avlKeys.begin(); iter != avlKeys.end(); ++iter)
    {
        treeTop = appendTree(treeTop, *iter);
    }

    cout << "Elements in Descending Order: " << endl;
    treeToList(treeTop, head);
    displayList(head);
    //size_t keySetSize = avlKeys.size();
    //cout << "SetSize: " << keySetSize << endl;

    cout << "Balance Factor: " << calcBalanceFactor(treeTop) << " " <<
    calcBalanceFactor(treeTop->right) << " " << calcBalanceFactor(treeTop->right->right)
    << " " << calcBalanceFactor(treeTop->right->right->right) << endl;

    cout << "With Run Check: " << endl;
    runCheck(treeTop);

    cout << endl;
    cout << "Results: " << endl;
    int rootBF = calcBalanceFactor(treeTop);
    if(rootBF > 1 || rootBF < -1)
    {
        cout << "|Avl: " << " NO";
    }
    else{
        cout << "|Avl: " << " YES";
    }
    cout << " |Min: " << findMin(treeTop);
    cout << " |Max: " << findMax(treeTop);
    cout << " |Average: " << findAverage(treeTop, 0) / (double)countElements(treeTop,0);
    cout << endl;

    freeMemory(head);
    freeTheTree(treeTop);

    return 0;
}
