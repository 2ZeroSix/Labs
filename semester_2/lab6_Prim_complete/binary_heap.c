#include "binary_heap.h"

 
void swap(void *a, void *b, size_t size) {
  void* tmp;
  tmp = malloc(size);
  memcpy(tmp, a, size);
  memcpy(a, b, size);
  memcpy(b, tmp, size);
  free(tmp);
}

void swap_low_mem(void *a, void *b, size_t size) {
    char tmp;
    size_t i;
    for (i = 0; i < size; i++) {
        tmp = *((char*) b + i);
        *((char*) b + i) = *((char*) a + i);
        *((char*) a + i) = tmp;
    }
}

heap* make_heap(size_t countMAX, size_t size, int (*comparator)(const void*, const void*)) {
	if(countMAX && size) {
		heap* bheap = (heap*)calloc(heap, 1);
		bheap->array = calloc(countMAX, size);
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
  size_t leftChild;
  size_t rightChild;
  size_t largestChild;
  size_t headSize = bh->countMAX;
  for (; ; ) {
    leftChild = 2 * i + 1;
    rightChild = 2 * i + 2;
    largestChild = i;
    int (*comparator)(const void*, const void*) = bheap->comparator;
    if (leftChild < heapSize && comparator((char*)list + leftChild, (char*)list + largestChild)) {
      largestChild = leftChild;
    }
    if (rightChild < heapSize && comparator((char*)list + rightChild, (char*)list + largestChild)) {
      largestChild = rightChild;
    }
    if (largestChild == i) {
      break;
    }
    swap((char*)list + i, (char*)list + largestChild)
    i = largestChild;
  }
}

heap* build_heap(void* array, size_t count, size_t size) {
	heap* bheap = make_heapheap(count, size);
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
	size_t cur = bheap->count;
	size_t parent = (cur - 1) / 2;
	size_t size = bheap->size;
	void* array = bheap->array;;
	int (*comparator)(const void*, const void*) = bheap->comparator;
	if(cur >= bheap->countMAX) {
		return 0;
	}
	memcpy((char*)array + cur*size, new, size);
	while(cur && (comparator((char*)array + (cur*size), (char*)array + (parent*size)) > 0)) {
		swap((char*)array + cur*size, (char*)array + (parent*size), size);
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
