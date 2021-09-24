#include "AVL_Tree.h"
AVL_TREE avl_tree_init_default(void){
	AVL_Tree* pTree = (AVL_Tree*)malloc(sizeof(AVL_Tree));
	if(pTree != NULL){
		pTree->root = NULL;
	}
	return (AVL_TREE) pTree;
}
int return_height(Node* pNode){
	if(pNode == NULL){
		return 0;
	}
	return pNode->height;
}
int calculate_max(int a, int b){
	if(a > b){
		return a;
	}
	return b;
}
int return_balance_factor(Node* pNode){
        if(pNode == NULL){
                return 0;
        }
        return return_height(pNode->left) - return_height(pNode->right);
}
Node* rotate_right(Node* pNode){
	Node* new_root = (Node*)malloc(sizeof(Node));
	if(new_root == NULL){
		return NULL;
	}
	Node* leaf = (Node*)malloc(sizeof(Node));
     	if(leaf == NULL){
                return NULL;
        }	
	new_root = pNode->left;
	leaf = new_root->right;

	new_root->right = pNode;
	pNode->left = leaf;

	pNode->height = calculate_max(return_height(pNode->left), return_height(pNode->right)) + 1; 
	new_root->height = calculate_max(return_height(new_root->left), return_height(new_root->right)) + 1;

	return new_root;
}
Node* rotate_left(Node* pNode){
        Node* new_root = (Node*)malloc(sizeof(Node));
        if(new_root == NULL){
                return NULL;
        }
        Node* leaf = (Node*)malloc(sizeof(Node));
        if(leaf == NULL){
                return NULL;
        }
        new_root = pNode->right;
        leaf = new_root->left;

        new_root->left = pNode;
        pNode->right = leaf;

        pNode->height = calculate_max(return_height(pNode->left), return_height(pNode->right)) + 1;
        new_root->height = calculate_max(return_height(new_root->left), return_height(new_root->right)) + 1;

        return new_root;
}
Node* new_node(MY_STRING new_key, MY_STRING word){
	Node* pNode = (Node*)malloc(sizeof(Node));
	if(pNode != NULL){
		pNode->string_key = my_string_init_c_string(my_string_c_str(new_key));
		pNode->string_group = generic_vector_init_default(my_string_assignment, my_string_destroy);
		generic_vector_push_back(pNode->string_group, word);
		pNode->left = NULL;
		pNode->right = NULL;
		pNode->height = 1;
	}
	return pNode;
}
GENERIC_VECTOR find_largest_group(Node* pNode){
	GENERIC_VECTOR biggest_family;
	GENERIC_VECTOR big_family = generic_vector_init_default(my_string_assignment, my_string_destroy);
	int i;
	biggest_family = assist_find_largest_group(pNode);
	for(i = 0; i < generic_vector_get_size(biggest_family); i++){
		generic_vector_push_back(big_family, generic_vector_at(biggest_family, i));
	}
	return big_family;
}
GENERIC_VECTOR assist_find_largest_group(Node* pNode){
	Generic_vector* left_child = NULL;
	Generic_vector* right_child = NULL;
	Generic_vector* biggest_child = NULL;
	//theres no groups to compare
	if(pNode->left == NULL && pNode->right == NULL){
		return pNode->string_group;
	}
	//if theres only a right child is it bigger?
	else if(pNode->left == NULL && pNode->right != NULL){
		right_child = find_largest_group(pNode->right);
		if(generic_vector_get_size(right_child) > generic_vector_get_size(pNode->string_group)){
			return right_child;
		}
			return pNode->string_group;
	}
	//if theres only a left child is it bigger?
	else if(pNode->left != NULL && pNode->right == NULL){
		left_child = find_largest_group(pNode->left);
                if(generic_vector_get_size(left_child) > generic_vector_get_size(pNode->string_group)){
                        return biggest_child;
                }
                        return pNode->string_group;
        }
	//Ok now both kids aren't null which ones bigger and is the bigger one bigger than the OG group of words
	else if(pNode->left != NULL && pNode->right != NULL){
		if(generic_vector_get_size(pNode->left->string_group) > generic_vector_get_size(pNode->right->string_group)){
			biggest_child = find_largest_group(pNode->left);
		}
		biggest_child = find_largest_group(pNode->right);
		if(generic_vector_get_size(biggest_child) > generic_vector_get_size(pNode->string_group)){
                        return biggest_child;
                }
                        return pNode->string_group;
	}
	return pNode->string_group;
}
Node* tree_insert(Node* pNode, MY_STRING string_key, MY_STRING word){
	int balance;
	int compare_result;
	if(pNode == NULL){
		return new_node(string_key, word);
	}		
	compare_result = my_string_compare(string_key, pNode->string_key);
	if(compare_result == -1){
		pNode->left = tree_insert(pNode->left, string_key, word);
	}
	else if(compare_result == 1){
		pNode->right = tree_insert(pNode->right, string_key, word);
        }
	else{
                generic_vector_push_back(pNode->string_group, word);
        }
	pNode->height = calculate_max(return_height(pNode->left), return_height(pNode->right)) + 1;
	
	balance = return_balance_factor(pNode);
	
	if(balance < -1 && my_string_compare(string_key, pNode->right->string_key) ==  -1){
		pNode->right = rotate_right(pNode->right);
		return rotate_left(pNode);
		}
	if(balance < -1 && my_string_compare(string_key, pNode->right->string_key) ==  1){
                return rotate_left(pNode);
                }
	if(balance > 1 && my_string_compare(string_key, pNode->left->string_key) ==  1){
                pNode->left = rotate_left(pNode->left);
                return rotate_right(pNode);
                }
	if(balance > 1 && my_string_compare(string_key, pNode->left->string_key) ==  -1){
                return rotate_right(pNode);

                }
	return pNode;
}
void tree_destroy(Node** pRoot){
	if(*pRoot != NULL){
		tree_destroy(&((*pRoot)->left));
		tree_destroy(&((*pRoot)->right));
		my_string_destroy(&((*pRoot)->string_key));
		generic_vector_destroy(&((*pRoot)->string_group));
		free(*pRoot);
		*pRoot = NULL;
	}
}
