#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define type_tree int // тип значений элементов дерева
typedef struct _avl_tree{
	unsigned char height;
	type_tree val;
	struct _avl_tree* left;
	struct _avl_tree* right;
}avl_tree;

/**
 * наибольший из данных элементов unsigned char
 * @param  a
 * @param  b
 * @return наибольший
 * */
unsigned char maxuchar(unsigned char a, unsigned char b) {
	return (a > b) ? a : b;
}

/**
 * определение высоты дерева по высотам его поддеревьев
 * @param  root ненулевой указатель на дерево
 * @return      высота дерева (верна только если высоты поддеревьев верны)
 */
unsigned char height_avl(avl_tree* root) {
	return maxuchar(((root->left) ? root->left->height : 0), ((root->right) ? root->right->height : 0)) + 1;
}

/**
 * малое правое вращение
 * @param  root ненулевой указатель на дерево
 * @return      указатель на дерево после вращения
 */
avl_tree* right (avl_tree* root) {
	avl_tree* b = root->left;
	root->left = b->right;
	b->right = root;
	root->height = height_avl(root);
	b->height = height_avl(b);
	return b;
}

/**
 * малое левое вращение
 * @param  root ненулевой указатель на дерево
 * @return      указатель на дерево после вращения
 */
avl_tree* left (avl_tree* root) {
	avl_tree* b = root->right;
	root->right = b->left;
	b->left = root;
	root->height = height_avl(root);
	b->height = height_avl(b);
	return b;
}

/**
 * Большое правое вращение
 * @param  root ненулевой указатель на дерево
 * @return      указатель на дерево после вращения
 */
avl_tree* big_right (avl_tree* root) {
	avl_tree* b = root->left;
	root->left = left(b);
	return right(root);
}

/**
 * Большое левое вращение
 * @param  root ненулевой указатель на дерево
 * @return      указатель на дерево после вращения
 */
avl_tree* big_left (avl_tree* root) {
	avl_tree* b = root->right;
	root->right = right(b);
	return left(root);
}

/**
 * Определение необходимого вращения, вращение и изменение высоты на корректное
 * @param  root ненулевой указатель на дерево
 * @return      указатель на дерево после вращения
 */
avl_tree* avl_rotation (avl_tree* root) {
	switch(((root->left) ? root->left->height : 0) - ((root->right) ? root->right->height : 0)) {
		case 2:
			if (((root->left->left) ? root->left->left->height : 0) >= ((root->left->right) ? root->left->right->height : 0)) {
				root = right(root);
			}
			else {
				root = big_right(root);
			}
			break;
		case -2:
			if(((root->right->right) ? root->right->right->height : 0) >= ((root->right->left) ? root->right->left->height : 0)) {
				root = left(root);
			}
			else {
				root = big_left(root);
			}
			break;
		default:
			root->height = height_avl(root);	
			break;
	}
	return root;
}

/**
 * добавление элемента в АВЛ дерево
 * @param  root    указатель на дерево
 * @param  element элемент для вставки
 * @return         дерево после вставки
 */
avl_tree* push_in_avl (avl_tree* root, type_tree element) {
	if (root) {
		if (root->val > element) {
			root->left = push_in_avl(root->left, element);
		}
		else {
			root->right = push_in_avl(root->right, element);
		}
	}
	else {
		avl_tree* new = (avl_tree*)calloc(1, sizeof(avl_tree));
		new->val = element;
		new->height = 1;
		root = new;
	}
	return avl_rotation(root);
}

/**
 * очистка памяти из под дерева рекурсивным проходом в глубину
 * @param root указатель на дерево
 */
void depth_free_avl(avl_tree* root) {
	if (root) {
		avl_tree* left = root->left;
		avl_tree* right = root->right;
		free(root);
		depth_free_avl(left);
		depth_free_avl(right);
	}
}

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