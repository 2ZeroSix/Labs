#include "binary_heap.h"
#include <stdio.h>

int intcmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

int main() {
	heap* bheap = make_heap(100, sizeof(int), intcmp);
	size_t i;
	for (i = 0; i < 100; i++) {
		insert(bheap, &i);
	}
	for (i = 0; i < 100; i++) {
		printf("%d ", ((int*)bheap->array)[i]);
	}
	printf("\n");
	i = -1;
	update_by_index(bheap, 98, &i);
	for (i = 0; i < 100; i++) {
		printf("%d ", ((int*)bheap->array)[i]);
	}
	printf("\n");
	for (i = 0; i < 99; i++) {
		printf("%d ", *(int*)get_max(bheap));
	}
	printf("\n");
	printf("%s\n", isEmpty(bheap) ? "empty" : "not empty");
	i = 9999999;
	update_by_index(bheap, 98, &i);
	printf("%d\n", *(int*)get_max(bheap));
	return 0;
}