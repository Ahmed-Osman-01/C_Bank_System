/*H**************************************************************************************************************
 * FILENAME :       account.c

 * DESCRIPTION :    
 *              Contains data and functions related to the account itself
 * 
 * AUTHOR :     Ahmed Osman                 START DATE :    21 May 2023
 * 
 * CHANGES : 
 * 
 *  VERSION       DATE              WHO             DETAIL
 *  1.0.0         21 May 2023       A.O             Made the file and started implementing the functions
 **************************************************************************************************************H*/

#include "../Headers/account.h"
#include "../Headers/account_list.h"

u32     g_currID = 1231;                            /* ID given to all accounts, each new has previous ID + 1 */

/***********************************************************************************
 * A utility function to scan name from the user while validating this name.
 * It handles the format of the name. All names will be saved with Capital first
 * letter and other letters small not matter how the input looked like
 * @param name Pointer to char where the scanned name will be copied into
 ***********************************************************************************/
void Scan_Name(char* name)
{
    char    fullName[MAX_NAME_LENGTH * 3];
    char    first   [MAX_NAME_LENGTH];          
    char    second  [MAX_NAME_LENGTH];          
    char    third   [MAX_NAME_LENGTH];          
                    
    printf( "Enter the first name: \n" );
    fgets( first, MAX_NAME_LENGTH, stdin );
    first[ strcspn(first, "\n") ] = 0;              /* using fgets is safer than scnaf but we have to remove the new line at the end  */

    while ( !(ACC_NameIsValid(first)) )
    {
        printf("Invalid name, enter the name again:\n");
        fgets( first, MAX_NAME_LENGTH, stdin );
        first[ strcspn(first, "\n") ] = 0;
    }

    strlwr( first );
    first[0] = toupper( first[0] );                 /* These two lines is to make sure all names are stored in the correct format 
                                                    (capital first letter only and otherletters are small)                              */
    strcat( first, " " );                           /* Add space between names                                                          */


    printf("Enter the second name: \n");
    fgets(second, MAX_NAME_LENGTH, stdin);
    second[ strcspn(second, "\n") ] = 0;

    while ( !(ACC_NameIsValid(second)) )
    {
        printf( "Invalid name, enter the name again:\n" );
        fgets( second, MAX_NAME_LENGTH, stdin );
        second[ strcspn(second, "\n") ] = 0;
    }

    strlwr( second );
    second[0] = toupper( second[0] );
    strcat( second, " " );


    printf("Enter the third name: \n");
    fgets( third, MAX_NAME_LENGTH, stdin );
    third[ strcspn(third, "\n") ] = 0;

    while ( !(ACC_NameIsValid(third)) )
    {
        printf("Invalid name, enter the name again:\n");
        fgets( third, MAX_NAME_LENGTH, stdin );
        third[ strcspn(third, "\n") ] = 0;
    }

    strlwr( third );
    third[0] = toupper( third[0] );


    memcpy( fullName, first, sizeof(first) );          /* Using cpy instead of cat here because full name has not been initialized so there are garbage data
                                                        which will be included at the beginning when using cat */
    strcat( fullName, second );
    strcat( fullName, third );

    memcpy( name, fullName, sizeof(fullName) );
    
}

/**************************************************************************************************
 * Recieves an account and scans new name from the user to this account
 * we make this function just for the naming convention because the other scan is used in many
 * places in the program so not to get confues when we need to scan a new name for the user or just
 * input a name to use it for example to search for an account using this name
 * @param acc The account to where the new name is scanned
 **************************************************************************************************/
void ACC_ScanName( Account* acc )
{ 
   Scan_Name( acc->name );
}


/**************************************************************************************************
 * Recieves a name and returns true if this name is valid and false otherwise
 * @param name Pointer to the name to check for
 **************************************************************************************************/
static bool ACC_NameIsValid( char* name )
{
    u32     i;
    i = 0;

    while ( name[i] != '\0' )
    {
        /* If current letter doesn't belong to alphabetic letters return false*/
        if ( !(((name[i] >= 'a') && (name[i] <= 'z'))        
                ||
             ((name[i] >= 'A') && (name[i] <= 'Z'))))
        {
            return false;   
        }
        i++;
    }

    // /* If the name is too short or too long return false */
    // if ( (i >= MAX_NAME_LENGTH) || (i < MIN_NAME_LENGTH) )
    // {
    //     printf("Name length is wrong!\n");
    //     return false;
    // }

    return true;
}


/**************************************************************************************************
 * Scans phone number from user then copies this phone number into the account if it is valid
 * @param acc The account where the phone number will be copied
 **************************************************************************************************/
