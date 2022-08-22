#pragma once

struct List{
	struct List * next;
	int value;
};

struct List init(struct List *list);
void add(struct List** root, int value);
struct List* get(struct List* root, int value);
int remove(struct List** root, int value);
void clear(struct List* root);