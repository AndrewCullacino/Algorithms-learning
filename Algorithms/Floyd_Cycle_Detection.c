// This algorithm is used to detect if there's a cycle, also called 'tortoise and hare'

/**
 * Def: cycle is that when a node create infinite loop
 * e.g. 
 * [1] -> [2] -> [3] -> [4] -> [5]
       ^                   |
       |___________________|
 */

/**
 * The LOGIC: tortoise and hare (龟兔赛跑)
 * Imagine two runners on a circular track:

 * Tortoise (slow): Runs at 1 mph
 * Hare (fast): Runs at 2 mph
 * If the track is straight (no cycle), the hare will reach the finish line first and they'll never meet.
 * If the track is circular (has a cycle), the hare will eventually lap the tortoise and they'll meet!
 */

struct node {
    int value;
    struct node *next;
};

bool hasCycle(struct node* head) {
    // Edge: empty list and 1-element list cannot have cycles
    if (head == NULL || head->next == NULL) {
        return false;   // no cycle detected
    }

    // initialize tortoise and hare
    struct node* tortoise = head;
    struct node* hare = head;

    // traverse the list 
    while(hare != NULL && hare->next != NULL) {

        // turtoise move 1 step
        tortoise = tortoise->next;

        // hare move 2 steps
        hare = hare->next->next;

        //check if they meet
        if (tortoise == hare) {
            return true;
        }

    }

    // if no cycle found at end, return false
    return false;
    
}
