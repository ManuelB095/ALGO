#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>

#include "Lnode.h"
#include "Tnode.h"


using namespace std;

Lnode* head = createLHead(); // Initialise List with empty node
Tnode* treeTop = NULL;

int main()
{
    srand(time(0));

    int avlkey[10] = {5,3,17,9,23,54,11,79,30,12};
    size_t keySetSize = sizeof(avlkey)/ sizeof(avlkey[0]);
    cout << keySetSize << endl;
    for(int i=0; i < keySetSize ; i++)
    {
        treeTop = appendTree(treeTop, avlkey[i]);
    }
    //displayList(head);
    treeToList(treeTop, head);
    displayList(head);

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
