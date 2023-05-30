/*H**************************************************************************************************************
 * FILENAME :       common.h

 * DESCRIPTION :    
 *              Common macros for the project
 * 
 * AUTHOR :     Ahmed Osman                 START DATE :    18 May 2023
 * 
 * CHANGES : 
 * 
 *  VERSION       DATE              WHO             DETAIL
 *  1.0.0         18 May 2023       A.O             Made the file
 **************************************************************************************************************H*/


#ifndef COMMON_H
#define COMMON_H

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>                  /* for the  toupper() function          */
                    
#define bool unsigned char
#define false 0
#define true 1



typedef   unsigned  char               u8;
typedef   signed    char               s8;
typedef   unsigned  short  int         u16;
typedef   signed    short  int         s16;
typedef   unsigned  long   int         u32;
typedef   signed    long   int         s32;
typedef   unsigned  long   long   int  u64;
typedef   signed    long   long   int  s64;
typedef   float                        f32;
typedef   double                       f64;





#endif