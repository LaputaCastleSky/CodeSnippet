#ifndef _ALG_STACK_H_INCLUDE_
#define _ALG_STACK_H_INCLUDE_
#include <stdio.h>
#include <stddef.h>

typedef struct alg_stack_s alg_stack_t;

struct alg_stack_s{
    alg_stack_t *next;
    alg_stack_t *prev;
};

#define alg_stack_init(s)           \
    (s)->next = (s);                \
    (s)->prev = (s);

#define alg_stack_empty(s)          \
    ((s) == (s)->prev)

#define alg_stack_remove(x)         \
    (x)->next->prev = (x)->prev;    \
    (x)->prev->next = (x)->next;    \
    (x)->next = NULL;               \
    (x)->prev = NULL

#define alg_stack_top(s)            \
    (s)->next

#define alg_stack_push(t, x)        \
    (x)->next = (t)->next;          \
    (x)->next->prev = x;            \
    (x)->prev = t;                  \
    (t)->next = x

static alg_stack_t *_stack_pop(alg_stack_t *s){
    alg_stack_t *t = NULL;
    t = alg_stack_top(s);
    alg_stack_remove(t);
    return t;
}

#define stack_pop(s)                \
    _stack_pop(s)

#define alg_stack_data(s, type, link)       \
    (type *)((char *)(s) - offsetof(type, link))

#define alg_stack_pop_data(s, type, link)   \
    alg_stack_data(_stack_pop(s), type, link)

#endif  //! endif _ALG_STACK_H_INCLUDE_
