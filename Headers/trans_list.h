/*H**************************************************************************************************************
 * FILENAME :       trans_list.h

 * DESCRIPTION :    
 *              Header file for transactions list data
 * 
 * AUTHOR :     Ahmed Osman                 START DATE :    22 May 2023
 * 
 * CHANGES : 
 * 
 *  VERSION       DATE              WHO             DETAIL
 *  1.0.0         22 May 2023       A.O             Made the file
 **************************************************************************************************************H*/

#ifndef TRANS_LIST_H
#define TRANS_LIST_H



#include "common.h"

typedef struct Transact
{
    s32                  amount;
    char                 type[10];
}Transact;


typedef struct TransNode
{
    Transact             data;
    struct TransNode   * pNext;
    struct TransNode   * pPrev;

}TransNode;

typedef struct TransList
{
    TransNode          * pHead;
    TransNode          * pTail;
    u32                  entryCount;
}TransList;



void        TRANS_CreateList( TransList * );
static bool TRANS_ListIsEmpty( TransList * );
void        TRANS_Append( TransList *, Transact );
void        TRANS_ClearList( TransList * );
void        TRANS_DisplayList( TransList * );


#endif