void ACC_ScanPhNum( Account* acc )
{
    char    num[15];                                    /* make a new variable to hold the number with slightly larger space in case
                                                        the user inputs a number with length bigger than 11 so it doesn't mess with the
                                                        memory */

    printf("Enter the phone number:  \n");
    fgets( num, sizeof(num), stdin );
    num[ strcspn(num, "\n") ] = 0;

    while ( !(ACC_PhNumIsValid(num)) )
    {
        printf("Invalid number, please enter the number again:  \n");
        fgets( num, sizeof(num), stdin );
        num[ strcspn(num, "\n") ] = 0;
    }

    memcpy( acc->phoneNum, num, sizeof(num) );
}


/**************************************************************************************************
 * Returns ture if the phone number is valid and false if not
 * @param phoneNum The phone number to check if valid
 **************************************************************************************************/
static bool ACC_PhNumIsValid( char* phoneNum )
{
    u32     i;
    i = 0;

    /* If the number doesn't start with 01... */
    if ( (phoneNum[0] != '0') || (phoneNum[1] != '1') )
    {
        return false;
    }

    /* If the number contains anything else but numbers */
    while ( phoneNum[i] != '\0' )
    {
        if( (phoneNum[i] < 48) || (phoneNum[i] > 57) )
        {
            return false;
        }
        i++;
    }

    /* If the length of the number isn't 11 numbers */
    if( i != 11 )
    {
        return false;
    }

    return true;
}

/**************************************************************************************************
 * Scans the birth date from the user and adds it to the given account if it's valid
 * @param acc The account where the date will be added
 **************************************************************************************************/
 void ACC_ScanDate(Account* acc)
{
    s32     day;                 // ---->>>> ???? something wrong happens when the data size is not int
    s32     month;              
    s32     year;                                           /* intentionally made them signed instead of unsigned to be able to check
                                                      if the user inputs a negative number */


    printf("Enter the day of birth: ");
    scanf( "%d", &day );
    while ( (getchar()) != '\n' );                  /* Clear the buffer to solve problem incasae the user enters a num + char ( ex: 12p) */

    while ( (day < 1) || (day > 31) )
    {
        printf("Invalid day, Please enter the day again: ");
        scanf("%d", &day);
        while ( (getchar()) != '\n' );             /* Must clear the buffer here becuse the program goes crazy if user inputs a char or string */
    }
    
    printf("Enter the month of birth: ");
    scanf( "%d", &month );
    while ( (getchar()) != '\n' );                  /* Clear the buffer to solve problem incasae the user enters a num + char ( ex: 12p) */

    while ( (month < 1) || (month > 12) )
    {
        printf("Invalid month, Please enter the month again: ");
        scanf("%d", &month);
        while ( (getchar()) != '\n' );             /* Must clear the buffer here becuse the program goes crazy if user inputs a char or string */
    }

    printf("Enter the year of birth: ");
    scanf( "%d", &year );
    while ( (getchar()) != '\n' );                  /* Clear the buffer to solve problem incasae the user enters a num + char ( ex: 12p) */

    while ( (year < 1900) || (year > 2005) )
    {
        printf("Invalid year, Please enter the year again: ");
        scanf( "%d", &year );
        while ( (getchar()) != '\n' );             /* Must clear the buffer here becuse the program goes crazy if user inputs a char or string */
    }
    

    acc->DOB.day   = day;
    acc->DOB.month = month;
    acc->DOB.year  = year;

}

/**************************************************************************************************
 * Initial balance in the account. This can't be less then 5000 EGP
 * @param acc The account to put this balance in
 **************************************************************************************************/
 void ACC_ScanBalance( Account* acc )
 {
    u32     balance;


    printf("Enter the initial balance of the account: ");
    scanf( "%d", &balance );
    while ( (getchar()) != '\n' );

    while ( balance < 5000 )
    {
        printf("Initial balance can't be less than 5000 EGP, Enter a valid initial balance: ");
        scanf( "%d", &balance );
        while ( (getchar()) != '\n' );
    }

    acc->balance = balance;
 }


/**************************************************************************************************
 * Scans address from the user then put this address in the given account
 * @param acc The account to put the address in
 **************************************************************************************************/
void ACC_ScanAddress( Account* acc )
 {
    char    gov[20];
    char    city[20];
    char    street[20];

    printf("Enter the Governrate : ");
    fgets( gov, sizeof(gov), stdin );
    gov[ strcspn(gov, "\n") ] = 0;

    printf("Enter the City: ");
    fgets( city, 20, stdin) ;                                                                                    
    city[ strcspn(city, "\n") ] = 0;                      
                                                            
    printf("Enter the street: ");
    fgets( street, 20, stdin );
    street[ strcspn(street, "\n") ] = 0;

    memcpy( acc->address.gov, gov, sizeof(gov) );
    memcpy( acc->address.city, city, sizeof(city) );
    memcpy( acc->address.street, street, sizeof(street) );

 }


