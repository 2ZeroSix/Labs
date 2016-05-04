#include "binary_heap.h"

#if  _BINARY_HEAP_LOW_MEM_
void swap(void *a, void *b, size_t size) {
  size_t i;
  for (i = 0; i < size; i++) {
	  char tmp;
    tmp = *((char*) a + i);
    *((char*) a + i) = *((char*) b + i);
    *((char*) b + i) = tmp;
  }
}
#else
void swap(void *a, void *b, size_t size) {
  void* tmp;
  tmp = malloc(size);
  memcpy(tmp, a, size);
  memcpy(a, b, size);
  memcpy(b, tmp, size);
  free(tmp);
}
#endif

void swap_heap(heap* bheap, size_t a, size_t b) {
	swap((char*)(bheap->array) + a*(bheap->size), (char*)(bheap->array) + b*(bheap->size), bheap->size);
	swap(&index[a], &index[b], sizeof(size_t));
}

int compare(heap* bheap, size_t a, size_t b) {
	return comparator((char*)bheap->array + a*bheap->size, (char*)bheap->array + b*bheap->size);
}

heap* make_heap(size_t countMAX, size_t size, int (*comparator)(const void*, const void*)) {
	if(countMAX && size && comparator) {
		heap* bheap = (heap*)calloc(1, sizeof(heap));
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

heap* build_heap(void* array, size_t count, size_t countMAX, size_t size, int (*comparator)(const void*, const void*)) {
	if (array && count && countMAX && size && comparator) {
		size_t i;
		heap* bheap = (heap*)calloc(1, sizeof(heap));
		bheap->array = array;
		bheap->index = malloc(countMAX*sizeof(size_t));
		for(i = 0; i < count; i++) {
			bheap->index[i] = i;
		}	
		bheap->size = size;
		bheap->count = count;
		bheap->countMAX = countMAX;
		bheap->comparator = comparator;
		
		for(i = count / 2; i > 0; i--)
			heapify(bheap, i);
		heapify(bheap, i);
		return bheap;
	}
	return NULL;
}

char insert(heap* bheap, void* new) {
	void* array = bheap->array;;
	size_t cur = bheap->count;
	size_t size = bheap->size;
	size_t parent = (cur - 1) / 2;
	if(cur >= bheap->countMAX) {
		return 0;
	}
	bheap->index[bheap->count] = bheap->count;
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
	if (isEmpty(bheap)) {
		return NULL;
	}
	swap_heap(bheap, 0, bheap->count);
	bheap->count--;
	heapify(bheap, 0);
	return (char*)(bheap->array) + (bheap->count * bheap->size);
}

void* extract_max(heap* bheap) {
	if (isEmpty(bheap)) {
		return NULL;
	}
	void* result = malloc(bheap->size);
	memcpy(result, bheap->array, bheap->size);
	swap_heap(bheap, 0, bheap->count);
	bheap->count--;
	heapify(bheap, 0);
	return result;
}

char isEmpty(heap* bheap) {
	return ((bheap->count) ? 0 : 1);
}

void update_by_index(heap* bheap, size_t id, void* upd) {
	void* array = bheap->array;
	size_t cur = bheap->index[id];
	size_t size = bheap->size;
	if (bheap->comparator(((char*)array + (cur * size)), (upd), (size))) {
		memcpy(((char*)array + (cur * size)), (upd), (size));
		heapify(bheap, cur);
	}
	else {
		memcpy(((char*)array + (index[id] * size)), (upd), (size));
		//TODO дописать поднятие элемента вверх
		while(cur > 0	)
	}
}

void* 
