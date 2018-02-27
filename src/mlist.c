#include "mlist.h"

#include <stdlib.h>
#include <stdio.h>

void mlist_prepend(mlist *head, void *data)
{
    mlist newnode = malloc(sizeof (struct mlist_));

    newnode->next = *head;

    newnode->data = data;

    *head = newnode;
}

void mlist_append(mlist *head, void *data)
{

    mlist newnode = malloc(sizeof (struct mlist_));
    newnode->data = data;

    newnode->next = NULL;

    mlist *cursor = head;

    while((*cursor) != NULL)
	cursor = &((*cursor)->next);

    (*cursor) = newnode;
}

void mlist_map(mlist head, void (*func)(void*))
{
    while(head != NULL)
    {
	func(head->data);
	head = head->next;
    }
}

int mlist_length(mlist head)
{
    int count = 0;
    while(head != NULL)
    {
	head = head->next;
	count++;
    }

    return count;
}

void* mlist_index(mlist head, int index)
{
    if (index < 0)
    {
	printf("mlist_index error: index is negative\n");
	return NULL;
    }

    if (index >= mlist_length(head))
    {
	printf("mlist_index error: out of bounds\n");
	return NULL;
    }
    
    while(index--)
    {
	head = head->next;
    }
    return head->data;
}

void* mlist_remove(mlist *head, int index)
{
    if (index < 0)
    {
	printf("mlist_remove error: index is negative\n");
	return NULL;
    }

    if (index >= mlist_length(*head))
    {
	printf("mlist_remove error: out of bounds\n");
	return NULL;
    }
    
    mlist *cursor = head;
    
    while(index--)
    {
	cursor = &((*cursor)->next);
    }
    
    mlist todel = (*cursor);
    void *toreturn = todel->data;
    (*cursor) = todel->next;
    free(todel);
    return toreturn;
}

void* mlist_pop(mlist *head)
{
    return mlist_remove(head, mlist_length(*head)-1);
}

void mlist_destroy(mlist *head)
{
    int len = mlist_length(*head);

    for (int i = 0; i < len-1; i++)
    {
	mlist_pop(head);
    }

    *head = NULL;
}