/**************************************************************************************************
 * Lets the user edit (Name, Phone number, Date of birth, Address) of the given account
 * @param acc Pointer to the account to edit
 **************************************************************************************************/
void ACC_EditAccount(Account* acc)
{
    u32     option;   
                                  
    /* array of pointer to the functions to let user choose from */
    void (*accFuncs[])(Account*) = { ACC_ScanName, ACC_ScanPhNum, ACC_ScanDate, ACC_ScanAddress };  


    do
    {
        printf("====================================================================\n");
        printf("====================================================================\n\n");
        printf("Choose which field to edit:\n");
        printf("1- Edit name.\n");
        printf("2- Edit Phone number.\n");
        printf("3- Edit Date of Birth.\n");
        printf("4- Edit Address.\n");
        printf("Enter 0 to Exit.\n");

        scanf( "%d", &option );
        while ( (getchar()) != '\n' );                                                /* clear the input buffer               */

        if( (option >= 1) && (option <= 4) )
        {
            accFuncs[option-1](acc);
            
        }
        else if( option == 0 )
        {
            return;
        }
        else
        {
            printf("Wrong option number\n");
        }

        printf("====================================================================\n");
        printf("====================================================================\n\n");

    } while ( 1 );  

}


/**************************************************************************************************
 * Lets the user make a transaction (Deposit, Withdraw) in the given account
 * @param acc Pointer to the given account to make transaction in
 **************************************************************************************************/
void ACC_Transact( Account* acc )
{
    u32     option;

    void (*transFuncs[])(Account*) = {ACC_Deposit, ACC_Withdraw};
 
    
    printf("====================================================================\n");
    printf("====================================================================\n\n");
    printf("Choose an option: \n");
    printf("1- Deposite\n");
    printf("2- Withdraw\n");
    printf("0- Exit\n");

    scanf("%d", &option);
    while ( (getchar()) != '\n' );

    if( (option >= 1) && (option <= 2))
    {
        transFuncs[option-1]( acc );
    }
    else if( option == 0 )
    {
        return;
    }
    else
    {
        printf("Invalid option!.\n");
    }
    printf("====================================================================\n");
    printf("====================================================================\n\n");
    
}


/**************************************************************************************************
 * Deposites money to the given account
 * @param acc Pointer to the given account
 **************************************************************************************************/
void ACC_Deposit(Account* acc)
{
    u32         amount;                             /* The amount of money to deposit                                           */
    Transact    newTrans;                           /* New transaction to append to the list of transaction in the given account */

    
    printf("Enter the amount of money to deposite : \n");

    scanf( "%d", &amount );
    while ( (getchar()) != '\n' );              /* Clear input buffer */

    if( amount < 100 )
    {
        printf("Sorry, the least amount to deposite is 100 EGP.\n");
    }
    else
    {   
        acc->balance   += amount;                       /* Add the amount to the balance of the account */
        newTrans.amount = amount;
        strcpy( newTrans.type, "DEPOSIT" );
        TRANS_Append( acc->transHistory, newTrans );
    }
     
}


/**************************************************************************************************
 * Withdraw money from the given account
 * @param acc Pointer to the given account
 **************************************************************************************************/
void ACC_Withdraw(Account* acc)
{
    u32         amount;                             /* The amount of money to withdraw                                          */
    Transact    newTrans;                           /* New transaction to append to the list of transaction in the given account */

    printf("Enter the amount of money to Withdraw : \n");

    scanf( "%d", &amount );
    while ( (getchar()) != '\n' );

    if( amount < 20)
    {
        printf("Sorry, the least amout to withdraw is 20 EGP.\n");
    }else if( amount > 5000)
    {
        printf("Sorry, the most amount to withdraw is 5000 EGP.\n");
    }
    else
    {
        acc->balance   -= amount;                   /* Remove the amount from the balance of the account */
        newTrans.amount = amount;
        strcpy( newTrans.type, "WITHDRAW" );
        TRANS_Append( acc->transHistory, newTrans );
    }
    
}


/**************************************************************************************************
 * Displays the transaction history of a given account chronologically
 * @param acc Pointer to the given account
 **************************************************************************************************/
void ACC_DisplayHistory(Account* acc) 
{
    
    TRANS_DisplayList(acc->transHistory);
    
}
