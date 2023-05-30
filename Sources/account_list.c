/*H**************************************************************************************************************
 * FILENAME :       account_list.c

 * DESCRIPTION :    
 *              Implementaion of list of accounts using doubly linked list
 * 
 * AUTHOR :     Ahmed Osman                 START DATE :    18 May 2023
 * 
 * CHANGES : 
 * 
 *  VERSION       DATE              WHO             DETAIL
 *  1.0.0         18 May 2023       A.O             Made the file and started implementing as a generic doubly linked ist
 *  1.0.0         22 May 2023       A.O             Implemented account DS and project as a whole specific functions
 **************************************************************************************************************H*/

#include "../Headers/account_list.h"

extern u32      g_currID;

/**************************************************************************************************
 * Initializes the account list
 * @param pList Pointer to the list of accounts
 **************************************************************************************************/
void LIST_CreateList( AccList* pList )
{
    pList->pHead      = NULL;
    pList->pTail      = NULL;
    pList->entryCount = 0;
}

/**************************************************************************************************
 * Creates a new account and asks the user to enter the data for this account then insert this 
 * account into the list of accounts
 * @param pList Pointer to the list of accounts
 **************************************************************************************************/
void LIST_NewAccount( AccList* pList )
{
    Account     newAcc;
    TransList * newTransList = NULL;                                   /* The transaction list (history) for this new account              */

    ACC_ScanName(&newAcc);
    ACC_ScanPhNum(&newAcc);
    ACC_ScanDate(&newAcc);
    ACC_ScanAddress(&newAcc);
    ACC_ScanBalance(&newAcc);
    

    newTransList = (TransList*)malloc( sizeof(TransList) );   

    if ( newTransList == NULL )
    {
        printf("Memory is full!!!\n");
        return;
    }

    newAcc.transHistory = newTransList;                         /* Adds and initializes the transaction history to the new account  */
    TRANS_CreateList(newAcc.transHistory);

    
    newAcc.ID = g_currID++;                                     /* Use the global ID to assign an ID for the new account            */

    LIST_Insert( pList, &newAcc );
}


/**************************************************************************************************
 * Returns true if the account list is empty
 * @param pList Pointer to the accounts list
 **************************************************************************************************/
static bool LIST_ListIsEmpty( AccList* pList )
{
    return ( pList -> entryCount == 0 );
}


/**************************************************************************************************
 * Appends new account to the given accounts list
 * @param pList Pointer to the list of accounts
 * @param newData Pointer to the new account to be added
 **************************************************************************************************/
