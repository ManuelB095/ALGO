#include "Lnode.h"

// Lnode FUNCTIONS

Lnode* createLHead()
{
    Lnode* temp = (Lnode*)malloc(sizeof(Lnode));
    temp->key = NULL;
    temp->next = NULL;
    return temp;

}

Lnode* createLnode(int d)
{
    Lnode* temp = (Lnode*)malloc(sizeof(Lnode));
    temp->key = d;
    temp->next = NULL;
    return temp;
}

Lnode* appendList(Lnode* head, int base)
{
    // Iterate through head
    Lnode* p = head;
    // Create new Lnode to append
    Lnode* temp = (Lnode*)malloc(sizeof(Lnode));
    temp->key = base;
    temp->next = NULL;

    // 2 Cases:
    if(head->key == NULL)
    {
        head->key = base;
        return head;
    }

    while(p->next != NULL)
    {
        p = p->next;
    }
    p->next = temp;
    return head;
}

Lnode* prependList(Lnode* head, int base)
{
    if(head->key == NULL)
    {
        head->key = base;
        return head;
    }
    // Create new Lnode to prepend
    Lnode* temp = (Lnode*)malloc(sizeof(Lnode));
    temp->key = base;
    temp->next = head;
    // MOST IMPORTANT STEP!! temp will become new head!
    return temp;
}

Lnode* insertAfter(Lnode* head, int base, int pos)
{
    Lnode* p = head;
    pos -= 1; // !! Is pos is 1-based!
    int count = 0;
    while(p!=NULL && count < pos)
    {
        p = p->next;
        count++;
    }

    Lnode* temp = (Lnode*)malloc(sizeof(Lnode));
    temp->key = base;
    // Order is important here! First establish connection from new Lnode to rest of list. Then from p to new Lnode!
    temp->next = p->next;
    p->next = temp;

    return head;
}

Lnode* deleteAt(Lnode* head, int pos)
{
    pos -= 1; // 1based!
    int count = 0;
    Lnode* p = head;

    if(pos == 0) // Special Case: Delete first Lnode.
    {
        Lnode* newHead = head->next;
        free(head);
        return newHead;
    }

    while(p!=NULL && count < pos - 1 ) // To delete at current, we must find previous Lnode!
    {
        p = p->next;
        count++;
    }
    Lnode* temp = p->next->next; // Establish temporary connection from current to next->next Lnode to be able to delete p->next
    free(p->next); // Free the Lnode to be deleted
    p->next = temp; // Set the next Lnode at current position to next->next Lnode in list.
    return head; // return head with updated elements.
}

Lnode* treeToList(Tnode* T, Lnode* L)
{
    if(T == NULL)
        return L;
    else{
        Lnode* temp = treeToList(T->right, L);
        temp = appendList(L, T->key);
        temp = treeToList(T->left, L);
    }
}


void displayList(Lnode* head)
{
    printf("\n");
    int counter = 0;
    Lnode* p = head;
    while(p != NULL)
    {
        printf("->%d", p->key);
        p = p->next;
        counter++;
    }
    printf("\n%d key(s)\n", counter);
}

Lnode* reverseList(Lnode* head)
{
    Lnode* newHead = (Lnode*)malloc(sizeof(Lnode)); // New empty Lnode for new List
    newHead->key = NULL;
    newHead->next = NULL;

    Lnode* p = head; // Laufvariable p iteriert durch alte Liste.

    while(p != NULL)
    {
        newHead = prependList(newHead, p->key);
        p = p->next;
    }
    freeMemory(head); // !!! head List is unchanged! Must be set free!!!
    return newHead;
}

void freeMemory(Lnode* head)
{
    Lnode* current = head;
    while(current != NULL)
    {
        head = head->next;
        free(current);
        current = head;
    }
}
