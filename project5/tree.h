#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

struct tree {
	int data;
	struct tree* parent;
	struct tree* left;
	struct tree* right;
};

struct tree *createTree(int data, struct tree *left, struct tree *right);

void destroyTree(struct tree *root);

int getData(struct tree *root);

struct tree *getLeft(struct tree *root);

struct tree *getRight(struct tree *root);

struct tree *getParent(struct tree *root);

void setLeft(struct tree *root, struct tree *left);

void setRight(struct tree *root, struct tree *right);

#endif
