#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* tree_preorder_traversal(tree_t* tree, int* return_size) {
    if(tree->root == NULL){
        return NULL;
    }
    int size = 0;
    int *arr = NULL;
    tree_node_t *p = tree->root;

    while(!alg_stack_empty(&tree->stack) || p){
        if(p){
            printf("%4d", p->val);
            size++;
            arr = realloc(arr, size*sizeof(int));
            arr[size-1] = p->val;
            alg_stack_push(&tree->stack, &p->stack_node);
            p = p->left;
        }else{
            p = alg_stack_pop_data(&tree->stack, tree_node_t, stack_node);
            p = p->right;
        }
    }
    printf("\n");
    *return_size = size;
    return arr;
}

int* tree_inorder_traversal(tree_t* tree, int* return_size) {
    if(tree->root == NULL){
        return NULL;
    }
    int size = 0;
    int *arr = NULL;
    tree_node_t *p = tree->root;

    while(!alg_stack_empty(&tree->stack) || p){
        if(p){
            alg_stack_push(&tree->stack, &p->stack_node);
            p = p->left;
        }else{
            p = alg_stack_pop_data(&tree->stack, tree_node_t, stack_node);
            size++;
            arr = realloc(arr, size*sizeof(int));
            arr[size-1] = p->val;
            p = p->right;
        }
    }
    *return_size = size;
    return arr;
}

void tree_inorder_without_recursion(tree_t *tree){
    if(tree->root == NULL){
        return;
    }

    tree_node_t *p = tree->root;

    while(!alg_stack_empty(&tree->stack) || p){
        if(p){
            alg_stack_push(&tree->stack, &p->stack_node);
            p = p->left;
        }
        else{
            p = alg_stack_pop_data(&tree->stack, tree_node_t, stack_node);
            printf("%4d", p->val);
            p = p->right;
        }
    }
    printf("\n");
}

void tree_preorder_without_recursion1(tree_t *tree){
    if(tree->root == NULL){
        return;
    }
    tree_node_t *p = tree->root;

    while(!alg_stack_empty(&tree->stack) || p){
        if(p){
            printf("%4d", p->val);
            alg_stack_push(&tree->stack, &p->stack_node);
            p = p->left;
        }else{
            p = alg_stack_pop_data(&tree->stack, tree_node_t, stack_node);
            p = p->right;
        }
    }
    printf("\n");
}

void tree_postorder_without_recursion(tree_t* tree){
    if(tree->root == NULL){
        return;
    }

    tree_node_t *cur = tree->root;
    tree_node_t *last_visit = NULL;

    while(cur){
        alg_stack_push(&tree->stack, &cur->stack_node);
        cur = cur->left;
    }

    while(!alg_stack_empty(&tree->stack)){
        cur = alg_stack_pop_data(&tree->stack, tree_node_t, stack_node);
        if(cur->right == NULL || cur->right == last_visit){
            printf("%4d", cur->val);
            last_visit = cur;
        }else{
            alg_stack_push(&tree->stack, &cur->stack_node);
            cur = cur->right;
            while(cur){
                alg_stack_push(&tree->stack, &cur->stack_node);
                cur = cur->left;
            }
        }
    }
    printf("\n");
}

int* tree_postorder_traversal(tree_t* tree, int* return_size) {
    if(tree->root == NULL){
        return NULL;
    }

    int *arr = NULL;
    int size = 0;
    tree_node_t *cur = tree->root;
    tree_node_t *last_visit = NULL;

    while(cur){
        alg_stack_push(&tree->stack, &cur->stack_node);
        cur = cur->left;
    }

    while(!alg_stack_empty(&tree->stack)){
        cur = alg_stack_pop_data(&tree->stack, tree_node_t, stack_node);
        if(cur->right == NULL || cur->right == last_visit){
            printf("%4d", cur->val);
            size++;
            arr = realloc(arr, size*sizeof(int));
            arr[size-1] = cur->val;
            last_visit = cur;
        }else{
            alg_stack_push(&tree->stack, &cur->stack_node);
            cur = cur->right;
            while(cur){
                alg_stack_push(&tree->stack, &cur->stack_node);
                cur = cur->left;
            }
        }
    }
    *return_size = size;
    return arr;
}

tree_node_t *tree_search(tree_node_t *root, int val){
    if(root == NULL || root->val == val){
        return root;
    }
    if(val < root->val){
        return tree_search(root->left, val);
    }else{
        return tree_search(root->right, val);
    }
}

tree_node_t *tree_interative_search(tree_node_t *root, int val){
    tree_node_t *n = root;
    while(n != NULL && val != n->val){
        if(val < n->val){
            n = n->left;
        }else{
            n = n->right;
        }
    }
    return n;
}

tree_node_t *tree_minimum(tree_node_t *root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

tree_node_t *tree_maximum(tree_node_t *root){
    while(root->right != NULL){
        root = root->right;
    }
    return root;
}

void tree_insert(tree_t *tree, int val){
    tree_node_t *p = NULL;
    tree_node_t *n = tree->root;
    tree_node_t *node = NULL;

    node = (tree_node_t *)malloc(sizeof(tree_node_t));
    if(node == NULL){
        printf("malloc error.\n");
        return;
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;

    while(n != NULL){
        p = n;
        if(val < n->val){
            n = n->left;
        }else{
            n = n->right;
        }
    }

    if(p == NULL){  //empry tree
        tree->root = node;
    }else if(val < p->val){
        p->left = node;
    }else{
        p->right = node;
    }
}