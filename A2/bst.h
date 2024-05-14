#ifndef BST_Included
#define BST_Included
#include <iostream>
#include <stddef.h> // For size_t
using namespace std;

/* Type: struct Node
 *
 * A type representing a node in a binary search tree.
 * The keys are integers.
 */
struct Node {
  int value;
  struct Node* left;
  struct Node* right;
};

/**
 * Inserts a new value into the binary search tree whose root pointer is pointed
 * at by root. The behavior of this function is unspecified in the case
 * where memory for a new node can't be allocated or if root is NULL.
 * <p>
 * This function does not make any attempt to balance the tree. It simply inserts
 * the element in to the BST following the standard insertion algorithm. This may
 * lead to significantly imbalanced trees.
 * <p>
 * If the specified value already exists in the given BST, this function has no
 * effect and does not change the underlying BST.
 *
 * @param root  The root of the tree, which may be updated.
 * @param value The value to insert.
 */
void insert_into(struct Node** root, int value);

/**
 * Deallocates all memory associated with the indicated binary search tree.
 *
 * @param root The root of the tree to free.
 */
void free_tree(struct Node* root);

/**
 * Returns the number of elements in the binary search tree pointed at by root.
 *
 * @param root The root of the tree in question.
 * @return The number of elements in that tree.
 */
size_t size_of(const struct Node* root);

/**
 * Returns a dynamically-allocated array containing the contents of the tree
 * in sorted order. The behavior of this function is unspecified in the case
 * where the appropriate memory can't be obtained.
 *
 * @param root A pointer to the root of the tree.
 * @return An array of the tree's elements, in sorted order.
 */
int* contents_of(const struct Node* root);

/**
 * Returns a pointer to the node in the specified tree containing the second-
 * smallest element in the tree. If the tree has zero or one elements, this
 * function returns NULL.
 *
 * @param root The root of the tree in question.
 * @return A pointer to the node holding the second-smallest element in the
 *         tree, or NULL if such a node doesn't exist.
 */
const struct Node* second_min_in(const struct Node* root);

//Helper Functions

/**
 * Prints out all the keys in a binary search tree in sorted order.
 * Prints the key of the root of a subtree between printing the values
 * in its left subtree and printing those in its right subtree.
 *
 * @param root The root of the tree to print
 */
void inorder_tree_walk(const struct Node* root);
void inorder_tree_walk_build(const struct Node* root, int [], int &);

/**
 * Prints the root before the values in either subtree.
 *
 * @param root The root of the tree to print
 */
void preorder_tree_walk(const struct Node* root);

/**
 * Prints the root after the values in its subtrees.
 *
 * @param root The root of the tree to print
 */
void postorder_tree_walk(const struct Node* root);

/**
 * Searches for a node with a given key in a binary search tree.
 * Given a pointer to the root of the tree and a key k, TREE-SEARCH
 * returns a pointer to a node with key k if one exists; otherwise, 
 * it returns NIL.
 * 
 * @param root The root of the tree to search
 * @return A pointer to a node with key k if one exists, otherwise,
 * it returns NIL.
 */
const struct Node* tree_search(const struct Node* x, int k);

/**
 * The following procedure returns a pointer to the minimum element in
 * the subtree rooted at a given node x, which we assume to be non-NIL:
 *
 * @param root The root of the tree to search for the minimum
 * @return A point to the minimum node in the tree,
 */
const struct Node* tree_minimum(const struct Node* x, const struct Node* p);

size_t count_tree(const struct Node* x);
void in_order_tree_count(const struct Node* x, size_t &count);

void tree_walk(int* a, int &index, const struct Node* root);



#endif
