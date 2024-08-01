#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int First_Name_Size , Second_Name_Size;
    int n=0;
    int counter = 0;
    char Name1[] = {"blue"};
    char Name2[] = {"clues"};
    First_Name_Size = sizeof(Name1)/sizeof(Name1[0]);
    Second_Name_Size = sizeof(Name2)/sizeof(Name2[0]);
    if(First_Name_Size > Second_Name_Size)
    {
        n= First_Name_Size;
    }
    else
    {
        n= Second_Name_Size ;
    }
    int cell[n][n];
    for(int i=0 ; i<n-1 ; i++)
    {
        for (int j=0 ; j<n-1 ; j++)
        {
            if(Name1[i] == Name2[j])
            {
                cell[i][j] = cell[i-1][j-1]+1;
            }
            else
            {
                cell[i][j]=0;
            }
        }
    }
    for(int i=0 ; i<n-1 ; i++)
    {
        printf("\n");
        for(int j=0 ; j<n-1 ; j++)
        {
            printf("%i ",cell[i][j]);
        }
    }
    return 0;
}

// counter++;
//                printf("%i ",counter);
