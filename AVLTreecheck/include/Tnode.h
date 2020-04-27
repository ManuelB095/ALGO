#ifndef TNODE_H
#define TNODE_H

#include <stdlib.h>

typedef struct Tnode {

    int key;
    int height;
    struct Tnode* left;
    struct Tnode* right;

} Tnode;

//Tnode* createTHead();
Tnode* createTnode(int d);
Tnode* appendTree(Tnode* T, int value);

int height(Tnode* T);
int calcBalanceFactor(Tnode *T);

void freeTheTree(Tnode* T);




#endif // TNODE_H
