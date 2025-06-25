#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

struct node {
	int value;
	struct node *left;
	struct node *right;
};

struct node *newNode(int val);

static void showBstNode(struct node *tree);

static void doBstPrint(struct node *t, FILE *out);





struct node *newNode(int val) {
    struct node *new = malloc(sizeof(struct node));

    // Check if the memory is full or invalid input is detected
    if (new == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    // create the new leaf
    new->value = val;
    new->left = NULL;
    new->right = NULL;

    return new;

}

// In this function, we ignore duplicate and return unchanged tree when duplicate is found
struct node *bstInsert(struct node *tree, int val) {

    // Base case: if tree is empty, return a new node
    if (tree == NULL) return newNode(val);

    if (tree->value > val) tree->left = bstInsert(tree->left, val);

    else if (tree->value < val) tree->right = bstInsert(tree->right, val);

	return tree;
}

bool bstSearch(struct node *tree, int val) {
	
    // Base case: If the tree is NULL, return false
    if (tree == NULL) return false;
    else if (tree->value > val) return bstSearch(tree->left, val);
    else if (tree->value < val) return bstSearch(tree->right, val);
    else return true;

}

/**
 * Assumptions: the max of t1 < the min of t2
 */
struct node *bstJoin(struct node *t1, struct node *t2) {
    if (t1 == NULL) return t2;
    if (t2 == NULL) return t1;


    // if t2 is only 1 node
    if (t2->left == NULL) {
        t2->left = t1;
        return t2;
    }

    // Find the minimum of t2
    struct node *parent = NULL;
    struct node *min = t2;

    // the bst is different from linked lists
    // we cannot extract like min->next->left, so we have a seperate parent node to record
    while (min->left != NULL) {
        parent = min;
        min = min->left;
    }

    parent->left = min->right;  // to put the min of t2 on the root, and avoid duplicate value of right
    min->left = t1;
    min->right = t2;


	return min;
}

struct node *bstDelete(struct node *tree, int val) {

    

















}