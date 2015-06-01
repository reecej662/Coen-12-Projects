/*
 * File:	huffman.c
 *
 * Description:	produce the huffman code for an inputted text file, output the code for each  
 *		character to the terminal, and compress the file using a pack function
 */

#include "tree.h"
#include "pack.h"

#define p(x) (x-1) / 2
#define l(x) (x*2) + 1
#define r(x) (x*2) + 2
#define MAX 257

// global arrays to hold data
struct tree* nodes[MAX];
struct tree* heap[MAX];

// functions for managing priority queue
bool insert(struct tree* input, struct tree** heap, int count);
bool delete(struct tree** dataOut, struct tree** heap, int count);
void reheapUp(struct tree** heap, int childLoc);
void reheapDown(struct tree** heap, int root, int size);
void bits(struct tree** nodes, int character, char* encoding);

/*
 * Function: main
 *
 * Description: driver function for the huffman application
 */

int main(int argc, char* argv[]) {

	if(argc != 3) {

		printf("Error - Usage: ./huffman file1.txt file2.txt.gz\n");
		return 1;

	}

	char* infile = argv[1];
	char* outfile = argv[2];

	FILE* input = fopen(infile, "r");

	char c;

	// read data from the input file and count the number of occurences
	while((c = fgetc(input)) != EOF) {
		
		if(nodes[(int) c] == NULL)
			nodes[(int) c] = createTree(1, NULL, NULL);
		else
			nodes[(int) c]->data++;

	}

	nodes[MAX-1] = createTree(0, NULL, NULL);

	int count = 0;

	//insert the nodes into a priority queue
	for(int i = 0; i < MAX; i++) {

		if(nodes[i] != NULL) {

			insert(nodes[i], heap, count);
			count++;
		}
	}	

	// itterate as long as there is more than one element in the heap
	while(count > 1) {

		//combine the lower two nodes to make one, change the count and insert that into the priority queue, replacing the second one 
		struct tree* node1;
		struct tree* node2;
		delete(&node1, heap, count);
		delete(&node2, heap, count-1);
		
		struct tree* newTree = createTree((node1->data + node2->data), node1, node2);	
	
		insert(newTree, heap, count-2);
		count--;
	
	}

	// compress the input into the outfile
	pack(infile, outfile, nodes);

	char encoding[9];

	// use the bits function to determine the bits corresponding to each letter
	for(int i = 0; i < MAX; i++) {

		if(nodes[i] != NULL) {
			bits(nodes, i, encoding);
			if(isprint(i))
				printf("'%c': %d %s\n", (char) i, nodes[i]->data, encoding);
			else
				printf("%03o: %d %s\n", i, nodes[i]->data, encoding);
		
		}
	}
	
	// free tree and exit
	destroyTree(nodes[0]);

	return 0;

}

/*
 * Function: bits
 *
 * Description: adds 1's and 0's to a string corresponding to character based on whether the node 
 * 		is a left or right child
 */

void bits(struct tree** nodes, int character, char* encoding) {

	struct tree* curr = nodes[character];
	int i = 0;

	for(i = 0; curr->parent != NULL && i < 8; i++) {
		if(curr->parent->left == curr)
		{
			encoding[i] = '0';
			curr = curr->parent;
		} else {
			encoding[i] = '1';
			curr = curr->parent;
		}
	}

	encoding[i] = '\0';
	
	return;
	
}

/*
 * Function: insert
 *
 * Description: insert a node into a heap and reheap up
 */

bool insert(struct tree* input, struct tree** heap, int count) {

	if(count == MAX)
		return false;

	heap[count] = input;
	
	reheapUp(heap, count);

	return true;

}

/*
 * Function: delete
 *
 * Description: delete a node from heap and reheap down
 */

bool delete(struct tree** dataOut, struct tree** heap, int count) {

	if(count == 0)
		return false;

	*dataOut = heap[0];
	heap[0] = heap[count-1];

	reheapDown(heap, 0, count);

	return true;

}

/*
 * Function: reheapUp
 *
 * Description: move a node from the bottom of the heap up into its correct place
 */

void reheapUp(struct tree** heap, int childLoc) {

	if(childLoc == 0)
		return;

	if(heap[childLoc]->data < heap[p(childLoc)]->data) {

		struct tree* temp = heap[p(childLoc)];
		heap[p(childLoc)] = heap[childLoc];
		heap[childLoc] = temp;

		reheapUp(heap, p(childLoc));

	}

	return;

}	

/*
 * Function: reheapDown
 *
 * Description: move a node from the top of the heap down into its correct place
 */

void reheapDown(struct tree** heap, int root, int size) {

	int minIndex = root;
	
	if(l(root) < size) {

		if(r(root) < size) {
		
			if(heap[l(root)]->data < heap[r(root)]->data)
				minIndex = l(root);
			else 	
				minIndex = r(root);
		
		} else {

			minIndex = l(root);
		
		}

	}

	if(heap[minIndex]->data < heap[root]->data) {

		struct tree* temp = heap[root];
		heap[root] = heap[minIndex];
		heap[minIndex] = temp;
		
		reheapDown(heap, minIndex, size);
	}

	return;
}
