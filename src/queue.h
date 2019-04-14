#ifndef _QUEUE_H_INCLUDE_
#define _QUEUE_H_INCLUDE_

#include <stddef.h>
#include <stdio.h>

typedef struct queue_s queue_t;

struct queue_s{
     queue_t *next;
     queue_t *prev; 
};

#define queue_init(q)               \
    (q)->next = q;                  \
    (q)->prev = q

#define queue_head(h)               \
    (h)->next

#define queue_last(h)               \
    (h)->prev

#define queue_empty(h)              \
    ((h) == (h)->prev)

#define queue_insert_head(h, x)     \
    (x)->next = (h)->next;          \
    (x)->next->prev = x;            \
    (x)->prev = h;                  \
    (h)->next = x

#define queue_insert_tail(h, x)     \
    (x)->prev = (h)->prev;          \
    (x)->prev->next = x;            \
    (x)->next = h;                  \
    (h)->prev = x;

#define queue_prev(q)               \
    (q)->prev

#define queue_next(q)               \
    (q)->next

#define queue_remove(x)             \
    (x)->next->prev = (x)->prev;    \
    (x)->prev->next = (x)->next;    \
    (x)->next = NULL;               \
    (x)->prev = NULL

#define queue_data(q, type, link)   \
    (type *)((char*)(q) - offsetof(type, link))


#endif  //! endif _QUEUE_H_INCLUDE_
