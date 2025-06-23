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