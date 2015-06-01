//
//  unsorted.c
//  project2
//
//  Created by Reece Jackson on 1/20/15.
//  Copyright (c) 2015 Reece Jackson. All rights reserved.
//

#include <stdio.h>
#include "set.h"

int findElement(SET *sp, char* elt);

/*
*   Function: createSet 
*
*   Description: creates a set with room for a given number of elements
*
*   Complexity: O(1)
*/

SET *createSet(int maxElts)
{
    //allocate space for the elements of the set
    SET* new_set = (SET*) malloc(sizeof(SET));
    new_set->elts = (char**) calloc(maxElts, sizeof(char*));
    
    //initialize the value of the set
    new_set->num_elts = 0;
    new_set->length = maxElts;

    return new_set;
}

/*
*   Function: destroySet
*
*   Description: frees the memory of an inputted set 
*
*   Complexity: O(n)
*/

void destroySet(SET *sp)
{
    //itterate over and free each element
    for(int i = 0; i < sp->num_elts; i++)
    {
        free(sp->elts[i]);
    }

    //free the other values of the set and the set itself
    free(sp->elts);
    free(sp);
}


/*
*   Function: numElements
*
*   Description: returns the number of elements in a given set
*
*   Complexity: O(1)
*/

int numElements(SET *sp)
{
    return sp->num_elts;
}


/*
*   Function: hasElement
*
*   Description: returns true if an inputted set has a given element, otherwise returns false
*
*   Complexity: O(n)
*/

bool hasElement(SET *sp, char* elt){

    //itterates over each element of the set and compares strings
    for(int i = 0; i < sp->num_elts; i++)
    {
        if(strcmp(elt, sp->elts[i]) == 0)
            return true;
    }

    return false;
}

/*
*   Function: addElement
*
*   Description: if the element is not already in the set, the function adds the given element to the inputted set and returns true on completion
*
*   Complexity: O(n)
*/

bool addElement(SET *sp, char* elt){

    //checks if the element is already part of the set 
    if(hasElement(sp, elt) == true)
        return false;

    //allocate space for the new element and copy it in
    sp->elts[sp->num_elts] = (char*) malloc(sizeof(elt));
    strcpy(sp->elts[sp->num_elts], elt);

    sp->num_elts++;

    return true;
}

/*
*   Function: removeElement
*
*   Description: finds and removes the given element from the inputted set 
*
*   Complexity: O(n)
*/

bool removeElement(SET *sp, char* elt)
{
    //find the location of the element
    int index = findElement(sp, elt);
    
    //swap the location with the location of the last element in the set to remove the element
    if(index > 0)
    {
        sp->elts[index] = sp->elts[sp->num_elts - 1];
        sp->num_elts--;
        return true;
    }
    else if(index == 0 && sp->num_elts != 0)
    {
        sp->elts[0] = NULL;
        sp->elts[0] = sp->elts[sp->num_elts - 1];
    	sp->num_elts--;
        return true;
    }
    else    
        return false;
}

/*
 *  Function
 *
 *  Description: returns the location of an element in the set and returns -1 if the element is not in the set
 *
 *  Complexity: O(n)
 */

int findElement(SET *sp, char* elt)
{
    //itterates over the whole set and returns the location if found
    for(int i = 0; i < sp->num_elts; i++)
    {
        if(strcmp(sp->elts[i], elt) == 0)
            return i;
    }
    
    return -1;
}
