/*H**************************************************************************************************************
 * FILENAME :       account.h

 * DESCRIPTION :    
 *              Header file for the account itself
 * 
 * AUTHOR :     Ahmed Osman                 START DATE :    18 May 2023
 * 
 * CHANGES : 
 * 
 *  VERSION       DATE              WHO             DETAIL
 *  1.0.0         18 May 2023       A.O             Made the file and added just the data types
 *  1.0.0         21 May 2023       A.O             Added functions
 **************************************************************************************************************H*/


#ifndef ACCOUNT_H
#define ACCOUNT_H


#include "common.h"
#include "trans_list.h"

#define MAX_NAME_LENGTH     20
#define MIN_NAME_LENGTH     3


extern u32      g_currID;                  /* ID for the last account created, each time account is created ID is increamented by 1 */

typedef struct Date
{
    u8          day;
    u8          month;
    u16         year;

}Date;

typedef struct Address
{
    char        gov[20];               /* cairo, alex...etc        */
    char        city[20];          
    char        street[20];

}Address;


typedef struct Account
{
    char        name[MAX_NAME_LENGTH * 3];
    Address     address;
    u32         ID;
    s32         balance;
    Date        DOB;                   /* Date of birth            */
    char        phoneNum[20];          /* 11 nums for Egypt + NULL */
    TransList * transHistory;

}Account;


void        Scan_Name( char* );
void        ACC_ScanName( Account * );
static bool ACC_NameIsValid( char * );
void        ACC_ScanPhNum( Account * );
static bool ACC_PhNumIsValid( char * );
void        ACC_ScanDate( Account * );
void        ACC_ScanBalance( Account * );
void        ACC_ScanAddress( Account * );
void        ACC_EditAccount(Account * );
void        ACC_Transact( Account * );
void        ACC_Deposit( Account * );
void        ACC_Withdraw( Account * );
void        ACC_DisplayHistory(Account * );


#endif