// COMP2521 - Assignment 1
// Concrete representation of the Evolutionary Tree ADT

#ifndef EVO_TREE_STRUCTS_H
#define EVO_TREE_STRUCTS_H

// DO NOT CHANGE THE NAME OF THIS STRUCT
struct evoTree {
    struct node *root;  // DO NOT MODIFY/REMOVE THIS FIELD

    // You may add more fields here if needed
};

// DO NOT CHANGE THE NAME OF THIS STRUCT
struct node {
    int speciesNumber;  // DO NOT MODIFY/REMOVE THIS FIELD
    char *speciesName;  // DO NOT MODIFY/REMOVE THIS FIELD
    struct node *left;  // DO NOT MODIFY/REMOVE THIS FIELD
    struct node *right; // DO NOT MODIFY/REMOVE THIS FIELD

    // You may add more fields here if needed
};

// You may define more structs here if needed

#endif

