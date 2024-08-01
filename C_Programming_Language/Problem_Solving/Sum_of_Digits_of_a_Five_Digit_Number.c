#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
	
    int n,res;
    int sum=0;
    scanf("%d", &n);
    for (int i=0 ; i<=20 ; i++)
    {
        res = n%10;
        sum = sum+res;
        n=n/10;
        if (n==0)
            break;
    }
    printf("%d",sum);
    return 0;
}
