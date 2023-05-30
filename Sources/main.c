#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../Headers/account_list.h"
#include "../Headers/account_bst.h"


void fun1(int x){
    printf("%d\n", x);
}


void wrap_fun(int z ,void (*fun)(int))
{
    fun(z);
}


int main()
{

    // LIST_MainMenu();
    
    // BST_MainMenu();

    wrap_fun(5, fun1);
    
    return 0;
}

