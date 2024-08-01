#include <stdio.h>
#include <stdlib.h>

int count (int num);

int main()
{
    int a=0;
    printf("please enter your number : ");
    scanf("%i",&a);
    printf("%i", count(a));
    return 0;
}

int count (int num)
{
    static int counter=0;
    if (num > 0)
    {
        counter++;
        count(num/10);
    }
    else
        return counter;
}
