#define _CRT_SECURE_NO_WARNINGS
#include "avl_func.h"

int main() {
	avl_tree* root = NULL;
	int N, elem;
	int i;
	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		scanf("%d", &elem);
		root = push_in_avl(root, elem);
	}
	printf("%d", (root) ? root->height : 0);
	depth_free_avl(root);
	return 0;
}