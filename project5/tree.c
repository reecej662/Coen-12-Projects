#include "tree.h"

/*
 * Function: createTree
 *
 * Description: return a pointer to a new tree with the specified left and right subtrees and data for its root 
 *
 * Complexity: O(1)
 */

struct tree *createTree(int data, struct tree *left, struct tree *right) {

	// allocate space for the new tree
	struct tree* newTree = malloc(sizeof(struct tree));
	
	// set the values for the tree
	newTree->parent = NULL;
	newTree->data = data;
	newTree->left = left;
	newTree->right = right; 

	// if the children aren't null, have them point to the new root
	if(left != NULL)
		left->parent = newTree;
	if(right != NULL)
		right->parent = newTree;

	return newTree;
}

/*
 * Function: destroyTree
 *
 * Description: recursively deallocate memory for the entire subtree pointed to by root
 * 
 * Complexity: O(n) 
 */

void destroyTree(struct tree *root) {

	// base case
	if(root == NULL)
		return;

	// deallocate both the left and right subchildren
	if(root->left != NULL) {
		destroyTree(root->left);
	}

	if(root->right != NULL) {
		destroyTree(root->right);
	}

	free(root);

}

/*
 * Function: getData
 *
 * Description: returns the data of the inputed node
 *
 * Complexity: O(1)
 */

int getData(struct tree *root) {

	assert(root != NULL);

	return root->data;

}

/*
 * Function: getLeft
 *
 * Description: returns a pointer to the left child of the inputted node 
 *
 * Complexity: O(1)
 */

struct tree *getLeft(struct tree *root) {

	assert(root != NULL);

	return root->left;
	
}

/*
 * Function: getRight
 *
 * Description: returns a pointer to the right child of the inputted node
 *
 * Complexity: O(1)
 */

struct tree *getRight(struct tree *root) {

	assert(root != NULL);

	return root->right;

}

/*
 * Function: getParent
 *
 * Description: returns the parent of the inputted node
 *
 * Complexity: O(1)
 */

struct tree *getParent(struct tree *root) {

	assert(root != NULL);

	return root->parent;

}

/*
 * Function: setLeft
 *
 * Description: updates the left subtree of root with the inputted tree
 *
 * Complexity: O(1)
 */

void setLeft(struct tree *root, struct tree *left) {

	assert(root != NULL && left != NULL);
	
	root->left = left;	
	left->parent = root;
}

/*
 * Function: createTree
 *
 * Description: updates the right subtree of root with the inputted tree
 *
 * Complexity: 
 */

void setRight(struct tree *root, struct tree *right) {

	assert(root != NULL && right != NULL);

	root->right = right;
	right->parent = root;

}

