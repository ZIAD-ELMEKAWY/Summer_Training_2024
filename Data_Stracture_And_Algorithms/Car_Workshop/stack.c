/*
 * File:   stack.c
 * Author: Ziad Elmekawy
 *
 * Created on 02 October, 2023, 11:20 ?
 */
#ifndef STACK_C
#define STACK_C

/************* Section : Includes ***************/
#include "stack.h"
#include <string.h>

/************* Section : Function Definitions ***************/
static void Create_Stack (Customer_t *my_Stack)
{
    if(NULL != my_Stack)
    {
        my_Stack->stack_pointer = -1 ;  /** to intialize stack_pointer equal to -1 **/
    }
    else{/*Nothing*/}
}

static void Add_New_Customer ( int ID , int year_model , Customer_t *my_Stack)
{
    char *Name[Max_Size];
    if(NULL != my_Stack)
    {
        my_Stack->stack_pointer++ ;
        my_Stack->ID = ID ;
        my_Stack->Model_year = year_model ;
        printf("Enter Your Name : ");
        gets(Name);
        strcpy(Name , (my_Stack->Name));
        printf ("Name       : %s \n",(my_Stack->Name));
    }
    else{/*Nothing*/}
}

static void Serve_Customer (Customer_t *my_Stack )
{
    if(NULL != my_Stack)
    {
        printf ("Name       : %s \n",*(my_Stack->Name)) ;
        printf ("ID         : %d \n",my_Stack->ID);
        printf ("Model_year : %d \n",my_Stack->Model_year);
        my_Stack->stack_pointer-- ;
    }
    else{/*Nothing*/}

}

static void Number_of_Customers (Customer_t *my_Stack)
{
    if(my_Stack != NULL)
    {
        printf("Number of Customers : %d \n",(my_Stack->stack_pointer +1));
    }
    else
    { /*Nothing*/ }

}
static void Display_Customer_Information_in_most_recent (Customer_t *my_Stack)
{
    for (int i=(my_Stack->stack_pointer) ; i >= 0 ; i--)
    {
        printf ("Name       : %s \n",my_Stack->Name) ;
        printf ("ID         : %d \n",my_Stack->ID);
        printf ("Model_year : %d \n",my_Stack->Model_year);
    }

}

static void Display_Customer_Information(Customer_t *my_Stack)
{
    printf ("Name       : %s \n",my_Stack->Name) ;
    printf ("ID         : %d \n",my_Stack->ID);
    printf ("Model_year : %d \n",my_Stack->Model_year);
}

static void Motion(void)
{
    printf("Please wait ");
    for(int UserPassIndex = 0; UserPassIndex < 15; UserPassIndex++)
    {
        printf(".");
        Sleep(100);
    }
    printf("\n");
}


#endif // STACK_C
