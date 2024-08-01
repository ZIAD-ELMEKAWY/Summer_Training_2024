#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main()
{
    char *s;
    s = malloc(1024 * sizeof(char));
    scanf("%[^\n]", s);
    s = realloc(s, strlen(s) + 1);
     for (int i =0 ; i< strlen(s)  ; i++)
    {
        if (s[i]!=' ')
        {
            printf("%c",s[i]);
        }
        else
        {
            printf("\n");
            continue;
        }
    }
    return 0;
}
