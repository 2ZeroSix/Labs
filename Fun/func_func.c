#include <stdio.h>


void *(*(func)())(void*, ...) {
	return (void* (*)(void*, ...))putchar;
}

int main() {
	void *(*(*infunc[10])())(void*, ...);//массив указателей на функции, которые работают без параметров и возвращают функции, которые принимают > 0 параметров и возвращают что угодно.
	infunc[4] = func;
	infunc[4]()((void*)'g');
	infunc[4]()((void*)'g');
	return 0;
}
