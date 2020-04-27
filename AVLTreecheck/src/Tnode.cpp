#include "Tnode.h"

//Tnode* createTHead()
//{
//    Tnode* temp = (Tnode*)malloc(sizeof(Tnode));
//    temp->key = NULL;
//    temp->height = NULL;
//    temp->left = NULL;
//    temp->right = NULL;
//    return temp;
//}

Tnode* createTnode(int d)
{
    Tnode* temp = (Tnode*)malloc(sizeof(Tnode));
    temp->key = d;
    temp->height = NULL;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

Tnode* appendTree(Tnode* T, int value)
{
    // 3 Cases:

    // Leaf node found ! Or more precisely, a node AFTER! Here we create our new node with the value
    if(T == NULL)
    {
        T = createTnode(value);
    }

    // Value is bigger than T -> continue with RIGHT side of tree;
    else if(value > T->key)
    {
        T->right = appendTree(T->right, value);
    }

    // Value is smaller than head -> continue with LEFT side of tree;
    else if(value < T->key)
    {
        T->left = appendTree(T->left, value);
    }

    // Re-Calculate the height of every node we went through !
    T->height = height(T);
    return T;
}

int height(Tnode* T)
{
	int leftHeight;
	int rightHeight;
    // We reached a LEAF node. Finished. Now start recursion upwards.
	if(T == NULL)
		return(0);

	if(T->left == NULL)
		leftHeight = 0;
	else
		leftHeight = 1 + T->left->height;

	if(T->right == NULL)
		rightHeight=0;
	else
		rightHeight = 1 + T->right->height;

    // Return whichever height is the biggest. This will become the UPPER Nodes height
	if(leftHeight>rightHeight)
		return(leftHeight);
    else
        return(rightHeight);
}

int calcBalanceFactor(Tnode* T) // Almost the same as height. The difference is, that this returns the height DIFFERENCE instead of height itself
{
	int leftHeight;
	int rightHeight;

	if(T == NULL)
		return(0);

	if(T->left == NULL)
		leftHeight=0; // Should be 1 ?
	else
		leftHeight = 1 + T->left->height;

	if(T->right == NULL)
		rightHeight = 0; // Should be 1 ?
	else
		rightHeight = 1 + T->right->height;

	return(leftHeight - rightHeight);
}

void freeTheTree(Tnode* T)
{
    if(T == NULL)
    {
        return;
    }
    freeTheTree(T->left);
    freeTheTree(T->right);
    free(T);
    // T->key = NULL; ?
}
