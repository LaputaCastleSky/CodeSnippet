#ifndef _BINARY_TREE_H_INCLUDE_
#define _BINARY_TREE_H_INCLUDE_

#include <stdio.h>
#include "queue.h"
#include "alg_stack.h"

typedef struct tree_node_s tree_node_t;
typedef struct tree_s      tree_t;

//definition for a binary tree node.
struct tree_node_s {
    int val;
    tree_node_t *left;
    tree_node_t *right;
    alg_stack_t stack_node;
    queue_t     queue_node;
};

//definition for a binary tree;
struct tree_s{
    tree_node_t *root;
    alg_stack_t stack;
    queue_t     queue;
};

#define tree_init(t)                \
    (t)->root = NULL;               \
    alg_stack_init(&(t)->stack);  \
    queue_init(&(t)->queue)

int* tree_preorder_traversal(tree_t* tree, int* return_size);
int* tree_inorder_traversal(tree_t* tree, int* return_size);
int* tree_postorder_traversal(tree_t* tree, int* return_size);
void tree_inorder_without_recursion(tree_t *tree);
void tree_preorder_without_recursion1(tree_t *tree);
void tree_postorder_without_recursion(tree_t* tree);
void tree_level_order(tree_t *tree);
tree_node_t *tree_search(tree_node_t *root, int val);
tree_node_t *tree_interative_search(tree_node_t *root, int val);
tree_node_t *tree_minimum(tree_node_t *root);
tree_node_t *tree_maximum(tree_node_t *root);
void tree_insert(tree_t *tree, int val);


#endif  //!endif _BINARY_TREE_H_INCLUDE_
