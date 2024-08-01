#include <stdio.h>
#include <stdlib.h>

#include "Linked_list.h"

struct Node *ListHead = NULL ;

int main()
{
    uint16 NumberFunction =0 ;

    printf("enter data at list head : ");
    scanf("%s",&ListHead);



    printf("To get any function insert function number \n");
    printf("/***************** HELP ***********************/ \n");
    printf("1 - Insert Node at Beginning \n");
    printf("2 - Insert Node at End \n");
    printf("3 - Insert Node After \n");
    printf("4 - Delete Node At Beginning \n");
    printf("5 - Delete Node \n");
    printf("6 - Display Node \n");
    printf("7 - Get Length \n");
    printf("8 - Quit from Application \n");
    printf("/***************** HELP ***********************/ \n");



    printf("Enter Number Function : ");
    scanf("%i",NumberFunction);


    switch(NumberFunction){
        case 1:
            Insert_Node_at_Beginning(&ListHead);
        break;
        case 2:
            Insert_Node_at_End(&ListHead);
        break;
        case 3:
            Insert_Node_After(ListHead);
        break;
        case 4:
            Delete_Node_At_Beginning(&ListHead);
        break;
        case 5:
            Delete_Node(ListHead);
        break;
        case 6:
            Display_Node(ListHead);
        break;
        case 7:
            Get_Length(ListHead);
        break;
        case 8:
            break;
        default:
            printf("please enter valid number \n");
        break;
    }
    return 0;
}
