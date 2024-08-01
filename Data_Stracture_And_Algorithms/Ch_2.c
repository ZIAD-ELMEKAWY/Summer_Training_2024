#include <stdio.h>
#include <stdlib.h>


void Smallest_element (int arr[] , int len);
void Sort_element (int arr[] , int len);

int main()
{
    int arra[] = {5, 3, 6, 10, 2};
    Smallest_element(arra , 5);
    Sort_element(arra , 5);
    return 0;
}

void Smallest_element (int arr[] , int len)
{
    int temp = arr[0] ;
    printf("Smallest element = %i \n" , temp);
    for (int i=0 ; i < (len-1) ; i++)
    {
        if(temp > arr[i+1])
        {
            temp = arr[i+1];
        }
        else
        {
            continue;
        }
    }
    printf("Smallest element = %i \n" , temp);

}

void Sort_element (int arr[] , int len)
{
    int temp = arr[0] ;
    for (int i=0 ; i < (len) ; i++)
    {
        for (int j=(i+1) ; j<(len) ; j++)
        {
            if(arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
    printf("array elements : ");
    for(int x=0 ; x<len ; x++)
    {
        printf("%i ", arr[x]);
    }
}
