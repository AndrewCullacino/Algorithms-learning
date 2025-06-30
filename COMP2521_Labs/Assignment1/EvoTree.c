// COMP2521 - Assignment 1
// Implementation of the Evolutionary Tree ADT

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EvoTree.h"
#include "EvoTreeStructs.h"

// Helper function prototypes
static void freeNode(struct node *node);
static int countNode(struct node *node);
static void printInOrder(struct node *node, FILE *out, bool *isFirst);
static int findRelativesHelper(struct node *node, int leftmost, int rightmost,
                            int speciesNumber, Species relatives[], int count);
////////////////////////////////////////////////////////////////////////
// Basic Operations

/**
 * Creates a new empty evolutionary tree
 */
EvoTree EvoTreeNew(void) {
    // allocate memory for the evolutionary tree
    struct evoTree *et = malloc(sizeof(struct evoTree));

    // check if the memory allocation is successful
    if (et == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // this tree is empty
    et->root = NULL;

    // return this new empty tree
    return et;
}

/**
 * Frees all memory allocated to the evolutionary tree
 */
void EvoTreeFree(EvoTree et) {
    // free all memory, which need to free every node and then the root

    // but this function only has a evotree parameter, so we need a helper function
    if (et == NULL) return;

    freeNode(et->root);

    free(et);
}

// helper function to free all nodes
static void freeNode (struct node *node) {
    if (node == NULL) return;

    // recursively free left and right
    freeNode(node->left);
    freeNode(node->right);

    // free the speciesName
    free(node->speciesName);
    
    // free the node itself
    free(node);
}

/**
 * Inserts a new species into the evolutionary tree. Does nothing if the
 * supplied species number already exists in the tree.
 */
void EvoTreeInsert(EvoTree et, int speciesNumber, char *speciesName) {
    // check if the tree exists
    if (et == NULL) return;

    // create a new node
    struct node *new = malloc(sizeof(struct node));
    if (new == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // initialize the new node, copy speciesName
    new->speciesName = strdup(speciesName);     // if this failed, it's an error
    if (new->speciesName == NULL) {
        fprintf(stderr, "Error: String duplicate failed.\n");
        free(new);  // free the memory allocated
        exit(EXIT_FAILURE);
    }
    new->speciesNumber = speciesNumber;
    new->left = NULL;
    new->right = NULL;

    // for empty tree
    if (et->root == NULL) {
        et->root = new;
        return;
    }

    // find the insertion place, also traverse to check duplicated species number
    struct node *curr = et->root;
    struct node *parent = NULL; // this is used for connect back to the root

    while (curr != NULL) {
        parent = curr;

        // if duplicate found, free the memory and terminates immediately
        if (speciesNumber == curr->speciesNumber) {
            free(new->speciesName);
            free(new);
            return;
        } else if (speciesNumber < curr->speciesNumber) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    // insert the newnode
    if (speciesNumber < parent->speciesNumber) {
        parent->left = new;
    } else {
        parent->right = new;
    }

}

/**
 * Returns the number of species in the evolutionary tree
 */
int EvoTreeNumSpecies(EvoTree et) {
    // count how many nodes including root
    if (et == NULL) {
        return 0;
    }

    return countNode(et->root);

}

static int countNode (struct node *node) {
    if (node == NULL) {
        return 0;
    }

    return 1 + countNode(node->left) + countNode(node->right);
}

/**
 * Prints all of the species in the evolutionary tree to the given file
 * in ascending order of species number. The list of species should be
 * printed inside a pair of curly braces, with species separated by a
 * comma and space, and each species should be printed inside a pair of
 * parentheses with its species number and name separated by a comma and
 * space.
 */
void EvoTreePrint(EvoTree et, FILE *out) {
    // if et is NULL or file is NULL
    if (et == NULL || out == NULL) return;

    // print opening and closing brackets
    fprintf(out, "{");

    // print species in order

    bool isFirst = true;
    printInOrder(et->root, out, &isFirst);
    

    fprintf(out, "}");
    fflush(out);    //bug fix: ensure no newline
}

static void printInOrder(struct node *node, FILE *out, bool *isFirst) {
    // deal with empty node
    if (node == NULL) return;

    // visit smaller numbers (left node)
    printInOrder(node->left, out, isFirst);

    if (*isFirst) {
        fprintf(out, "(%d, %s)", node->speciesNumber, node->speciesName);
        *isFirst = false;
    } else {
        fprintf(out, ", (%d, %s)", node->speciesNumber, node->speciesName);
    }
    
    // Visit right subtree last (larger numbers)
    printInOrder(node->right, out, isFirst);
}

////////////////////////////////////////////////////////////////////////
// Classifying Species

/**
 * Returns the name of the species with the given species number, or the
 * string "undefined" if there is no species with that species number.
 */
char *EvoTreeFind(EvoTree et, int speciesNumber) {
    // handle invalid input

    if (et == NULL) return "undefined";

    if (et->root == NULL) return "undefined";

    struct node *curr = et->root;
    while (curr != NULL) {
        if (speciesNumber == curr->speciesNumber) {
            return curr->speciesName;
        } else if (speciesNumber < curr->speciesNumber) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

    }

    return "undefined";
}


/**
 * Given a species number, this function stores the species that make up
 * its evolutionary history in the given `history` array in order of
 * recency, and returns the number of species stored.
 */
int EvoTreeHistory(EvoTree et, int speciesNumber, Species history[]) {
    // for safety use concern, I still put the invalid input handle here
    // although assuming the species of give number exists
    
    // it's finding the path between the given species and root reversely
    // then counting how many edges are there
    if (et == NULL || et->root == NULL) return 0;

    // use temporary array to store in normal order (root -> target)
    struct node *path[114514];
    int pathlength = 0;

    // search for target species
    struct node *curr = et->root;
    bool found = false;

    // traverse the tree
    while (curr != NULL) {
        path[pathlength++] = curr;  // bug fix: increment should be done here

        if (speciesNumber == curr->speciesNumber) {
            found = true;
            break;  // mission accomplished
        } else if (speciesNumber < curr->speciesNumber) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

    }

    // if no species found, return 0
    if (!found) return 0;

    // fill up the history
    for (int i = 0; i < pathlength; i++) {
        history[i].name = path[pathlength - 1 - i]->speciesName;
        history[i].number = path[pathlength - 1 - i]->speciesNumber;
    }

    return pathlength;

}

/**
 * Given a species number and a positive integer `width`, this function
 * stores all relatives of the species in the given `relatives` array in
 * ascending order of species number, and returns the number of species
 * stored.
 * Two different species are called relatives if their species numbers
 * differ by at most `width`.
 */
int EvoTreeRelatives(EvoTree et, int speciesNumber,
                     int width, Species relatives[]) {
    // handle invalid input
    if (et == NULL || et->root == NULL) return 0;
    
    // the target: speciesNumber +/- width/2
    // Range: [speciesNumber - width/2, speciesNumber + width/2]

    // bug fix: DO NOT divide 2
    int leftmost = speciesNumber - width;
    int rightmost = speciesNumber + width;

    return findRelativesHelper(et->root, leftmost, rightmost, speciesNumber, relatives, 0);
}

static int findRelativesHelper(struct node *node, int leftmost, int rightmost,
                            int speciesNumber, Species relatives[], int count) {
    if (node == NULL) return count;

    // Process left subtree
    count = findRelativesHelper(node->left, leftmost, rightmost, speciesNumber, relatives, count);
    
    // Only add if it's in range 
    // bug fix: AND not the species itself
    if (node->speciesNumber >= leftmost && node->speciesNumber <= rightmost && 
        node->speciesNumber != speciesNumber) {
        relatives[count].number = node->speciesNumber;
        relatives[count].name = node->speciesName;
        count++;
    }
    
    // Process right subtree if needed
    if (node->speciesNumber < rightmost) {
        count = findRelativesHelper(node->right, leftmost, rightmost, speciesNumber, relatives, count);
    }
    
    return count;
}


////////////////////////////////////////////////////////////////////////
// Common Ancestry

/**
 * Given an array of species numbers and its size, this function returns
 * the most recent common ancestor of all the valid species numbers in
 * the array.
 */
Species EvoTreeCommonAncestor(EvoTree et, int speciesNumbers[], int size) {
    // handle invalid input
    if (et == NULL || et->root == NULL) return (Species) {-1, "undefined"};

    // only check the valid input in the array
    // so deal with invalid arr size
    if (size <= 0) return (Species) {-1, "undefined"};

    // loop through each array element
    // find valid input and put them into another array
    // get the min and max to find the common ancestor(least upper node)

    int validcount = 0;
    int *validSpecies = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        char *name = EvoTreeFind(et, speciesNumbers[i]);
        if (strcmp(name, "undefined") != 0) {
            validSpecies[validcount++] = speciesNumbers[i];
        }
    }

    // if no valid species found
    if (validcount == 0) {
        free(validSpecies);
        return (Species) {-1, "undefined"};
    }
    // get the min and max
    int min = validSpecies[0];
    int max = validSpecies[0];
    for (int i = 1; i < validcount; i++){
        if (validSpecies[i] < min) min = validSpecies[i];
        if (validSpecies[i] > max) max = validSpecies[i];
    }
    free(validSpecies);

    // traverse the tree
    struct node *curr = et->root;
    while (curr != NULL) {
        if (curr->speciesNumber < min) {
            curr = curr->right;
        } else if (curr->speciesNumber > max) {
            curr = curr->left;
        } else {
            // now we find the node we want
            break;
        }
    }

    return (Species) {curr->speciesNumber, curr->speciesName};
}

/**
 * Given two valid species numbers, this function stores the path that
 * connects the two species (from `speciesNumberA` to `speciesNumberB`)
 * in the provided `path` array, and returns the number of species
 * stored.
 */
int EvoTreeEvolutionPath(EvoTree et, int speciesNumberA,
                         int speciesNumberB, Species path[]) {
    
    // assume the AB number are different
    if (et == NULL || et->root == NULL) return 0;

    // check if A and B are valid species number
    char *nameA = EvoTreeFind(et, speciesNumberA);
    char *nameB = EvoTreeFind(et, speciesNumberB);

    if (strcmp(nameA, "undefined") == 0 || strcmp(nameB, "undefined") == 0) {
        return 0;  // One or both species not found
    }

    struct node *pathToA[1000]; 
    struct node *pathToB[1000];
    int lenA = 0;
    int lenB = 0;

    struct node *curr = et->root;
    while (curr != NULL) {
        pathToA[lenA++] = curr;
        if (curr->speciesNumber == speciesNumberA) {
            break;
        } else if (speciesNumberA < curr->speciesNumber) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    
    curr = et->root;
    while (curr != NULL) {
        pathToB[lenB++] = curr;
        if (curr->speciesNumber == speciesNumberB) {
            break;
        } else if (speciesNumberB < curr->speciesNumber) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    // go to root/lowerst common ancestor(lca)
    int lcaIdx = 0;
    while (lcaIdx < lenA && lcaIdx < lenB && 
           pathToA[lcaIdx]->speciesNumber == pathToB[lcaIdx]->speciesNumber) {
        lcaIdx++;
    }
    lcaIdx--; 

    // initialzie and prepare
    int pathIdx = 0;
    
    // Start with species A
    path[pathIdx].number = speciesNumberA;
    path[pathIdx].name = pathToA[lenA - 1]->speciesName;
    pathIdx++;

    // Go up from A to LCA
    for (int i = lenA - 2; i >= lcaIdx; i--) {
        path[pathIdx].number = pathToA[i]->speciesNumber;
        path[pathIdx].name = pathToA[i]->speciesName;
        pathIdx++;
    }
    
    // Go down from LCA to B
    for (int i = lcaIdx + 1; i < lenB; i++) {
        path[pathIdx].number = pathToB[i]->speciesNumber;
        path[pathIdx].name = pathToB[i]->speciesName;
        pathIdx++;
    }
    
    return pathIdx;

}

////////////////////////////////////////////////////////////////////////
// Tree Reconstruction

/**
 * Constructs and returns an evolutionary tree from its post-order
 * traversal provided in the `data` array.
 */
EvoTree EvoTreeConstruct(Species data[], int size) {
    if (size <= 0) return NULL;
    
    EvoTree et = EvoTreeNew();
    
    // Simple approach: just insert nodes from the array
    // The BST property will ensure correct structure
    for (int i = 0; i < size; i++) {
        EvoTreeInsert(et, data[i].number, data[i].name);
    }
    
    return et;
}

////////////////////////////////////////////////////////////////////////
// Generating Intermediate Species

/**
 * Given an acceptable gap between species, this function generates
 * intermediate species to fill all unacceptable gaps within the given
 * evolutionary tree, and returns the number of species generated.
 */
int EvoTreeGenerateIntermediate(EvoTree et, int acceptableGap) {
    // TODO
    return -1;
}

////////////////////////////////////////////////////////////////////////
