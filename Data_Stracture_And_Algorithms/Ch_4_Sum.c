#include <stdio.h>
#include <stdlib.h>

int sum (int arr[],int num);

int main()
{
    int res = 0;
    int arr[] = {1, 2, 3, 4, 5};
    int num = sizeof(arr)/ sizeof(arr[0]);
    res=sum(arr , num);
    printf("sum of list = %i",res);
    return 0;
}

int sum (int arr[] , int num)
{
    if (num<=0)
        return 0 ;
    return (sum(arr,(num-1)) + arr[num-1]);
}
