/*H**************************************************************************************************************
 * FILENAME :       account_bst.c

 * DESCRIPTION :    
 *              Implementaion of Tree of accounts using Binary Search Tree
 * 
 * AUTHOR :     Ahmed Osman                 START DATE :    24 May 2023
 * 
 * CHANGES : 
 * 
 *  VERSION       DATE              WHO             DETAIL
 *  1.0.0         24 May 2023       A.O             Made the file
 **************************************************************************************************************H*/


#include "../Headers/account_bst.h"

extern u32      g_currID;

/**************************************************************************************************
 * Initializes the given BST
 * @param accTree Pointer to the BST that will be initialized
 **************************************************************************************************/
void BST_CreateTree( AccTree * accTree )
{
    accTree->root = NULL;
    accTree->nodeCount = 0;
}


/**************************************************************************************************
 * Utility function to create a new node for a BST
 * @param data The account that will be stored inside this new node
 **************************************************************************************************/
static TreeNode * NewTreeNode( Account data )
{
    TreeNode * newNode = (TreeNode *)malloc( sizeof(TreeNode) );
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


/**************************************************************************************************
 * Creates a new account and asks the user to input the data for this account
 * then inserts this account into the given BST
 * @param Pointer to the BST that the new account will be inserted into
 *************************************************************************************************/
void BST_NewAccount( AccTree * accTree )
{
    Account     newAcc;
    TransList * newTransList = NULL;                               /* The transaction list (history) for this new account        */

    ACC_ScanName (&newAcc);
    ACC_ScanPhNum(&newAcc);
    ACC_ScanDate (&newAcc);
    ACC_ScanAddress(&newAcc);
    ACC_ScanBalance(&newAcc);
    

    newTransList = (TransList*)malloc( sizeof(TransList) );      /* Allocates memory for a transaction list for the new account   */

    if ( newTransList == NULL )
    {
        printf("Memory is full!!!\n");
        return;
    }

    newAcc.transHistory = newTransList;                         /* Adds and initializes the transaction history to the new account  */
    TRANS_CreateList(newAcc.transHistory);

    
    newAcc.ID = g_currID++;                                     /* Use the global ID to assign an ID for the new account            */

    accTree->root = BST_InsertAcc( accTree->root, newAcc );              /* Insert the account into the BST                                  */
}


/**************************************************************************************************
 * Inserts account into its correct position in the BST
 * @param root The root node of the BST
 * @param data The account to be inserted
 **************************************************************************************************/
TreeNode * BST_InsertAcc(TreeNode * root, Account data)
{
    if ( root == NULL )
    {
        return ( NewTreeNode( data ) );                     /* When leaf node is reached create a new node to be assigned to the left or 
                                                                right of that node depending on if smaller or bigger than this node */
    }

    if ( strcmp( data.name, root->data.name ) <= 0 )        /* If the given account node is smaller than or equal the root node */
    {
        root->left = BST_InsertAcc( root->left, data );            /* New tree is tree with root is left side of the current root      */
    }
    else
    {
        root->right = BST_InsertAcc( root->right, data );
    }

    return root;
}

/**************************************************************************************************
 * Displays the accounts in the tree in accending order according to names
 * @param root Pointer to the root node for the BST to be displayed
 **************************************************************************************************/
void BST_Display( TreeNode * root )
{
    if ( root == NULL )
    {
        return;
    }

    BST_Display( root->left );                              /* Go to the most left element and print it then when reach null */                                                
    PrintNodeData( root );                                      /* rewind and print this node then go to the right of this node */
    BST_Display( root->right );                             /* and repeat the processs                                      */
}


/**************************************************************************************************
 * Wraper function for display to make it recieve a pointer to the account tree itself
 * @param root Pointer to the root node for the BST to be displayed
 **************************************************************************************************/
void BST_DisplayTree( AccTree * accTree)
{
    if ( accTree->root == NULL )
    {
        printf("\nNo accounts!!\n");
    }
    else
    {
        BST_Display( accTree->root );
    }
}


/**************************************************************************************************
 * A utility function to print the account data of the given node
 * @param node Pointer to the node to print the data of
 **************************************************************************************************/
static void PrintNodeData( TreeNode * node )
{

    printf("--------------------------\n"                 );
    printf("Name:          %s\n", node->data.name         );
    printf("ID:            %d\n", node->data.ID           );
    printf("Balance:       %d\n", node->data.balance      );
    printf("Phone Number:  %s\n", node->data.phoneNum     );
    printf("Date of birth: %d/%d/%d\n",
            node->data.DOB.day,     node->data.DOB.month,       node->data.DOB.year  );
    printf("Address:\n        GOV: %s   City: %s   Street:   %s\n", 
            node->data.address.gov, node->data.address.city, node->data.address.street);
    printf("--------------------------\n"                 );
}


/**************************************************************************************************
 * Searches for a particular account using the accounts name and return the node holding the
 * account if found and NULL if not found
 * @param root Pointer to the root node of the BST
 * @param key The name of the account to search for in the BST
 **************************************************************************************************/
TreeNode * BST_SearchTree( TreeNode * root, char * key )
{
    /* Base case, if the account is found will return pointer to the node holding the element
                    and if not found will return NULL                                       */
    if ( ( root == NULL ) || ( strcmp( root->data.name, key ) == 0 ) )
    {
        return root;
    }

    if ( strcmp( key, root->data.name ) <= 0 )
    {
        BST_SearchTree( root->left, key );                      /* Search in the left side of the current tree */
    }
    else
    {
        BST_SearchTree( root->right, key );                     /* Search in the right side of the current tree */
    }
}


/**************************************************************************************************
 * Searches for an account using its name and deletes this account if found
 * @param root Pointer to the root node of the BST
 * @param key The name of the account to delete
 **************************************************************************************************/
TreeNode * BST_Delete(TreeNode * root, char * key )
{
    /* Base case, will rewind all the delete functions wihtout 
    deleting any account if the bottom of the tree is reached
    without finding the account                                      */
    if ( root == NULL )
    {
        return root;        
    }

    /* Keep going through the tree untill the node to be deleted is found */
    if ( strcmp( key, root->data.name ) < 0 )                       
    {
        root->left = BST_Delete( root->left, key );                     
    }
    else if( strcmp( key, root->data.name ) > 0 )
    {
        root->right = BST_Delete( root->right, key );
    }
    else
    {   /* If the account is found                                      */

        /* If the node has only one child node or no child nodes 
        create a temp node to hold the chlild node of the current node
        then return this temp node so the child node of the current node
        will be assigned to the parent node of the current node       */
        if ( root->left == NULL )
        {
            
            TreeNode * tmpNode = root->right;                           
            free( root );
            return tmpNode;
        }
        else if( root->right == NULL )
        {
            TreeNode * tmpNode = root->left;
            free(root);
            return tmpNode;
        }
        else /* If the account to be deleted has two child nodes                        */
        {       
            /* Find the inorder successor of  that account node                         */
            TreeNode * tmpNode = MinTreeVal( root->right );

            /* Replace the data of the account with the data of its inorder successor   */
            root->data = tmpNode->data;

            /* Delete the indorder successor node                                       */
            root->right = BST_Delete( root->right, tmpNode->data.name );
        }
    }

    /* Every step has left =  or right =    , this is where this left or right is assigned
    aka this keeps the root node connected with its left or right node after doing recursion */
    return root;
}



/**************************************************************************************************
 * Wraper function for the delete function to be able to use it in the main menu as the return
 * type should be void inorder to use it in the array of pointer to functions in the main menu
 * and also to make it recive the Account tree itself as an argument
 * @param root Pointer to the root node of the BST
 * @param key The name of the account to delete
 **************************************************************************************************/
void BST_DeleteAcc( AccTree * accTree )
{
    char    name[MAX_NAME_LENGTH * 3];

    printf("Please enter the name of the account to be deleted:\n");
    Scan_Name(name);
    accTree->root = BST_Delete( accTree->root, name);
}


/**************************************************************************************************
 * Returns the smallest node of the given tree.
 * Used to find the inorder successor of a certain node in the tree
 * @param root The root of the given tree
 **************************************************************************************************/
static TreeNode * MinTreeVal( TreeNode * root )
{
    TreeNode * tmpNode = root;

    /* Keep going to left until reach the most left node in the tree.
    The most left node will be the smallest node in the tree        */
    while ( tmpNode->left != NULL )
    {
        tmpNode = tmpNode->left;
    }

    return tmpNode;
}


/**************************************************************************************************
 * The main function of the program. Creates a new accounts list and Displays list of options
 *  for the user to choose from
 **************************************************************************************************/
void BST_MainMenu()
{
    AccTree     accTree;                    /* Make a new accounts tree                                  */
    u32          option;

    /* Array of functions to choose from */     
    void (*arrFuncs[])(AccTree *) = {BST_NewAccount, BST_DeleteAcc, BST_DisplayTree, BST_ChooseAccMenu};

    BST_CreateTree(&accTree);               /* Initialize the accounts list                              */

    printf("\n*********************************************************************\n");
    printf("            Welcome to the NTI Bank management system =)\n");
    printf("                This is the Tree implementation           \n");
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
            arrFuncs[option-1]( &accTree );
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
void BST_ChooseAccMenu( AccTree * accTree )
{
    u32          option;
    char        name[MAX_NAME_LENGTH * 3];                      /* Name of the account to search for and control          */

    TreeNode  * accNode = NULL;                                 /* Node containing the account we want to control         */

    void(*arrFuncs[])(Account*) = {ACC_EditAccount, ACC_Transact, ACC_DisplayHistory}; 

    printf("Please enter the name of the account owner:\n");
    Scan_Name( name );

    accNode = BST_SearchTree( accTree->root, name );                      /* Search for the account in the list                       */

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
            

            // printf("====================================================================\n");
            // printf("====================================================================\n");

        } while (1);
        
    }

}