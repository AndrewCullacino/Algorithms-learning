/**
 * The recursive algorithm requires a base case + recursive 
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

struct list {
    struct node *head;
};

struct node *newNode(int value) {
    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    n->value = value;
    n->next = NULL;
    return n;
}

// Task1: shift a list recursively/normally
/**
 * e.g. 
 * input: 16 5 2
 * output: 2 16 5
 */

struct node* listShiftRecursive (struct node *list) {
    // so we can start with empty list (NULL)
    // actually, when the list is only 1 element, same output
    if (list == NULL || list->next == NULL) {
        return list;
    } 

    // BASE case: if 2 elements in the list, just swap them
    // e.g.
    // [5,2] -> [2, 5]
    if (list->next->next == NULL) {
        // create a node
        struct node *lastNode = list->next; // save the last node
        list->next = NULL;                  // disconnect last node from the lsit
        lastNode->next = list;              // last node points to first
        return lastNode;                    // last node becomes new head
    }

    // Recursive part
    // e.g. if we have [16, 5, 2], we want [2, 16, 5]
    // this new head is made to make [5, 2] to [2, 5] newHead

    struct node *newHead = listShift(list->next);

    // this condition is made to check if the recursive call has changed the sublist (if so, do the following change)
    if (newHead != list->next) {
        list->next = newHead->next; // now list is 16 -> 5, and 2->5

        newHead->next = list;       // now list is 2->16->5
        return newHead;
    }

    return list;
}

// if we use normal loops
struct node* listShiftLoop(struct node* list) {
    // edge case
    if (list == NULL || list->next == NULL) {
        return list;
    }

    // using loop to find the second last and last
    struct node *curr = list;
    while (curr->next->next != NULL) {
        curr = curr->next;
    }
    struct node *secondLast  = curr;

    struct node *last = curr->next;

    // then, we made the last node as first node, second node as last node
    secondLast->next = NULL;
    last->next = list;

    return last;
}

// Task2: listSum 
/**
 * This task is to practice using helper functions for recursive functions
 * it should calculate the sum of all the values in the list 
 * 
 * Why do we need a helper here?
 * the list, is a wrapper for user convinence, but we need to access raw data, which is in the nodes
 */

int listSum(struct list *list) {

    return listSumHelper(list->head); 

}

int listSumHelper(struct node *node) {

    if (node == NULL) {
        return 0;
    }

    return node->value = listSumHelper(node->next);
}

// Task3: insert into a list sorted
/**
 * e.g. [2, 5, 7]
 * insert 3
 * output:[2, 3, 5,7]
 * 
 * Additionally: the prototype is void, so we definitely need a helper
 */
void listInsertOrdered(struct list* list, int value) {
    // the given list is sorted, so we must find the first value that is larger or equal to the given value
    // therefore, we may need a helper function

    //Edge: empty list
    if (list == NULL) {
        return NULL;
    }

    list->head = listInsertOrderedHelper(list->head, value);

}

struct node* listInsertOrderedHelper(struct node* head, int value) {
    // BASE case: if the value should be the first node
    if (head == NULL) {
        return newNode(value);
    }

    if (head->value >= value) {
        struct node* new = newNode(value);
        new->next = head;
        return new;
    }

    // recursive: the value should go somewhere else
    head->next = listInsertOrderedHelper(head->next, value);
    return head;    

}

// Task4: insert into nth position of the list
/**
 * e.g. [16, 7, 8]
 * insert: 1 12
 * output: [16, 12, 7, 8]
 * n -> position
 */
void listInsertNth(struct list *list, int n, int value) {
    if (list == NULL) return NULL;

    list->head = listInsertNthHelper(list->head, n, value);

}

struct node* listInsertNthHelper(struct node* head, int n, int value) {
    // so we need to find nth position

    if (head == NULL) return newNode(value);
    // BASE case: added to the first node
    if (n == 0) {
        struct node* new = newNode(value);
        new->next = head;
        return new;
    }
    
    // recursive part
    head->next = listInsertNthHelper(head->next, n - 1, value);
    return head;

}








