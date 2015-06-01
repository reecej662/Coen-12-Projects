//
//  set.h
//  project2
//
//  Created by Reece Jackson on 1/20/15.
//  Copyright (c) 2015 Reece Jackson. All rights reserved.
//

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY 0
#define FILLED 1
#define DELETED 2

typedef struct{
    char** elts;
    int num_elts;
    int length;
    char* flags;
} SET;

SET *createSet(int maxElts);
//return a pointer to a new set with a maximum capacity of maxElts

void destroySet(SET *sp);
//deallocate memory associated with the set pointed to by sp

int numElements(SET *sp);
//return the number of elements in the set pointed to by sp

bool hasElement(SET *sp, char *elt);
//return whether elt is a member of the set pointed to by sp

bool addElement(SET *sp, char *elt);
//add elt to the set pointed to by sp, and return whether the set changed

bool removeElement(SET *sp, char *elt);
//remove elt from the set pointed to by sp, and return whether the set changed
