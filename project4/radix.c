#include "deque.h"
#include <math.h>

#define RADIX 10

int getValue();

/*
 * Function: main
 *
 * Description: prompts the user for a number of inputs and sorts the list using radix sort
 *
 * Complexity: O(nk), where k is the number of digits of the largest value (in base of the radix)
 */

int main(int argc, char* argv[]) {
	
	// create initial deque to store data
	DEQUE* inputNums = createDeque();

	// prompt the user to input numbers into the deque
	int count = 0;
	printf("How many numbers do you want to input into the deque? ");
	scanf("%d", &count);
	printf("\n");

	// variables to keep track of input and max
	int max = -1;
	int val = -1;

	// use getValue to get values greater than 0
	for(int i = 0; i < count; i++) {
	
		val = getValue();

		if(max < val)
			max = val;
	
		if(val > 0) 
			addLast(inputNums, val);		
	
	}	
	
	// create the array of deques to sort to
	DEQUE** dequeArray = (DEQUE**) malloc(sizeof(DEQUE*) * RADIX);

	// create all the deques 
	for(int i = 0; i < RADIX; i++)
		dequeArray[i] = createDeque();

	// maxItteration is the number of digits of the largest value
	int itteration = 0;
	int maxItteration = (log10(max))/log10(RADIX);

	while(itteration <=  maxItteration) {
	
                int div = 1;

		// get the significant digit by dividing and taking the mod of the radix
       	        for(int i = 0; i < itteration; i++)
        	        div = div * RADIX;
	
		// add the value to the deque based on its significant digit
		while(inputNums->count > 0) {		

			int value = removeFirst(inputNums);
			int sigDig = (value / div) % RADIX;
	
			addLast(dequeArray[sigDig], value);
		}
	
		// move values to initial array after all have been sorted
		for(int i = 0; i < RADIX; i++) {
			
			while(dequeArray[i]->count > 0) {
				
				addLast(inputNums, removeFirst(dequeArray[i]));
	
			}
			
		} 
	
		itteration++;
	}

	// print the sorted values
	while(numItems(inputNums) > 0) {

		printf("%d ", removeFirst(inputNums));

	}

	printf("\n");

	// free the allocated memory
	for(int i = 0; i < RADIX; i++)
		destroyDeque(dequeArray[i]);

	destroyDeque(inputNums);
	free(dequeArray);

	return 0;
}

/*
 * Function: getValue()
 *
 * Description: Prompts the user the enter an integer greater than 0
 *
 * Complexity: O(1)
 */

int getValue() {
	
	int number = -1;
	printf("Enter an integer greater than 0: ");
	scanf("%d", &number);
	
	while(number < 0) {
		
		printf("Number is not greater than 0. Please enter an integer greater than 0: ");
		scanf("%d", &number);
	
	}
	
	return number;

}
