#pragma once
#pragma comment(linker, "/STACK:996777217")
typedef unsigned long long INT_64;

struct BST {
	BST* left;
	BST* right;
	INT_64 value;
};

struct BST* init(INT_64 value);
void add(struct BST** root, INT_64 value);
struct BST* get(struct BST** root, INT_64 value);
int remove(struct BST** root, INT_64 value);
void print(struct BST* tree, int level = 0);
void clear(struct BST* root);

void number(struct BST* root, int &count);

void add(struct BST** root, INT_64 value, int &step_add);
struct BST* get(struct BST** root, INT_64 value, int &step_get);
int remove(struct BST** root, INT_64 value, int &step_del);