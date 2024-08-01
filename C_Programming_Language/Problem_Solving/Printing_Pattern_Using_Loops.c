#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num, *arr, i , j;
    scanf("%d", &num);
    arr = (int*) malloc(num * sizeof(int));
    for(i = 0; i < num; i++)
    {
        scanf("%d", arr + i);
    }


    /* Write the logic to reverse the array. */

    for(j = (num-1); j >= 0; j--)
        printf("%d ", *(arr + j));
    return 0;
}
