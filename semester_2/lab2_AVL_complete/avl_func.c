#define _CRT_SECURE_NO_WARNINGS
#include "avl_func.h"

unsigned char maxuchar(unsigned char a, unsigned char b) {
	return (a > b) ? a : b;
}

unsigned char height_avl(avl_tree* root) {
	return maxuchar(((root->left) ? root->left->height : 0), ((root->right) ? root->right->height : 0)) + 1;
}

avl_tree* avl_right (avl_tree* root) {
	avl_tree* b = root->left;
	root->left = b->right;
	b->right = root;
	root->height = height_avl(root);
	b->height = height_avl(b);
	return b;
}

avl_tree* avl_left (avl_tree* root) {
	avl_tree* b = root->right;
	root->right = b->left;
	b->left = root;
	root->height = height_avl(root);
	b->height = height_avl(b);
	return b;
}

avl_tree* avl_big_right (avl_tree* root) {
	avl_tree* b = root->left;
	root->left = avl_left(b);
	return avl_right(root);
}

avl_tree* avl_big_left (avl_tree* root) {
	avl_tree* b = root->right;
	root->right = avl_right(b);
	return avl_left(root);
}

avl_tree* avl_rotation (avl_tree* root) {
	switch(((root->left) ? root->left->height : 0) - ((root->right) ? root->right->height : 0)) {
		case 2:
			if (((root->left->left) ? root->left->left->height : 0) >= ((root->left->right) ? root->left->right->height : 0)) {
				root = avl_right(root);
			}
			else {
				root = avl_big_right(root);
			}
			break;
		case -2:
			if(((root->right->right) ? root->right->right->height : 0) >= ((root->right->left) ? root->right->left->height : 0)) {
				root = avl_left(root);
			}
			else {
				root = avl_big_left(root);
			}
			break;
		default:
			root->height = height_avl(root);	
			break;
	}
	return root;
}

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

void depth_free_avl(avl_tree* root) {
	if (root) {
		avl_tree* left = root->left;
		avl_tree* right = root->right;
		free(root);
		depth_free_avl(left);
		depth_free_avl(right);
	}
}