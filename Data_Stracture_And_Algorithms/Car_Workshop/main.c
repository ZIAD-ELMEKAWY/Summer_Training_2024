/*
 * File:   Main.c
 * Author: Ziad Elmekawy
 *
 * Created on 02 October, 2023, 11:20 ?
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.c"

Customer_t customer1 ;
Customer_t customer2 ;
Customer_t customer3 ;
Customer_t customer4 ;

char Name[] = "Ziad" ;

int main()
{
    Create_Stack(&customer1);
    int Number_of_serve;
    printf("****************** Welcome to Our Car Workshop *******************\n\n");
    printf("1. Add a New Customer.\n2. Serve a Customer.\n3. How many Customers are waiting \n4. Display Customers Information. \n5. Display Customers information in a “most-recent” Order. \n6. Exit \n");

    do
    {
        printf("\nPlease insert the number of your serve : ");
        scanf("%i",&Number_of_serve);
        switch(Number_of_serve)
        {
            case 1:
                printf("Add a New Customer... \n");
                Motion();
                Add_New_Customer( 1234 , 2020 , &customer1 );
                printf("Add a New Customer is done \n");
                break;
            case 2:
                printf("Serve a Customer...   \n");
                Motion();
                Serve_Customer(&customer1);
                printf("Serve a Customer is done \n");
                break;
            case 3:
                Motion();
                Number_of_Customers(&customer1);
                break;
            case 4:
                Motion();
                Display_Customer_Information(&customer1);
                break;
            case 5:
                Motion();
                Display_Customer_Information_in_most_recent(&customer1);
                break;
            case 6:
                printf("Exit \n");
                break;
            default:
                printf("Error !!!!!!!! Please Enter a valid Number \n");
        }
    }while(Number_of_serve != 6);
    return 0;
}
