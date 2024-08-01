
/************ Section : Includes **************/
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"


/*********** Section : Function Definition *******/
static void Craete_List(List *pl)
{
    if(pl != NULL)
    {
        pl->Size =0 ;
    }
    else{/*Nothing*/}
}

static void List_Empty(List *pl)
{
    if(pl != NULL)
    {
        return !pl->Size ;
    }
    else{/*Nothing*/}
}

static void List_Full (List *pl)
{
    if(pl != NULL)
    {
        return pl->Size==MAXLIST;
    }
    else{/*Nothing*/}
}


static void List_Size(List *pl)
{
    if(pl != NULL)
    {
        return pl->Size ;
    }
    else{/*Nothing*/}
}

static void Insert_List(int p , ListEntry e, List *pl)
{
    if(pl != NULL)
    {
        int i ;
        for(i=pl->Size-1 ; i>=p ; i-- )
        {
            pl->entry[i+1] = pl->entry[i];
        }
        pl->entry[p] = e ;
        pl->Size++ ;
    }
    else{/*Nothing*/}
}

static void Delete_List(int p , ListEntry *pe  , List *pl)
{
    if(pl != NULL)
    {
        int i ;
        *pe = pl->entry[p];
        /* the loop shifts down all elemens in the range [p+1 , size-1 ] to free the Pth location */
        for(i=p+1 ; i<=pl->Size ; i++)
        {
            pl->entry[i-1]=pl->entry[i];
        }
        pl->Size-- ;
    }
    else{/*Nothing*/}
}

static void Destroy_List(List *pl)
{
    if(pl != NULL)
    {
        return pl->Size=0 ;
    }
    else{/*Nothing*/}
}

static void Traverse_List(List *pl ,void (* Visit)(ListEntry))
{
    if(pl != NULL)
    {
        int i ;
        for(i=0 ; i< pl->Size ; i++)
        {
            (* Visit)(pl->entry[i]);
        }
    }
    else{/*Nothing*/}
}

static void Retrive_List(int p , ListEntry *pe  , List *pl)
{
    if(pl != NULL)
    {
        *pe = pl->entry[p];
    }
    else{/*Nothing*/}
}

static void Replace_List(int p , ListEntry e    , List *pl)
{
    if(pl != NULL)
    {
        pl->entry[p] = e ;
    }
    else{/*Nothing*/}
}
