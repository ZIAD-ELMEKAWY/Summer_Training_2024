#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

/************ Section : Includes ***************/
#include "global.h"
/************ Section : Data Type Declaration ***************/
typedef struct lst
{
    ListEntry entry[MAXLIST];
    int Size ;

}List;
/************ Section : Function Declaration *************/
static void Craete_List(List *pl);
static void List_Empty(List *pl);
static void List_Full (List *pl);
static void List_Size(List *pl);
static void Insert_List(int p , ListEntry e    , List *pl);
static void Delete_List(int p , ListEntry *pe  , List *pl);
static void Destroy_List(List *pl);
static void Traverse_List(List *pl , void (* Visit)(ListEntry));
static void Retrive_List(int p , ListEntry *pe  , List *pl);
static void Replace_List(int p , ListEntry e    , List *pl);
#endif // LIST_H_INCLUDED
