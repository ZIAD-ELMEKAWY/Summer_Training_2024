#include "Linked_list.h"
#include <stdio.h>
#include <string.h>

uint32 Get_Length(struct Node *List)
{
    struct Node *TempNode = List;
    uint32 Node_Count = 0;
    while(TempNode != NULL)
    {
        Node_Count++;
        TempNode = TempNode->NodeLink;
    }
    return Node_Count;
}

void Insert_Node_at_Beginning(struct Node **List)
{
    struct Node *TempNode = NULL;
    /** Create node َ**/
    TempNode = (struct Node *)malloc(sizeof(struct Node));
    if(NULL != TempNode)
    {
        printf("Enter Node data : ");
        scanf("%i",&TempNode->NodeData);      /*** TempNode stored the address of data which will add ***/

        /** Check if linked list is empty **/
        if (NULL == *List)
        {
            TempNode->NodeLink = NULL ;   /** Linked list is empty and this node is the first then we will make node_link equals NULL **/
            *List = TempNode;
        }
        else
        {
            TempNode->NodeLink = *List;   /** Linked list is not empty and there are a node then we will make node_link equals the node_link which is entered before **/
            *List = TempNode;             /** pass TempNode Link to List Head **/
        }
    }
    else
    {
        printf("is false \n");
    }
}

void Insert_Node_at_End(struct Node **List)
{
    struct Node *TempNode = NULL ;
    struct Node *LastNode = NULL ;

    TempNode = (struct Node *)malloc(sizeof(struct Node));
    if (NULL != TempNode)
    {
        printf("Enter node data : ");
        scanf("%i",&TempNode->NodeData);
        TempNode->NodeLink = NULL;
        if (NULL == *List)
        {
            *List = TempNode;
        }
        else
        {
            LastNode = *List;
            while(LastNode->NodeLink != NULL)
            {
                LastNode = LastNode->NodeLink ;
            }
            LastNode->NodeLink = TempNode;
        }
    }
    else
    {
        /* Nothing */
    }
}

void Insert_Node_After(struct Node *List)
{
    struct Node *TempNode = NULL , *NodeListCounter = NULL;   /** NodeListCounter made to make traverse at noedes **/
    uint32 NodePosition = 0 , ListLength = 0 , NodeCounter = 1 ;
    printf("Enter Node Position : ");
    scanf("%i",&NodePosition);
    ListLength=Get_Length(List);
    if(ListLength <  NodePosition)
    {
        printf("Invalid Node position \n");
    }
    else
    {
        NodeListCounter = List;
        while(NodeCounter < NodePosition)
        {
            NodeCounter++;
            NodeListCounter = NodeListCounter->NodeLink;
        }
        /** to create a node **/
        TempNode = (struct Node *)malloc(sizeof(struct Node));
        if(NULL != TempNode)
        {
            printf("Enter Node data : ");
            scanf("%i",&TempNode->NodeData);
            /** To make link between the last node first (first link from right then left) **/
            TempNode->NodeLink = NodeListCounter->NodeLink;
            NodeListCounter->NodeLink = TempNode ;    /** To link TempNode & NodeListCounter **/
        }
        else{/* Nothing */}
    }
}

void Delete_Node_At_Beginning (struct Node **List)
{
    struct Node *TempNode = *List ;  /** TempNode now stored List Head which is contain the address of first node **/
    uint32 ListLength = 0;

    ListLength = Get_Length(*List);
    if(ListLength == 0)
    {
        printf("Linked List is empty \n");
    }
    else
    {
        *List = TempNode->NodeLink;   /** Take the (TempNode->NodeLink) and write it in list head **/
        TempNode->NodeLink = NULL ;   /** TempNode is free **/
        free(TempNode);
    }
}

void Delete_Node (struct Node *List)
{
   struct Node *NodeListCounter = List;
   struct Node *NodeNext = List ;
   uint32 NodePosition = 0 ;
   uint32 ListLength = 0 ;
   uint32 NodeCounter = 1 ;

   printf("Enter Node Position (First Node is position = 1) : ");
   scanf("%i",&NodePosition);
   ListLength=Get_Length(List);
   if((NodePosition > ListLength) || (ListLength == 1))
   {
       printf("Please use Delete_Node_at_Beginning \n");
   }
   else
   {
       while(NodeCounter < (NodePosition-1))
       {
           NodeCounter++;
           NodeListCounter = NodeListCounter->NodeLink;
       }
       NodeNext = NodeListCounter->NodeLink;
       NodeListCounter->NodeLink = NodeNext->NodeLink;
       free(NodeNext);
   }
}

void Display_Node(struct Node *List)
{
    struct Node *TempNode = List;
    printf("Node values : ");
    if(NULL == TempNode)
    {
        printf("Ohps........Linked List is empty!! \n");
    }
    else
    {
        while(TempNode != NULL)
        {
            printf("%i " , TempNode->NodeData);
            TempNode = TempNode->NodeLink;
        }
        if(NULL == TempNode)
        {
            printf("NULL \n");
        }
    }
}

