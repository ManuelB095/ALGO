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

    int avlkey[3];
    size_t keySetSize = sizeof(avlkey)/ sizeof(avlkey[0]);
    cout << keySetSize << endl;
    for(int i=0; i < keySetSize ; i++)
    {
        avlkey[i] = rand() % 101; // 0 - 100;
        head = appendList(head, avlkey[i]);
        treeTop = appendTree(treeTop, avlkey[i]);
    }
    displayList(head);
    treeToList(treeTop, head);
    displayList(head);

    freeMemory(head);
    freeTheTree(treeTop);

    return 0;
}
