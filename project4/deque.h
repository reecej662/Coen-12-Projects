/*
 * File:	deque.h
 *
 * Description:	This file contains the public function declarations for a
 *		deque abstract data type for integers.  A deque is a
 *		doubly-ended queue, in which items can only be added to or
 *		removed from the front or rear of the list.
 */

# ifndef DEQUE_H
# define DEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct DEQUE {
    
    struct NODE* head;
    struct NODE* tail;
    int count;
    
} DEQUE;

typedef struct NODE {
    
    struct NODE* next;
    struct NODE* prev;
    int value;
    
} NODE;

DEQUE *createDeque(void);
//return a pointer to a new deque

void destroyDeque(DEQUE *dp);
//deallocate memory associated with the deque pointed to by dp

int numItems(DEQUE *dp);
//return the number of items in the deque pointed to by dp

void addFirst(DEQUE *dp, int x);
//add x as the first item in the deque pointed to by dp

void addLast(DEQUE *dp, int x);
//add x as the last item in the deque pointed to by dp

int removeFirst(DEQUE *dp);
//remove and return the first itemin the deque pointed to by dp; the //deque must not be empty

int removeLast(DEQUE *dp);
//remove and return the last item in the deque pointed to by dp; the //deque must not be empty

int getFirst(DEQUE *dp);
//return, but do not remove, the first item in the deque pointed to by //dp; the deque must not be empty

int getLast(DEQUE *dp);
//return, but do not remove, the last itemin the deque pointed to by dp; the deque must not be empty

# endif /* DEQUE_H */
