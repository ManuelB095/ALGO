#ifndef TNODE_H
#define TNODE_H

#include <stdlib.h>
#include <iostream>

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
int findMin(Tnode* T);
int findMax(Tnode* T);
double findAverage(Tnode* T);
bool isAVL(Tnode* T);

void findAvgValues(Tnode* T, int& keySum, unsigned int& counter);
void runCheck(Tnode* T, bool& isAVL);
void freeTheTree(Tnode* T);
#endif // TNODE_H
