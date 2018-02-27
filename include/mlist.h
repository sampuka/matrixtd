#ifndef MLIST_H
#define MLIST_H

typedef struct mlist_
{
    struct mlist_ *next;
    void *data;
} *mlist;

void mlist_prepend(mlist *head, void *data);

void mlist_append(mlist *head, void *data);

void mlist_map(mlist head, void (*func)(void*));

int mlist_length(mlist head);

void* mlist_index(mlist head, int index);

void* mlist_remove(mlist *head, int index);

void* mlist_pop(mlist *head);

void mlist_destroy(mlist *head);

#endif
