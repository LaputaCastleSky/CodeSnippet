#ifndef _ALG_STACK_H_INCLUDE_
#define _ALG_STACK_H_INCLUDE_
#include <stdio.h>
#include <stddef.h>

typedef struct alg_stack_s alg_stack_t;

struct alg_stack_s{
    alg_stack_t *next;
};

#define alg_stack_init(s)           \
    (s)->next = (s)                

#define alg_stack_empty(s)          \
    ((s) == (s)->next)

#define alg_stack_remove_first(s)   \
    (s)->next = (s)->next->next

#define alg_stack_top(s)            \
    (s)->next

#define alg_stack_push(s, x)        \
    (x)->next = (s)->next;          \
    (s)->next = x

static alg_stack_t *_stack_pop(alg_stack_t *s){
    alg_stack_t *t = NULL;
    t = alg_stack_top(s);
    alg_stack_remove_first(s);
    return t;
}

#define stack_pop(s)                \
    _stack_pop(s)

#define alg_stack_data(s, type, link)       \
    (type *)((char *)(s) - offsetof(type, link))

#define alg_stack_pop_data(s, type, link)   \
    alg_stack_data(_stack_pop(s), type, link)

#endif  //! endif _ALG_STACK_H_INCLUDE_
