//
//  sorted.c
//  project2
//
//  Created by Reece Jackson on 1/20/15.
//  Copyright (c) 2015 Reece Jackson. All rights reserved.
//

#include <stdio.h>
#include "set.h"

int findElement(SET *sp, char* elt);

/*
 * Function: createSet
 *
 * Description: Makes a new set with maxElts number of elts initialized to NULL
 *
 * Complexity: O(1)
 */

SET *createSet(int maxElts)
{
    //allocate space for the new set
    SET* new_set = (SET*) malloc(sizeof(SET));
    new_set->elts = (char**) calloc(maxElts, sizeof(char*));
    
    //initialzie the values in the set
    new_set->num_elts = 0;
    new_set->length = maxElts;
    
    return new_set;
}

/*
 *  Function: destroySet
 *
 *  Description: Frees an inputted set from memory
 *
 *  Complexity: O(n)
 */

void destroySet(SET *sp)
{
    //free elements of the set
    for(int i = 0; i < sp->num_elts; i++)
    {
        free(sp->elts[i]);
    }
    
    //free the array of the elements
    free(sp->elts);
    
    //free the set itself
    free(sp);
}

/*
 *  Function: numElements
 *
 *  Description: Returns the number of elements of an inputted set
 *
 *  Complexity: O(1)
 */

int numElements(SET *sp)
{
    return sp->num_elts;
}

/*
 *  Function: hasElement
 *
 *  Description: Returns true or false based on whether an inputted set has the given element
 *
 *  Complexity: O(log n)
 */

bool hasElement(SET *sp, char* elt){
    
    if(sp->num_elts == 0)
	return false;
	
    //search for the element that the element should be at
    int index = findElement(sp, elt);
	
    //check to see if the elemenet is at that index and return
    if(sp->elts[index] != NULL &&  strcmp(sp->elts[index], elt) == 0)
        return true;
    return false;
}

/*
 *  Function: addElement
 *
 *  Description: Adds a given element alphabetically to the inputted sorted set and returns true or false based on completion
 *
 *  Complexity: O(n)
 */

bool addElement(SET *sp, char* elt){
    
    //if the set is full, cause the function to fail
    if(sp->num_elts == sp->length)
        return false;
    
    //allocate the space for the new element
    sp->elts[sp->num_elts] = malloc(sizeof(elt));

    //store index of where new element should go
    int index = findElement(sp, elt);

    //make sure the word isn't already in the set
    if(sp->elts[index] != NULL && strcmp(sp->elts[index], elt) == 0)
        return false;
    
    //move current elements in set by 1
    for(int i = sp->num_elts; i > index; i--)
    {
        sp->elts[i] = sp->elts[i-1];
    }

    //copy the element into the location and increment the number of elements
    sp->elts[index] = strdup(elt);
    sp->num_elts++;
	
    return true;
}


/*
 *  Function: removeElement
 *
 *  Description: Removes a given element from the inputted sorted set and returns true or false based on completion
 *
 *  Complexity: O(n)
 */

bool removeElement(SET *sp, char* elt)
{
    //search for potential index of element
    int i, index = findElement(sp, elt);
    
    //if the element is found set it to NULL, otherwise return false
    if(strcmp(sp->elts[index], elt) == 0)
    	free(sp->elts[index]);
    else
        return false;
    
    //decrement the number of elements in the set
    sp->num_elts--;

    //shift indexes of the remaining elements in the set
    for(i = index; i < sp->num_elts; i++)
        sp->elts[i] = sp->elts[i+1];
 
    return true;   
}

/*
 *  Function: findElement
 *
 *  Description: Uses a binary search algorithm to alphabetically search for the appropriate index of an inputted elemenet in a sorted set and returns that index
 *
 *  Complexity: O(log n)
 */

int findElement(SET *sp, char* elt)
{
    //declare variables
    int hi, lo, mid = 0;
    hi = sp->num_elts;
    lo = 0;
    
    while(hi > lo){
        
        mid = (hi + lo)/2;
        if(strcmp(elt, sp->elts[mid])< 0)
        {
            //elt is alphabetically before the mid
            hi = mid;
        }
        if(strcmp(elt, sp->elts[mid])> 0)
        {
            //elt is alphabetically after the mid
            lo = mid + 1;
        }
        if(strcmp(elt, sp->elts[mid])== 0){
            return mid;
        }
    }
    
    return lo;
}

