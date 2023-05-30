/*H**************************************************************************************************************
 * FILENAME :       account_list.h

 * DESCRIPTION :    
 *              Header file for the account list doubly linked list implementation
 * 
 * AUTHOR :     Ahmed Osman                 START DATE :    18 May 2023
 * 
 * CHANGES : 
 * 
 *  VERSION       DATE              WHO             DETAIL
 *  1.0.0         18 May 2023       A.O             Made the file
 *  1.0.0         22 May 2023       A.O             Added more functions related to the project
 **************************************************************************************************************H*/

#ifndef ACCOUNT_LIST_H
#define ACCOUNT_LIST_H

#include "account.h"

typedef Account     ListEntry;                             /* define Account as ListEntry to easily use the same code for other implementations */


typedef struct ListNode
{
    ListEntry             data;
    struct ListNode     * pNext;
    struct ListNode     * pPrev;

}ListNode;

typedef struct AccList
{
    ListNode            * pHead;
    ListNode            * pTail;
    u32                   entryCount;
}AccList;



void        LIST_CreateList(AccList*);
void        LIST_NewAccount(AccList*);
static bool LIST_ListIsEmpty(AccList*);
void        LIST_Append(AccList*, ListEntry*);
ListNode *  LIST_SearchList(AccList*, char*);
void        LIST_Insert(AccList*, ListEntry*);
void        LIST_Delete(AccList*);
void        LIST_ClearList(AccList*);
void        LIST_DisplayList(AccList*);
void        LIST_SortList(AccList*);
static void LIST_SwapNodes(ListNode* , ListNode*);
void        LIST_MainMenu();
void        LIST_ChooseAccMenu(AccList*);



#endif