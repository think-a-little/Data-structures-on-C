#include <stdlib.h>
#include <stdio.h>
#include "BST.h"
#pragma comment(linker, "/STACK:996777217")

struct BST* init(INT_64 value) {
	struct BST* tree = (struct BST*)malloc(sizeof(struct BST));
	tree->left = NULL;
	tree->right = NULL;
	tree->value = value;
	return tree;
}

void add(struct BST** root, INT_64 value) {
	struct BST* temp = *root, *parent = NULL;
	int flag = 1;
	if (*root == NULL) {
		*root = init(value);
	}
	else {
		while (temp != NULL && flag == 1) {
			parent = temp;
			if (value < temp->value) {
				temp = temp->left;
			}
			else if (value > temp->value) {
				temp = temp->right;
			}
			else flag = 0;
		}
		if (flag == 1) {
			if (value < parent->value) {
				parent->left = init(value);
			}
			else if (value > parent->value) {
				parent->right = init(value);
			}
		}
	}
}

void remove_no(struct BST* parent, struct BST* temp, INT_64 value) {
	if (parent->left == temp) {
		parent->left = NULL;
	}
	else if (parent->right == temp) parent->right = NULL;
	free(temp);
}

void remove_l(struct BST* parent, struct BST* temp, INT_64 value) {
	if (parent->left == temp) {
		parent->left = temp->left;
	}
	else if (parent->right == temp) parent->right = temp->left;
	//else if (parent == temp) parent = temp->left;
	free(temp);
}

void remove_r(struct BST* parent, struct BST* temp, INT_64 value) {
	if (parent->left == temp) {
		parent->left = temp->right;
	}
	else if (parent->right == temp) parent->right = temp->right;
	free(temp);
}

void remove_all(struct BST* parent, struct BST* temp, INT_64 value) {
	struct BST* new_root = temp;
	parent = temp;
	temp = temp->right;
	while (temp->left != NULL) {
		parent = temp;
		temp = temp->left;
	}
	new_root->value = temp->value;
	if (temp->right == NULL) {
		if (parent->left == temp) {
			parent->left = temp->right;
		}
		else if (parent->right == temp) {
			parent->right = temp->right;
		}
	}
	else {
		if (parent->left == temp) {
			parent->left = temp->right;
		}
		else if (parent->right == temp) {
			parent->right = temp->right;
		}
	}
	free(temp);
}

struct BST* get(struct BST** root, INT_64 value) {
	struct BST* temp = *root, *find = NULL;
	if (*root != NULL) {
		while (temp != NULL) {
			if (value == temp->value) {
				find = temp;
				break;
			}
			if (value < temp->value) {
				temp = temp->left;
			}
			else if (value > temp->value) {
				temp = temp->right;
			}
		}
	}
	return find;
}

void find(struct BST** temp, struct BST** parent, INT_64 value) {
	if (*temp != NULL) {
		while (*temp != NULL) {
			if (value == (*temp)->value) {
				break;
			}
			*parent = *temp;
			if (value < (*temp)->value) {
				*temp = (*temp)->left;
			}
			else if (value > (*temp)->value) {
				*temp = (*temp)->right;
			}
		}
	}
}


int remove(struct BST** root, INT_64 value) {
	struct BST* temp = *root, *parent = *root;
	int flag = 0;
	find(&temp, &parent, value);
	if (temp != NULL) {
		flag = 1;
		if (temp->left == NULL && temp->right == NULL) {
			if (temp == *root) {
				free(*root);
				*root = NULL;
			}
			else remove_no(parent, temp, value);
		}
		else if (temp->left != NULL && temp->right != NULL) {
		remove_all(parent, temp, value);
		}
		else if (temp->left != NULL) {
			if (temp == *root) {
				*root = temp->left;
				free(temp);
			}
			else remove_l(parent, temp, value);
		}
		else if (temp->right != NULL) {
			if (temp == *root) {
				*root = temp->right;
				free(temp);
			}
			else remove_r(parent, temp, value);
		}
	}
	return flag;
}

void print(struct BST* tree, int level) {
	if (tree != NULL) {
		if (tree->right != NULL)
			print(tree->right, level + 1);
		for (int i = 0; i < level * 10; i++) {
			printf(" ");
		}
		printf("(%d)\n", tree->value);
		if (tree->left != NULL)
			print(tree->left, level + 1);
	}
}

