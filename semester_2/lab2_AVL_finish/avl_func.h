#ifndef _AVL_FUNC_H
#define _AVL_FUNC_H

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
unsigned char maxuchar(unsigned char a, unsigned char b);

/**
 * определение высоты дерева по высотам его поддеревьев
 * @param  root ненулевой указатель на дерево
 * @return      высота дерева (верна только если высоты поддеревьев верны)
 */
unsigned char height_avl(avl_tree* root);

 /**
 * малое правое вращение
 * @param  root ненулевой указатель на дерево
 * @return      указатель на дерево после вращения
 */
avl_tree* avl_right (avl_tree* root);

/**
 * малое левое вращение
 * @param  root ненулевой указатель на дерево
 * @return      указатель на дерево после вращения
 */
avl_tree* avl_left (avl_tree* root);

/**
 * Большое правое вращение
 * @param  root ненулевой указатель на дерево
 * @return      указатель на дерево после вращения
 */
avl_tree* avl_big_right (avl_tree* root);

/**
 * Большое левое вращение
 * @param  root ненулевой указатель на дерево
 * @return      указатель на дерево после вращения
 */
avl_tree* avl_big_left (avl_tree* root);

/**
 * Определение необходимого вращения, вращение и изменение высоты на корректное
 * @param  root ненулевой указатель на дерево
 * @return      указатель на дерево после вращения
 */
avl_tree* avl_rotation (avl_tree* root);

/**
 * добавление элемента в АВЛ дерево
 * @param  root    указатель на дерево
 * @param  element элемент для вставки
 * @return         дерево после вставки
 */
avl_tree* push_in_avl (avl_tree* root, type_tree element);

/**
 * очистка памяти из под дерева рекурсивным проходом в глубину
 * @param root указатель на дерево
 */
void depth_free_avl(avl_tree* root);

#endif