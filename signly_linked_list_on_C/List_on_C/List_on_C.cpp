#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() {
	struct List* list = NULL, *node = NULL;
	add(&list, 1);
	add(&list, 2);
	add(&list, 3);
	node = list;
	for (int i = 3; i <= 4; i++) {
		node = get(list, i);
		if (node != NULL) {
			printf("%d ", node->value);
		}
	}
	remove(&list, 3);
	clear(list);
}
