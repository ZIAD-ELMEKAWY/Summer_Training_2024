#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdio.h>
#include "platform.h"

struct Node
{
    unsigned int NodeData;
    struct Node *NodeLink;
};

void Insert_Node_at_Beginning(struct Node **List);
void Insert_Node_at_End(struct Node **List);
void Insert_Node_After(struct Node *List);
void Delete_Node_At_Beginning (struct Node **List);
void Delete_Node (struct Node *List);
void Display_Node(struct Node *List);
uint32 Get_Length(struct Node *List);



#endif // _LINKED_LIST_H
