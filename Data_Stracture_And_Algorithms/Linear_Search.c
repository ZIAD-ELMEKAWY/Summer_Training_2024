#include <stdio.h>
#include <stdlib.h>

 // Linear Search algorithm
void Linear_Search (int arr[5]);

int main()
{
    int arr[5] = {2,5,8,7,4} ;
    int n, i;

    printf("****** Array Elments ********* \n");
    for(i=0 ; i<5 ; i++)
    {
        printf("%i ",arr[i]);
    }
    Linear_Search(arr);


    return 0;
}

void Linear_Search (int arr[5])
{
    int n, i;
    printf("\nEnter any number: ");
    scanf("%i",&n);
    for(i=0 ; i<5 ; i++)
    {
        if (arr[i] == n)
        {
            printf("your number %i is successfully founded and take %i oerations\n",n,i+1);
            break;
        }
        else
        {
            printf("for element %i Your number is not founded \n",i+1);
        }
    }
}
