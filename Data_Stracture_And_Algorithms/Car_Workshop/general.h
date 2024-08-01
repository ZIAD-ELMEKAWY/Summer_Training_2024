/*
 * File:   queue.c
 * Author: Ziad Elmekawy
 *
 * Created on 02 October, 2023, 11:20 ?
 */

#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

/************ Section : includes ************/
#include <stdio.h>
#include <stdlib.h>
#include "Platform.h"

/************ Section : Macro Declarations ***************/
#define Max_Stack_Size 50
#define Max_Queue_Size 50
#define Max_Size       100


/************* Section : Macro Function Declarations *************/

/************* Section : Data Type Declarations *************/


typedef struct
{
    char *Name[Max_Size];
    int ID ;
    int Model_year;
    uint32 stack_pointer;
}Customer_t;


/************* Section : Function Declarations *************/


#endif // GENERAL_H_INCLUDED
