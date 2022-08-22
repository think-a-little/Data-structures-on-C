#include "List.h"
#include <stdlib.h>

struct List* init(int value) {
	struct List *list = (struct List*)malloc(sizeof(struct List));
	list->value = value;
	list->next = NULL;
	return list;
}

void add(struct List** root, int value) {
	struct List* temp = *root, *p;
	if (*root == NULL) {
		*root = init(value);
	}
	else {
		p = init(value);
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = p;
	}
}

struct List* get(struct List* root, int value) {
	struct List* temp = root, *ret;
	while (temp != NULL && temp->value != value) {
		temp = temp->next;
	}
	if (temp != NULL && temp->value == value) {
		ret = temp;
	}
	else {
		ret = NULL;
	}
	return ret;
}

int remove(struct List** root, int value) {
	struct List* list = *root, *prev = NULL;
	int ret = 0;
	if (root != NULL) {
		if (list->value == value) {
			list = (*root)->next;
			free(*root);
			*root = list;
			ret = 1;
		}
		else {
			while (list != NULL && list->value != value) {
				prev = list;
				list = list->next;
			}
			if (list != NULL && list->value == value) {
				prev->next = list->next;
				free(list);
				ret = 1;
			}
		}
	}
	return ret;
}

void clear(struct List* root) {
	if (root->next != NULL) {
		clear(root->next);
	}
	free(root);
}