#ifndef Lnode_H
#define Lnode_H

#include <stdio.h>
#include <stdlib.h>
#include "Tnode.h"

typedef struct Lnode { // I briefly thought about using STL`s list container, but decided it would be easier this way, given what we know about the topic already

    int key;
    struct Lnode* next;

} Lnode;

Lnode* createLHead();
Lnode* createLnode(int d);
Lnode* appendList(Lnode* head, int d);
Lnode* prependList(Lnode* head, int d);
Lnode* insertAfter(Lnode* head, int d, int pos);
Lnode* deleteAt(Lnode* head, int pos);
Lnode* reverseList(Lnode* head);
void displayList(Lnode* head);
void freeMemory(Lnode* head);

Lnode* treeToList(Tnode* T, Lnode* L);


#endif // LLnode_H
