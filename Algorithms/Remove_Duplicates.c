// This file is used to record the Leetcode linked list problems
// Algorithms are written in C
// Andrew Wang 15 Jun 2025

struct node {
    int value;
    struct node *next;
};


// 1. Delete the duplicates in the linked lists
/**
 * This function is to delete the duplicates in a sorted linked lists
 * e.g.
 * input: [1,1,2,3,4]
 * ouput:[1,2,3,4]
 */

struct node* deleteDuplicates(struct node* head) {
    // because the list is sorted
    // we need to traverse the list to find the duplicates

    // EDGE: No duplicates
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // traverse the list 
    struct node *curr = head;

    // we must ensure that curr is not NULl as well
    while (curr != NULL && curr->next != NULL) {
        // compare the current value to the one after
        if (curr->value == curr->next->value) {
            // if they are equal, delete
            struct node *temp = curr->next;

            // now we are at the curr
            curr->next = curr->next->next;
            free(temp);
        } else {
            // check for the following duplicates
            // if no duplicates found, moving forward
            curr = curr->next;
        }

    }

    return head;
}
