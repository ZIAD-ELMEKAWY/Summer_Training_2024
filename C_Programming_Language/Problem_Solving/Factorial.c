#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

unsigned int Number =0 ;
int factorial (int FactNumber);
void Motion (void);

int main()
{
    printf("********Factorial Number**************\n");
    printf("Enter the number : ");
    scanf("%i",&Number);
    Motion();
    printf("The factorial of %i = %i \n", Number , factorial(Number));
    return 0;
}

int factorial (int FactNumber)
{
    int result = 0;
    if (FactNumber == 0)
    {
        result = 1 ;
    }
    else
    {
        result = (FactNumber * factorial(FactNumber-1));
    }
    return result;
}

void Motion (void)
{
    printf("Please wait ");
        for(int UserPassIndex = 0; UserPassIndex < 15; UserPassIndex++)
        {
            printf(".");
            Sleep(100);
        }
        printf("\n");
}