void clear(struct BST* root) {
	if (root->left != NULL) {
		clear(root->left);
	}
	if (root->right != NULL) {
		clear(root->right);
	}
	free(root);
}

void number(struct BST* root, int &count) {
	if (root != NULL) {
		if (root->left != NULL) {
			count++;
			number(root->left, count);
		}
		if (root->right != NULL) {
			count++;
			number(root->right, count);
		}
	}
}




void add(struct BST** root, INT_64 value, int &step_add) {
	struct BST* temp = *root, * parent = NULL;
	int flag = 1;
	if (*root == NULL) {
		*root = init(value);
	}
	else {
		while (temp != NULL && flag == 1) {
			parent = temp;
			if (value < temp->value) {
				temp = temp->left;
			}
			else if (value > temp->value) {
				temp = temp->right;
			}
			else {
				flag = 0;
			}
			step_add++;
		}
		if (flag == 1) {
			if (value < parent->value) {
				parent->left = init(value);
			}
			else if (value > parent->value) {
				parent->right = init(value);
			}
		}
	}
}

void remove_no(struct BST* parent, struct BST* temp, INT_64 value, int& step_del) {
	if (parent->left == temp) {
		parent->left = NULL;
	}
	else if (parent->right == temp) parent->right = NULL;
	free(temp);
}

void remove_l(struct BST* parent, struct BST* temp, INT_64 value, int& step_del) {
	if (parent->left == temp) {
		parent->left = temp->left;
	}
	else if (parent->right == temp) parent->right = temp->left;
	//else if (parent == temp) parent = temp->left;
	free(temp);
}

void remove_r(struct BST* parent, struct BST* temp, INT_64 value, int& step_del) {
	if (parent->left == temp) {
		parent->left = temp->right;
	}
	else if (parent->right == temp) parent->right = temp->right;
	free(temp);
}

void remove_all(struct BST* parent, struct BST* temp, INT_64 value, int &step_del) {
	struct BST* new_root = temp;
	parent = temp;
	temp = temp->right;
	while (temp->left != NULL) {
		parent = temp;
		temp = temp->left;
		step_del++;
	}
	new_root->value = temp->value;
	if (temp->right == NULL) {
		if (parent->left == temp) {
			parent->left = temp->right;
		}
		else if (parent->right == temp) {
			parent->right = temp->right;
		}
	}
	else {
		if (parent->left == temp) {
			parent->left = temp->right;
		}
		else if (parent->right == temp) {
			parent->right = temp->right;
		}
	}
	free(temp);
}

struct BST* get(struct BST** root, INT_64 value, int &step_get) {
	struct BST* temp = *root, * find = NULL;
	if (*root != NULL) {
		while (temp != NULL) {
			if (value == temp->value) {
				find = temp;
				break;
			}
			if (value < temp->value) {
				temp = temp->left;
			}
			else if (value > temp->value) {
				temp = temp->right;
			}
			step_get++;
		}
	}
	return find;
}

void find(struct BST** temp, struct BST** parent, INT_64 value, int &step_del) {
	if (*temp != NULL) {
		while (*temp != NULL) {
			if (value == (*temp)->value) {
				break;
			}
			*parent = *temp;
			if (value < (*temp)->value) {
				*temp = (*temp)->left;
			}
			else if (value > (*temp)->value) {
				*temp = (*temp)->right;
			}
			step_del++;
		}
	}
}


int remove(struct BST** root, INT_64 value, int &step_del) {
	struct BST* temp = *root, * parent = *root;
	int flag = 0, step = 0;
	find(&temp, &parent, value, step_del);
	if (temp != NULL) {
		flag = 1;
		if (temp->left == NULL && temp->right == NULL) {
			if (temp == *root) {
				free(*root);
				*root = NULL;
			}
			else remove_no(parent, temp, value, step_del);
		}
		else if (temp->left != NULL && temp->right != NULL) {
			remove_all(parent, temp, value, step_del);
		}
		else if (temp->left != NULL) {
			if (temp == *root) {
				*root = temp->left;
				step_del++;
				free(temp);
			}
			else remove_l(parent, temp, value, step_del);
		}
		else if (temp->right != NULL) {
			if (temp == *root) {
				*root = temp->right;
				step_del++;
				free(temp);
			}
			else remove_r(parent, temp, value, step_del);
		}
	}
	return flag;
}