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

	return(rightHeight - leftHeight);
}

void runCheck(Tnode* T) // Reverse Postorder
{
    if (T == NULL)
        return;

    // first recur on right subtree
    runCheck(T->right);

    // then recur on left subtree
    runCheck(T->left);

    // After Recursion Code for every node
    int BF = calcBalanceFactor(T);
    if(BF!=0)
    {
        std::cout << "bal(" << T->key << ") = " << BF << " (AVL Violation !)" << std::endl;
    }
    else
    {
        std::cout << "bal(" << T->key << ") = " << BF << " (OK)" << std::endl;
    }
}

int findMin(Tnode* T)
{
    while(T->left != NULL)
    {
        T = T->left;
    }
    int temp = T->key;
    return temp;
}
int findMax(Tnode* T)
{
    while(T->right != NULL)
    {
        T = T->right;
    }
    int temp = T->key;
    return temp;
}

int findAverage(Tnode* T, int keySum)
{
    if(T == NULL)
    {
        return keySum;
    }
    keySum = findAverage(T->right, keySum);
    keySum = findAverage(T->left, keySum);

    keySum += T->key;
    return keySum;
}

int countElements(Tnode* T, int counter)
{
    if(T == NULL)
    {
        return counter;
    }
    counter = countElements(T->right, counter);
    counter = countElements(T->left, counter);

    counter++;
    return counter;
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
