/*H**************************************************************************************************************
 * FILENAME :       trans_list.c

 * DESCRIPTION :    
 *              Double list implementation for transactions list
 * 
 * AUTHOR :     Ahmed Osman                 START DATE :    22 May 2023
 * 
 * CHANGES : 
 * 
 *  VERSION       DATE              WHO             DETAIL
 *  1.0.0         22 May 2023       A.O             Made the file
 **************************************************************************************************************H*/

#include "../Headers/trans_list.h"

/**************************************************************************************************
 * Initializes the list of transactions
 * @param pList Pointer to the list of transactions to be initialized
 **************************************************************************************************/
void TRANS_CreateList( TransList* pList )
{
    pList->pHead      = NULL;
    pList->pTail      = NULL;
    pList->entryCount = 0;
}

/**************************************************************************************************
 * Returns true if the list of transactions is empty and flase if not
 * @param pList Pointer to the list of transactions
 **************************************************************************************************/
static bool TRANS_ListIsEmpty( TransList* pList )
{
    return ( pList -> entryCount == 0 );
}


/**************************************************************************************************
 * Appends a transaction to the list of transactions
 * @param pList Pointer to the list of transactions
 * @param newData The new transaction to be added to the list
 **************************************************************************************************/
void TRANS_Append( TransList* pList, Transact newData )
{

    TransNode *newNode = (TransNode*)malloc( sizeof(TransNode) );

    newNode->data  = newData;
    newNode->pNext = NULL;
    newNode->pPrev = pList -> pTail;

    if ( newNode == NULL )
    {
        printf("Memory is full!!!\n");
    }
    else if ( TRANS_ListIsEmpty(pList) )
    {
        pList->pHead = newNode;
        pList->pTail = newNode;
    }
    else
    {
        pList->pTail->pNext = newNode;
        pList->pTail        = newNode;
    }
    
    pList->entryCount++;

}

/**************************************************************************************************
 * Prints all the elements in the list of transactions and specifying the type of each transaction
 * (either Deposit or Withdraw)
 * @param pList Pointer to the list of transactions
 **************************************************************************************************/
void TRANS_DisplayList( TransList* pList )
{
    TransNode * pTmpNode;                           /* A temp node to loop through the list                                         */
    u32         index;                              /* The current index of the tmp node to display the order of the transactions   */

    index = 1;

    if ( TRANS_ListIsEmpty(pList) )
    {
        printf("\n-------------------\n");
        printf("No transaction history!\n");
        return;
    }
   
    pTmpNode = pList->pHead;

    printf("\n---------------------- TRANSACTION HISTORY ---------------------------\n");
    while ( pTmpNode != NULL )
   {
        printf("%d-  %d   (%s) \n", index++, pTmpNode -> data.amount, pTmpNode->data.type );
        pTmpNode = pTmpNode->pNext;
   }
    printf("\n---------------------- END OF TRANSACTION HISTORY ----------------------\n");
}


/**************************************************************************************************
 * Clears the list of transactions
 *@param pList Pointer to the list of transactions
***************************************************************************************************/
void TRANS_ClearList( TransList* pList )
{
    TransNode *tmpNode = NULL;

    if ( TRANS_ListIsEmpty(pList) )
    {
        printf("Transaction List is already empty!\n");
    }
    else
    {
        while ( pList->pHead != NULL )
        {
            tmpNode = pList->pHead;
            pList->pHead = pList->pHead->pNext;
            free( tmpNode );
        }
        pList->pTail = NULL;
        pList->entryCount = 0;
    }
}

