//
//  deque.c
//
//
//  Created by Reece Jackson on 2/22/15.
//
//

#include "deque.h"

/*
 * Function: createDeque
 *
 * Description: returns a pointe to a new deque
 *
 * Complexity: O(1)
 */

DEQUE* createDeque(void) {
    
    // allocate space for the new deque and initialize its values
    DEQUE* newDeque = (DEQUE*) malloc(sizeof(DEQUE));
    newDeque->head = (NODE*) malloc(sizeof(NODE));
    newDeque->tail = newDeque->head;
    newDeque->count = 0;
    
    // initialize the values for the sentinel node
    newDeque->head->next = newDeque->head;
    newDeque->head->prev = newDeque->head;
    newDeque->head->value = (int) NULL;
    
    return newDeque;
    
}

/*
 * Function: destroyDeque
 *
 * Description: Deallocates the memory of the inputted deque
 *
 * Complexity: O(n)
 */

void destroyDeque(DEQUE *dp) {
    
    assert(dp != NULL);
    
    NODE* curr = dp->head;
    
    // itteratively free each node of linked list
    while(curr != dp->tail) {
        
        curr = curr->next;
        free(curr->prev);
        
    }
    
    free(curr);
    
}

/*
 * Function: numItems
 *
 * Description: returns the number of items in the given deque
 *
 * Complexity: O(1)
 */

int numItems(DEQUE *dp) {
    
    assert(dp != NULL);
    
    return dp->count;
    
}

/*
 * Function: addFirst
 *
 * Description: adds a new node with value x at the beginning of the inputted deque
 *
 * Complexity: O(1)
 */

void addFirst(DEQUE *dp, int x) {
    
    assert(dp != NULL);
    
    // allocate new node
    NODE* newNode = (NODE*) malloc(sizeof(NODE));
    
    // initialize the values of the new node
    newNode->next = dp->head->next;
    newNode->prev = dp->head;
    newNode->value = x;
    
    // reasign the value of the first node and increment the count
    if(dp->head->next != NULL) {
        
        dp->head->next->prev = newNode;
        dp->head->next = newNode;
        
    } else {
        
        dp->tail = newNode;
        
    }
    
    dp->head->next = newNode;
    dp->count++;
    
}

/*
 * Function: addLast
 *
 * Description: adds a new node with value x at the end of the inputted deque
 *
 * Complexity: O(1)
 */

void addLast(DEQUE *dp, int x) {
    
    assert(dp != NULL);
    
    // allocate new node
    NODE* newNode = (NODE*) malloc(sizeof(NODE));
    
    // initialize values of the new node
    newNode->next = dp->head;
    newNode->prev = dp->tail;
    newNode->value = x;
    
    // reassign values of the tail and sentinel node and increment the count
    if(dp->tail != NULL) {
        
        dp->tail->next = newNode;
        dp->head->prev = newNode;
        
    } else {
        
        dp->head->next  = newNode;
        
    }
    
    dp->tail = newNode;
    dp->count++;
    
}

/*
 * Function: removeFirst
 *
 * Description: Removes and returns the first node in the deque
 *
 * Complexity: O(1)
 */

int removeFirst(DEQUE *dp) {
    
    assert(dp->count > 0);
    
    // make a temporary pointer to the first node
    NODE* temp = dp->head->next;
    
    // assign the sentinel node to point to the following node and vice versa
    dp->head->next = dp->head->next->next;
    dp->head->next->prev = dp->head;
    
    // if you're removing the last node in the deque reassign the tail
    if(temp == dp->tail)
        dp->tail = dp->head;
    
    // store the return value and free the node
    int returnValue = temp->value;
    free(temp);
    
    dp->count--;
    
    return returnValue;
}

/*
 * Function: removeLast
 *
 * Description: Removes and returns the last node in the deque
 *
 * Complexity: O(1)
 */

int removeLast(DEQUE *dp) {
    
    assert(dp->count > 0);
    
    // make a temporary pointer to the last node
    NODE* temp = dp->tail;
    
    // assign the sentinel prev to point to the second to last node and vice versa
    dp->head->prev = dp->tail->prev;
    dp->tail->prev->next = dp->head;
    dp->tail = dp->tail->prev;
    
    // store the return value and free the node
    int returnValue = temp->value;
    free(temp);
    
    dp->count--;
    
    return returnValue;
}

/*
 * Function: getFirst
 *
 * Description: Returns the value of the first node in the deque
 *
 * Complexity: O(1)
 */

int getFirst(DEQUE *dp) {
    
    assert(dp->count > 0);
    
    return dp->head->next->value;
    
}

/*
 * Function: getLast
 *
 * Description: Returns the value of the last node in the deque
 *
 * Complexity: O(1)
 */

int getLast(DEQUE *dp) {
    
    assert(dp->count > 0);
    
    return dp->tail->value;
    
}
