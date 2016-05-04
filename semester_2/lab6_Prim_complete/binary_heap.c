#include "binary_heap.h"

void swap_heap(heap* bheap, size_t a, size_t b) {
	swap((char*)(bheap->array) + a*(bheap->size), (char*)(bheap->array) + b*(bheap->size), bheap->size);
	swap(&index[a], &index[b], sizeof(size_t));
}

void swap(void *a, void *b, size_t size) {
  void* tmp;
  tmp = malloc(size);
  memcpy(tmp, a, size);
  memcpy(a, b, size);
  memcpy(b, tmp, size);
  free(tmp);
}

void swap_low_mem(void *a, void *b, size_t size) {
  size_t i;
  for (i = 0; i < size; i++) {
	  char tmp;
    tmp = *((char*) a + i);
    *((char*) a + i) = *((char*) b + i);
    *((char*) b + i) = tmp;
  }
}

int compare(heap* bheap, size_t a, size_t b) {
	return comparator((char*)bheap->array + a*bheap->size, (char*)bheap->array + b*bheap->size);
}

heap* make_heap(size_t countMAX, size_t size, int (*comparator)(const void*, const void*)) {
	if(countMAX && size && comparator) {
		heap* bheap = (heap*)calloc(heap, 1);
		bheap->array = calloc(countMAX, size);
		bheap->index = calloc(countMAX, sizeof(size_t));
		bheap->size = size;
		bheap->countMAX = countMAX;
		bheap->comparator = comparator;
		return bheap;
	}
	else {
		return NULL;
	}
}

void heapify(heap* bheap, size_t i) {
  for (; ; ) {
	  size_t heapSize = bh->count;
	  size_t leftChild = 2 * i + 1;
	  size_t rightChild = 2 * i + 2;
	  size_t largestChild = i;
    
    if (leftChild < heapSize && (compare(bheap, leftChild, largestChild)) > 0) {
      largestChild = leftChild;
    }
    if (rightChild < heapSize && (compare(bheap, rightChild, largestChild)) > 0) {
      largestChild = rightChild;
    }
    if (largestChild == i) {
      break;
    }
    swap_heap(bheap, i, largestChild);
    i = largestChild;
  }
}

heap* build_heap(void* array, size_t count, size_t size, int (*comparator)(const void*, const void*)) {
	heap* bheap = make_heapheap(count, size, comparator);
	if(bheap) {
		bheap->array = array;
		size_t i;
		for(i = count / 2; i > 0; i--)
			heapify(bheap, i);
		heapify(bheap, i);
	}
	return bheap;
}

char insert(heap* bheap, void* new) {
	void* array = bheap->array;;
	size_t cur = bheap->count;
	size_t size = bheap->size;
	size_t parent = (cur - 1) / 2;

	if(cur >= bheap->countMAX) {
		return 0;
	}
	memcpy((char*)array + cur*size, new, size);
	while(cur && (compare(bheap, cur, parent) > 0)) {
		swap_heap(bheap, cur, parent);
		cur = parent;
		parent = (cur - 1) / 2;
	}
	bheap->count++;
	return 1;
}

void* get_max(heap* bheap) {
	swap(bheap->array, (char*)(bheap->array) + bheap->count, bheap->size);
	bheap->count--;
	return (char*)(bheap->array) + (bheap->count + 1);
}

void* extract_max(heap* bheap) {
	if (isEmpty(bheap)) {
		return NULL;
	}
	void* result = calloc(bheap->size);
	memcpy(result, bheap->array, bheap->size);
	memcpy(bheap->array, (char*)(bheap->array) + bheap->count, bheap->size);
	bheap->count--;
	heapify(bheap, 0);
	return result;
}

char isEmpty(heap* bheap) {
	return bheap->count;
}
