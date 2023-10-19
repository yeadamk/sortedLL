// ============================================================================
// File: sortedll.h by Yeadam Kim
// ============================================================================

#ifndef SORTEDLL_H
#define SORTEDLL_H

// Preprocessor statements
#define BUFLEN 256
#define FALSE 0
#define TRUE 1

// Structure declarations
typedef struct LNode
{
    int value;
    struct LNode *next;

} LNode;

// Function prototypes
LNode *AddItem(LNode *headPtr, int newItem);
int DisplayList(const LNode *nodePtr);
void DisplayMenu(void);
int FreeList(LNode **headPtr);
LNode *RemoveItem(LNode *headPtr, int target);

#endif // SORTEDLL_H
