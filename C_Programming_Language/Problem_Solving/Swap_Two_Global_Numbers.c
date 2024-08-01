#include <stdio.h>
#include <stdlib.h>


int Num1 = 55 ;
int Num2 = 66 ;

void swap_numbers (int *num1 , int *num2 );
int main()
{
    printf("Before swap..... \n");
    printf("Num1 = %i \t Num2 = %i \n",Num1, Num2);
    swap_numbers( &Num1 , &Num2);   // call by refrence
    printf("After swap..... \n");
    printf("Num1 = %i \t Num2 = %i \n",Num1, Num2);  //value of Num1 & Num2 changes.
    return 0;
}

void swap_numbers (int *num1 , int *num2 )   /** using pointers to change the original values inside Num1 & Num2 **/
{
    int temp =0 ;
    temp = *num1 ;
    *num1 = *num2 ;
    *num2 = temp ;
    printf("Swap Function..... \n");
    printf("Num1 = %i \t Num2 = %i \n",Num1, Num2);
}
