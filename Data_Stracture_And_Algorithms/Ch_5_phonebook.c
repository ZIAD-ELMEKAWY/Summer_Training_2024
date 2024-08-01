#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 30

typedef struct
{
    char *name[MAX_SIZE];
    int number;
}phonebook_t;

phonebook_t phonebook ;


int main()
{
    int i=0;
    char *name[MAX_SIZE];
    printf("phone book\n");
    do
    {
       printf(" Enter name and phone --> enter 1 \nQuit--> enter 0..\n");
       scanf("%i",&i);
       if(i==1)
       {
           printf("Enter name : ");
           _flushall();
           gets(phonebook.name);
           printf("Enter Number : ");
           scanf("%i",&phonebook.number);
       }
       else
       {
           break;
       }
    }while(true);
    printf("Enter the name you need to know its number : ");
    _flushall();
    gets(name);
    if(strcmp(phonebook.name , name)==0)
    {
       printf("name : %s \t number : %i \n",phonebook.name , phonebook.number);

    }
    return 0;
}
