#include <stdio.h>
#include <stdlib.h>

int main()
{
    int temp = 0;
    int arr[] = {6,3,1,5} ;
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int i = 0 ; i<n-1 ; i++)
    {
        for(int j = 0; j<n-i-1 ; j++)
        {
            if(arr[j] > arr[(j+1)])
            {
                temp  = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp ;
            }
            else
            {
                continue;
            }
        }
    }
    for(int x=0 ; x<n ; x++)
    {
        printf("%i ",arr[x]);
    }
    return 0;
}
