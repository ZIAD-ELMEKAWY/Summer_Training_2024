#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
 /*** Return_two_Numbers_of_function ***/

int Num1 = 66 ;
int Num2 = 77 ;

void fun (int *ptrnum1 , int *ptrnum2);
int main()
{
    printf("Before Editing ........ \n");
    printf("Number_1 = %i \t Number_2 = %i \n",Num1 , Num2);
    fun (&Num1 , &Num2);
    printf("Editing please wait ");
    for(int counter = 0; counter < 15; counter++)  /** this loop is used for motion graphic not more ^_^ **/
    {
        printf(".");
        Sleep(100);
    }
    printf("\n");
    printf("Number_1 = %i \t Number_2 = %i \n",Num1 , Num2);
    return 0;
}

 void fun (int *ptrnum1 , int *ptrnum2)  /** function return one value but here return more than one value **/
 {
     *ptrnum1 = 999 ;
     *ptrnum2 = 666;

 }
