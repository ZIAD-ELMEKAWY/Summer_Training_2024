/*
 * File:   stack.h
 * Author: Ziad Elmekawy
 *
 * Created on 02 October, 2023, 11:20 ?
 */

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

/************ Section : includes ************/
#include <stdio.h>
#include <stdlib.h>
#include "general.h"
/************ Section : Macro Declarations ***************/

/************* Section : Macro Function Declarations *************/

/************* Section : Data Type Declarations *************/


/************* Section : Function Declarations *************/
static void Create_Stack (Customer_t *my_Stack);
static void Add_New_Customer (int ID , int year_model , Customer_t *my_Stack);
static void Serve_Customer (Customer_t *my_Stac) ;
static void Number_of_Customers (Customer_t *my_Stack) ;
static void Display_Customer_Information_in_most_recent(Customer_t *my_Stack);
static void Motion(void) ;
static void Display_Customer_Information(Customer_t *my_Stack) ;

#endif // STACK_H_INCLUDED
