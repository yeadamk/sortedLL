// ============================================================================
// sortedll.c by Yeadam Kim
// ============================================================================
// This program allows the user to manipulate the contents of a list of
// integers in a singly-linked list. The list items are maintained in sorted
// ascending order, and duplicate values are permitted.
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sortedll.h"

#define NEWLINE puts("");

// ==== main ==================================================================
//
// ============================================================================

int main(void)
{
  auto int intVal;
  auto LNode *headPtr = NULL;
  auto char buf[BUFLEN];
  auto int numItems;

  do
  {
    // Ask the user what they want to do and handle their choice
    DisplayMenu();
    printf("Please enter a selection: ");
    fgets(buf, BUFLEN, stdin);
    *buf = toupper(*buf);
    switch (*buf)
    {
    case 'A':
      printf("Please enter an integer value to add: ");
      fgets(buf, BUFLEN, stdin);
      if (1 != sscanf(buf, "%d", &intVal))
      {
        puts("Error reading the integer value...");
      }
      else
      {
        headPtr = AddItem(headPtr, intVal);
      }
      break;

    case 'R':
      if (NULL == headPtr)
      {
        puts("The list is already empty...");
      }
      else
      {
        printf("Please enter an integer value to remove: ");
        fgets(buf, BUFLEN, stdin);
        if (1 != sscanf(buf, "%d", &intVal))
        {
          puts("Error reading the integer value...");
        }
        else
        {
          headPtr = RemoveItem(headPtr, intVal);
        }
      }
      break;

    case 'D':
      // Display the current contents of the list
      NEWLINE
      numItems = DisplayList(headPtr);
      printf("*** main -- currently there %s %d node%s in the list...\n", (numItems != 1) ? "are" : "is", numItems, (numItems != 1) ? "s" : "");
      break;

    case 'F':
    case 'Q':
      // User wants to either clear the list or quit the program, so
      // Release all nodes in the list
      numItems = FreeList(&headPtr);
      printf("*** main -- there %s %d node%s released...\n", (numItems != 1) ? "were" : "was", numItems, (numItems != 1) ? "s" : "");
      break;

    default:
      puts("Unrecognized option; please try again.");
      break;
    }

    // Write out a blank line before next loop iteration
    puts("");

  } while ('Q' != *buf);

  puts("Thanks for playing!  Bye!!\n");
  return 0;

} // End of "main"

// ==== AddItem ===============================================================
//
// This function inserts an item into the list by dynamically allocating a node
// to store the value and locating the correct position for the new item so
// that the list is maintained in ascending sorted order.
//
// Input:
//      headPtr [IN]        -- a pointer to the first node in the list
//
//      newItem [IN]        -- the new item to insert into the list
//
// Output:
//      A pointer to the head of the list.

// ============================================================================

LNode *AddItem(LNode *headPtr, int newItem)
{
  auto LNode *nodePtr = headPtr;
  auto LNode *trailPtr = headPtr;

  // Create a new node
  LNode *newNode = malloc(sizeof(LNode));

  // Check if new node was created
  if (NULL == newNode)
  {
    return NULL; // Error occured
  }

  // Set int value to newNode
  newNode->value = newItem;

  // If list is empty
  if (NULL == headPtr)
  {
    newNode->next = NULL;
    return newNode; // New headPtr
  }

  // Find where to add the new node
  while (NULL != nodePtr)
  {
    if (nodePtr->value >= newItem)
    {
      break;
    }
    else
    {
      trailPtr = nodePtr;
    }

    nodePtr = nodePtr->next;
  }

  // Adding front
  if (nodePtr == headPtr)
  {
    newNode->next = headPtr;
    return newNode; // New headPtr
  }

  // Adding last
  if (NULL == nodePtr)
  {
    newNode->next = NULL;
    trailPtr->next = newNode;
    return headPtr; // Original headPtr
  }

  // Adding somewhere in the middle
  trailPtr->next = newNode;
  newNode->next = nodePtr;
  return headPtr; // Original headPtr

} // End of "AddItem"

// ==== DisplayList ===========================================================
//
// This function displays all of the values contained in the linked list to the
// standard output stream.
//
// Input:
//      headPtr [IN]        -- a pointer to the first node in the list
//
// Output:
//      The total number of nodes displayed is returned.
//
// ============================================================================

int DisplayList(const LNode *nodePtr)
{
  auto int counter = 0;

  // If the list is empty, indicate as such and return zero
  if (NULL == nodePtr)
  {
    // puts("*** DisplayList -- the list is currently empty...");
    return 0;
  }

  while (NULL != nodePtr)
  {
    printf("%d\n", nodePtr->value);
    nodePtr = nodePtr->next;
    counter++;
  }

  return counter;

} // End of "DisplayList"

// ==== DisplayMenu ===========================================================
//
// This function displays the menu to stdout.
//
// Input:
//      Nothing
//
// Output:
//      Nothing
//
// ============================================================================

void DisplayMenu(void)
{
  // write out a leading blank line, followed by menu items
  puts("A)dd a value");
  puts("R)emove a value");
  puts("D)isplay the list");
  puts("F)ree the list");
  puts("Q)uit");

} // End of "DisplayMenu"

// ==== FreeList ==============================================================
//
// This function traverses the linked list and releases the memory allocated
// for each individual node, and the caller's head node pointer is set to NULL.
//
// Input:
//      headPtr [IN/OUT]    -- the address of the caller's head node pointer
//
// Output:
//      The total number of nodes released is returned.
//
// ============================================================================

int FreeList(LNode **headPtr)
{
  auto int counter = 0;
  auto LNode *nodePtr = *headPtr;
  auto LNode *tempPtr = NULL;

  // Ff the list is empty, indicate as such and return zero
  if (NULL == nodePtr)
  {
    // puts("*** DisplayList -- the list is currently empty...");
    return 0;
  }

  while (NULL != nodePtr)
  {
    tempPtr = nodePtr->next;
    free(nodePtr);
    nodePtr = tempPtr;
    counter++;
  }

  *headPtr = NULL;

  return counter;

} // End of "FreeList"

// ==== RemoveItem ============================================================
//
// This function removes an item from the list.  If the target item is located
// in the list, the memory allocated for its node is released and any adjacent
// nodes are joined so as not to break the list.
//
// Input:
//      headPtr [IN]        -- a pointer to the first node in the list
//
//      target [IN]         -- the item to remove
//
// Output:
//      A pointer to the (potentially new) head of the list
//
// ============================================================================

LNode *RemoveItem(LNode *headPtr, int target)
{
  // Extra variables for clarity
  auto LNode *nodePtr = headPtr;
  auto LNode *trailPtr = headPtr;
  auto LNode *targetPtr = NULL;

  // Find target pointer (targetPtr)
  while (NULL != nodePtr)
  {
    if (nodePtr->value == target)
    {
      targetPtr = nodePtr;
      break;
    }
    else
    {
      trailPtr = nodePtr;
    }

    nodePtr = nodePtr->next;
  }

  // If target is not found
  if (NULL == targetPtr)
  {
    return headPtr;
  }

  // If first list contains target
  if (targetPtr == headPtr)
  {
    nodePtr = targetPtr->next;
    free(targetPtr);
    return nodePtr;
  }

  // If last list contains target
  if (NULL == targetPtr->next)
  {
    trailPtr->next = NULL;
    free(targetPtr);
    return headPtr;
  }

  // Else...
  trailPtr->next = targetPtr->next;
  free(targetPtr);
  return headPtr;

} // End of "RemoveItem"
