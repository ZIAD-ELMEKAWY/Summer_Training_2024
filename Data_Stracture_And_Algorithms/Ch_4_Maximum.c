#include <stdio.h>
#include <stdlib.h>

int max(int array[], int n);

int main()
{
    int array[] = {4,1,8,6,0,9,5,2,3,7};
    int length = 10;

    printf("max: %d\n", max(array, length));

    return 0;
}

int max(int array[], int n)
{
    if (n == 1)
        return array[n - 1];

    int possible_max = max(array, n - 1);

    if (possible_max > array[n - 1])
        return possible_max;
    else
        return array[n - 1];
}
