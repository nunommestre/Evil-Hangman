#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "generic.h"
#include "generic_vector.h"
#include "my_string.h"
#include "status.h"
typedef void* AVL_TREE;
//tried to make an opaque object, but I couldn't make it work

typedef struct node Node;
struct node{
        int height;
        Node* left;
        Node* right;
        MY_STRING string_key;
        GENERIC_VECTOR string_group;
};

typedef struct avl_tree AVL_Tree;
struct avl_tree{
        Node* root;
};

Node* rotate_right(Node* pNode);
Node* rotate_left(Node* pNode);
Node* tree_insert(Node* pNode, MY_STRING string_key, MY_STRING word);
int return_height(Node* pNode);
int return_balance_factor(Node* pNode);
Node* new_node(MY_STRING new_key, MY_STRING word);
GENERIC_VECTOR find_largest_group(Node* pNode);
GENERIC_VECTOR assist_find_largest_group(Node* pNode);
void tree_destroy(Node** pRoot);
AVL_TREE avl_tree_init_default(void);
int calculate_max(int a, int b);
#endif
