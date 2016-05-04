#ifndef _BINARY_HEAP_
	#define _BINARY_HEAP_
	typedef _heap {
		void* array; // указатель на область памяти выделенную под кучу
		size_t* index; // текущее расположение элементов (в позиции n хранится положение n-ного добавленного элемента)
		size_t count; // текущее кол-во элементов в куче
		size_t countMAX; // размер памяти выделенной под кучу
		size_t size; // размер одного элемента
		int (*comparator)(const void*, const void*); // функция сравнения элементов кучи
	}heap;

	heap* make_heap(size_t count, size_t size, int (*comparator)(const void*, const void*));

	heap* build_heap(void* array, size_t count, size_t size, int (*comparator)(const void*, const void*));
	
	void insert(heap* bheap, void* new);

	void* get_max(heap* bheap);

	void* extract_max(heap* bheap);

	void* increase_key(heap* bheap, size_t);

	char isEmpty(heap* bheap);

#endif