void LIST_Append(AccList* pList, ListEntry *newData)
{
    ListNode    * newNode = NULL;

    newNode = (ListNode*)malloc( sizeof(ListNode) );

    if (newNode == NULL )
    {
        printf("Memory is full!!!\n");
        return;
    }

    newNode->data  = *newData;
    newNode->pNext = NULL;
    newNode->pPrev = pList->pTail;

    if ( LIST_ListIsEmpty(pList) )
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
 * Prints all the data of accounts in the accounts list
 * @param pList Pointer to the accounts list
 **************************************************************************************************/
void LIST_DisplayList( AccList* pList )
{
    ListNode    * pTmpNode;                                         /* Node to move through the list                */

    if ( LIST_ListIsEmpty(pList) )
    {
        printf("\n-----------------\n\n");
        printf("List is empty!\n");
        return;
    }
   
    // LIST_SortList( pList );                                       /* Uncomment if using append instead of insert */

    pTmpNode = pList->pHead;                                         /* Start from the head (the beginnig of the list) */

    /* While end of the list is not reached */
    while(pTmpNode != NULL)                                      
    {
        printf("--------------------------\n"                     );
        printf("Name:          %s\n", pTmpNode->data.name         );
        printf("ID:            %d\n", pTmpNode->data.ID           );
        printf("Balance:       %d\n", pTmpNode->data.balance      );
        printf("Phone Number:  %s\n", pTmpNode->data.phoneNum     );
        printf("Date of birth: %d/%d/%d\n",
                pTmpNode->data.DOB.day,     pTmpNode->data.DOB.month,       pTmpNode->data.DOB.year  );
        printf("Address:\n        GOV: %s   City: %s   Street:   %s\n", 
                pTmpNode->data.address.gov, pTmpNode->data.address.city, pTmpNode->data.address.street);
        pTmpNode = pTmpNode->pNext;
        printf("--------------------------\n");
    }
}


/**************************************************************************************************
 * Searches for an account using its name and returns the node containing that account if found
 * @param pList Pointer to the list of accounts
 * @param name The name of the account to search for
 **************************************************************************************************/
ListNode* LIST_SearchList(AccList* pList, char* name)
{
    ListNode        * pTmpNode;

    if ( LIST_ListIsEmpty(pList) )
    {
        printf("List is empty!\n");
        return NULL;
    }

    pTmpNode = pList -> pHead;

    while(pTmpNode != NULL)
    {
        if ( (strcmp(pTmpNode->data.name, name)) == 0 )                     /* If the current account name equals the name searching for */
        {
            return pTmpNode;
        }
        pTmpNode = pTmpNode->pNext;
    }

    return pTmpNode;                                                       /* Returns NULL if name is not found                            */
}


/**************************************************************************************************
 * Inserts the account in the list in its correct alphabetic order accodring to the name
 * @param pList Pointer to accounts list
 * @param newData Pointer to account to add in accounts list
 **************************************************************************************************/
void LIST_Insert( AccList* pList, ListEntry *newData )
{
    ListNode    * newNode = NULL;
    ListNode    * tmpNode = NULL;                          /* the posision where to insert the new node to be sorted */

    newNode = (ListNode*)malloc( sizeof(ListNode) );

    if ( newNode == NULL )
    {
        printf("Memory is full!!!\n");
        return;
    }

    newNode -> data = *newData;

    if ( LIST_ListIsEmpty(pList) )
    {
        pList->pHead   = newNode;
        pList->pTail   = newNode;
        newNode->pNext = NULL;
        newNode->pPrev = NULL;
        pList->entryCount++;
        return;
    }

    tmpNode = pList -> pHead;

    /* Keep going though list untill reach node with a name alphanumerically larger than new data name or untill end of list */
    while ( (tmpNode != NULL) && (strcmp(tmpNode->data.name, newData->name) < 0) )
    {
        tmpNode = tmpNode -> pNext;
    }

    if ( tmpNode == pList->pHead )        /* Insert it at the start of the list */
    {
        newNode->pPrev      = NULL;
        newNode->pNext      = pList->pHead;
        pList->pHead->pPrev = newNode;
        pList->pHead        = newNode;
    }
    else if ( tmpNode == NULL )            /* Insert at end of the Acclist*/
    {
        newNode->pNext      = NULL;
        newNode->pPrev      = pList->pTail;
        pList->pTail->pNext = newNode;
        pList->pTail        = newNode;
    }
    else                                /* Insert in the middle of the list */
    {
        newNode->pNext        = tmpNode;
        newNode->pPrev        = tmpNode->pPrev;
        tmpNode->pPrev->pNext = newNode;
        tmpNode->pPrev        = newNode;
    }

    pList->entryCount++;

}


/**************************************************************************************************
 * Searches for an account using its name then deletes this account fromt the list of accounts
 * @param pList Pointer to the list of account
 **************************************************************************************************/
void LIST_Delete( AccList* pList )
{
    ListNode    * accNode;                                  /* The node containing the account to delete                                */
    char          name[MAX_NAME_LENGTH * 3];                /* The name to search for                                                   */

    Scan_Name(name);                                        /* Ask the user to input the account name and save it in the name variable  */

    if ( LIST_ListIsEmpty(pList) )
    {
        printf("List is empty, no items to delete!\n");
        return;
    }

    accNode = LIST_SearchList(pList, name);

    if ( accNode == NULL )
    {
        printf("Name not found!\n");
        return;
    }
    else if ( pList->pHead == pList->pTail )            /* if only one element in the list */
    {
        pList->pHead          = NULL;
        pList->pTail          = NULL;
    }
    else if ( accNode == pList->pHead )                 /* Delete the first element */
    {
        accNode->pNext->pPrev = NULL;
        pList->pHead          = accNode->pNext;
    }
    else if( accNode == pList->pTail )                  /* Delete the last element */
    {
        accNode->pPrev->pNext = NULL;
        pList->pTail          = accNode->pPrev;
    }
    else                                                /* Delete element from the middle */
    {
        accNode->pPrev->pNext = accNode->pNext;
        accNode->pNext->pPrev = accNode->pPrev;
    }

    TRANS_ClearList( accNode->data.transHistory );      /* Clear the history to free all transaction nodes from heap             */
    free( accNode->data.transHistory);                  /* Free the place containing the transaction list (head, tail) from heap */
    free( accNode );                                    /* Free account node itself from heap                                    */
    pList->entryCount--;
}

/**************************************************************************************************
 * Clears the list of accounts
 * @param pList Pointer to the list of accounts
 **************************************************************************************************/
void LIST_ClearList( AccList* pList )
{
    ListNode *tmpNode;

    if ( LIST_ListIsEmpty(pList) )
    {
        printf("List is already empty!\n");
    }
    else
    {
        while ( pList->pHead != NULL )
        {
            tmpNode      = pList->pHead;
            pList->pHead = pList->pHead->pNext;
            free( tmpNode );
        }
        pList->pTail      = NULL;
        pList->entryCount = 0;
    }
}

/**************************************************************************************************
 * Sorts the accounts list alphanumerically according to the accounts names using bubble sort
 * @param pList Pointer to the accounts list
 **************************************************************************************************/
void LIST_SortList( AccList* pList )
{
    u32           i;
    u32           j;

    ListNode    * tmpNode;

    if ( LIST_ListIsEmpty(pList) )
    {
        printf("List is empty! nothing to sort\n");
    }
    else if ( pList->pHead == pList->pTail )
    {
        printf("Only one element in the list, nothing to be sorted\n");
    }
    else
    {
        tmpNode = pList->pHead;

        for(i = 0; i < pList->entryCount - 1; i++)
        {
            for(j = 0; j < pList->entryCount - 1 - i; j++)
            {
                if( (strcmp( tmpNode->data.name, tmpNode->pNext->data.name )) > 0 )   /* If current accounts name is bigger than next accounts name */
                {
                    LIST_SwapNodes( tmpNode, tmpNode->pNext );
                }
                tmpNode = tmpNode->pNext;
            }
            tmpNode = pList->pHead;                                                 /* Reset the tmp node back to the beginning of the list */
        }
    }
}

/**************************************************************************************************
 * Swaps the two given nodes data
 * @param node1 Pointer to the first node
 * @param node2 Pointer to the next node
 **************************************************************************************************/
static void LIST_SwapNodes(ListNode *node1, ListNode *node2)
{
    ListEntry tmp = node1->data;
    node1->data = node2->data;
    node2->data = tmp;
}



/**************************************************************************************************
 * The main function of the program. Creates a new accounts list and Displays list of options
 *  for the user to choose from
 **************************************************************************************************/
void LIST_MainMenu()
{
    AccList     accList;                    /* Make a new accounts list                                  */
    u32          option;

    /* Array of functions to choose from */     
    void (*arrFuncs[])(AccList*) = {LIST_NewAccount, LIST_Delete, LIST_DisplayList, LIST_ChooseAccMenu};

    LIST_CreateList(&accList);               /* Initialize the accounts list                              */

    printf("\n*********************************************************************\n");
    printf("                Welcome to the NTI Bank management system =)\n");
    printf("                   This is the List implementation  \n ");
    printf("*********************************************************************\n\n");
    
    do
    {
        printf("====================================================================\n");
        printf("====================================================================\n");
        printf("Choose one of the following options:\n");
        printf("1- Add a new account.\n");
        printf("2- Delete an account.\n");
        printf("3- Display all accounts in alphabetical order.\n");
        printf("4- Choose an account.\n");
        printf("0- Exit.\n");

        scanf( "%d", &option );
        while ( (getchar()) != '\n' );

        if ( (option >= 1) && (option <= 4))
        {
            arrFuncs[option-1]( &accList );
        }
        else if ( option == 0 )
        {
            printf("Thankyou for using our system =)\n");
            return;
        }
        else
        {
            printf("Invalid option!\n");
        }

        printf("====================================================================\n");
        printf("====================================================================\n\n");

    } while (1);
    
}


/**************************************************************************************************
 * Lets the user to choose a certain account using the name from the accounts list
 * and control this account by choosing one of the options from the menu
 * @param pList Pointer to the list of accounts
 **************************************************************************************************/
void LIST_ChooseAccMenu( AccList* pList )
{
    u32          option;
    char        name[MAX_NAME_LENGTH * 3];                      /* Name of the account to search for and control          */

    ListNode  * accNode = NULL;                                 /* Node containing the account we want to control         */

    void(*arrFuncs[])(Account*) = {ACC_EditAccount, ACC_Transact, ACC_DisplayHistory}; 

    printf("Please enter the name of the account owner:\n");
    Scan_Name(name);

    accNode = LIST_SearchList(pList, name);                      /* Search for the account in the list                       */

    if ( accNode == NULL )
    {
        printf("\n");
        printf("Account doesn't exist or name typed incorrectly.\n");
    }
    else
    {
        
        do
        {
            printf("\n                    You can now control (%s) account.\n", name);
            printf("====================================================================\n");
            printf("====================================================================\n");
            printf("Choose one of the following options:\n");
            printf("1- Edit account.\n");
            printf("2- Make a transaction.\n");
            printf("3- Display transactions history.\n");
            printf("0- Exit.\n");

            scanf(" %d", &option );
            while ( (getchar()) != '\n' );                          /* Clear input buffer                                   */

            if ( (option >= 1) && (option <= 3) )
            {
                arrFuncs[option-1]( &(accNode->data) );             /* Send pointer to the account we are controlling       */
            }
            else if ( option == 0 )
            {
                return;
            }
            else
            {
                printf("Invalid option!\n");
            }
            

            printf("====================================================================\n");
            printf("====================================================================\n");

        } while (1);
        
    }

}