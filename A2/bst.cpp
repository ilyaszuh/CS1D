#include "bst.h"
#include <stddef.h>  // For NULL
#include <stdlib.h>  // For malloc, free

void insert_into(struct Node** root, int value)
{
    struct Node *y = NULL;
    struct Node *x = *root;
    struct Node *z = NULL;
    z = new struct Node;
    z->value = value;
    z->left = NULL;
    z->right = NULL;

    while(x != NULL)
    {
        y = x;
        if(x->value == value)
			{
				delete z;
            return;
			}
        if(z->value < x->value)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    if(y == NULL)
    {
        *root = z;
    }
    else if(z->value < y->value)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
	return;
}

void free_tree(struct Node* root) {
	if(root == NULL)
	{
		return;
	}
	free_tree(root->left);
	free_tree(root->right);
	delete root;
	return;
}

size_t size_of(const struct Node* root) {
	//Use same functionality as inorder tree walk to count number of elements
	int count = 0;
	if(root != NULL)
	{
		count += size_of(root->left);
		count++;
		count += size_of(root->right);
	}
	return count;
}

int* contents_of(const struct Node* root) {
	if(root == NULL)
		return 0;
    size_t size = size_of(root);
    int* a = (int*)calloc(size, sizeof(int));
    if (a == NULL) {
        return NULL;
    }
    int index = 0;
    tree_walk(a, index, root);
    return a;
}

const struct Node* second_min_in(const struct Node* root) {
	int size = size_of(root);
	if(size < 2)
	{
		return NULL;
	}
	int* temparr = contents_of(root);
	int secondMin = temparr[1];
	while(secondMin != root->value && root != NULL)
	{
		if(secondMin < root->value)
		{
			root = root->left;
		}
		else
		{
			root = root->right;
		}
	}
	free(temparr);
	return root;
}

void inorder_tree_walk(const struct Node* x)
	{
    if(x != NULL)
    {
        inorder_tree_walk(x->left);
		  cout << x->value << ", ";
        inorder_tree_walk(x->right);
    }
	return;
}

void tree_walk(int* a, int &index, const struct Node* root)
{
	if(root == NULL)
	{
		return;
	}
		tree_walk(a, index, root->left);
		a[index++] = root->value;
		tree_walk(a, index, root->right);
}

const struct Node* tree_minimum(const struct Node* root, const struct Node* p)
{
	int* temparr = contents_of(root);
	int smallest = *temparr;
	while(smallest != root->value && root != NULL)
	{
		if(smallest < root->value)
		{
			root = root->left;
		}
		else
		{
			root = root->right;
		}
	}
	free(temparr);
	return root;
}
