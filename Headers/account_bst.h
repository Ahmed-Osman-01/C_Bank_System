/*H**************************************************************************************************************
 * FILENAME :       account_bst.h

 * DESCRIPTION :    
 *              Header file for Binary Search Tree implementation as accounts Data Structure
 * 
 * AUTHOR :     Ahmed Osman                 START DATE :    24 May 2023
 * 
 * CHANGES : 
 * 
 *  VERSION       DATE              WHO             DETAIL
 *  1.0.0         24 May 2023       A.O             Made the file
 **************************************************************************************************************H*/

#ifndef ACCOUNT_BST_H
#define ACCOUNT_BST_H


#include "account.h"

typedef struct TreeNode
{
    Account           data;
    struct TreeNode * left;
    struct TreeNode * right;

}TreeNode;

typedef struct AccTree
{
    TreeNode * root;
    u32        nodeCount;

}AccTree;


void              BST_CreateTree( AccTree * );
void              BST_NewAccount( AccTree * );
static bool       BST_IsEmpty( TreeNode * );
static TreeNode * NewTreeNode(Account );
TreeNode *        BST_InsertAcc( TreeNode * , Account);
void              BST_Display( TreeNode * );
void              BST_DisplayTree( AccTree *);
static void       PrintNodeData( TreeNode * );
TreeNode *        BST_SearchTree( TreeNode * , char * );
TreeNode *        BST_Delete( TreeNode *, char *);
void              BST_DeleteAcc( AccTree *);
static TreeNode * MinTreeVal( TreeNode *);
void              BST_MainMenu();
void              BST_ChooseAccMenu( AccTree * );

#endif