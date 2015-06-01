//
//  table.c
//  project3
//
//  Created by Reece Jackson on 2/2/15.
//  Copyright (c) 2015 Reece Jackson. All rights reserved.
//

#include "set.h"

int findElement(SET *sp, char* elt, bool *found);
unsigned  hashString(char* s);

/*
 *  Function: createSet
 *
 *  Description: Makes a new set with maxElts number of elts initialized to NULL
 *
 *  Complexity: O(1)
 */

SET *createSet(int maxElts)
{
    assert(maxElts > 0);
    
    //allocate space for the new set
    SET* new_set = (SET*) malloc(sizeof(SET));
    new_set->elts = (char**) calloc(maxElts, sizeof(char*));
    new_set->flags = (char*) calloc(maxElts, sizeof(char));   
 
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
 *  Complexity: O(m)
 */

void destroySet(SET *sp)
{
    assert(sp != NULL);
    
    //free elements of the set
    for(int i = 0; i < sp->length; i++)
    {
	if(sp->flags[i] == FILLED)
        	free(sp->elts[i]);
    }
    
    //free the values of the set
    free(sp->elts);
    free(sp->flags);
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
    assert(sp != NULL);
    return sp->num_elts;
}

/*
 *  Function: hasElement
 *
 *  Description: Returns true or false based on whether an inputted set has the given element
 *
 *  Complexity: O(m) - worst case, O(1) - average case
 */

bool hasElement(SET *sp, char* elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    
    if(sp->num_elts == 0)
     	return false;
	
    //call findElement to determine whether the element is present
    bool found = false;
    
    findElement(sp, elt, &found);

    return found;
}

/*
 *  Function: addElement
 *
 *  Description: Adds a given element alphabetically to the inputted sorted set and returns true or false based on completion
 *
 *  Complexity: O(m) - worst case, O(1) - average case
 */

bool addElement(SET *sp, char* elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    
    //get the hash value for the inputted string   
    unsigned int index = hashString(elt);
    index = index  % sp->length;
    
    //return false if the element is already in the set
    if(hasElement(sp, elt))
	return false;

    //if the set is full, cause the function to fail
    if(sp->num_elts == sp->length)
        return false;

    //itterate along the set, finding the right place in the probe sequence
    int i = index;    
    do
    {
	if(sp->flags[i] != FILLED)
		index = i; 
	else
		i = (i + 1) % sp->length;
    }while(i != index);

    if(sp->flags[index] != FILLED)
    {
	//allocate the space for the new element
	sp->elts[index] = malloc(sizeof(elt));
	sp->num_elts++;

	//copy the element into the set and set the flag to filled
	sp->elts[index] = strdup(elt);
	sp->flags[index] = FILLED;

        return true;
    }        

   return false;

}


/*
 *  Function: removeElement
 *
 *  Description: Removes a given element from the inputted sorted set and returns true or false based on completion
 *
 *  Complexity: O(m) - worst case, O(1) - average case
 */

bool removeElement(SET *sp, char* elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    
    //find the element in the set
    bool found = false; 
    int index = findElement(sp, elt, &found);
	
    //return false if it's not there
    if(!found)
	return false;
	
    //if it's filled, remove it and return
    if(sp->flags[index] == FILLED)
    {
	free(sp->elts[index]);
	sp->flags[index] = DELETED;
	sp->num_elts--;

	return true;
    }
	
    return false;
}

/*
 *  Function: findElement
 *
 *  Description: Uses a binary search algorithm to alphabetically search for the appropriate index of an inputted elemenet in a sorted set and returns that index
 *
 *  Complexity: O(m) - worst case, O(1) - average case
 */

int findElement(SET *sp, char* elt, bool* found)
{
    assert(sp != NULL);
    assert(elt != NULL);
    assert(found != NULL);
    
	//check the hash element for the index 
	unsigned int start = hashString(elt) % sp->length;
	int loc;

	//itterate along the whole set
	for(int i = 0; i < sp->length; i++)
	{
		//increment the location linearly along the probe sequence
		loc  = start + i % sp->length;

		//return the appropriate value based on the value of the flag
		if(sp->flags[loc] == EMPTY){
			*found = false;
			return -1; 
		}else if(sp->flags[loc] == FILLED && strcmp(sp->elts[loc], elt) == 0){
                        *found = true;
                        return loc;
                }
	}

	return -1;
}

/*
*  Function: hashString
*
*  Description: Hashes a string to a location in the set
*
*  Complexity: O(1)
*/ 

unsigned hashString(char *s)
{
    unsigned hash = 0;

    while(*s != '\0')
	hash = 31 * hash + *s ++;

    return hash;
}
