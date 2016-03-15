#include <stdio.h>
#include <stdlib.h>

typedef struct _tree{
  int value;
  struct _tree* left;
  struct _tree* right;
}tree;

tree* push_in_tree(tree* root, int element){
  tree* new = (tree*)calloc(1, sizeof(tree));
  new->value = element;
  if (root) {
    tree* cur = root;
    char go = 1;
    while(go) {
      if (cur->value > element) {
        if (cur->left) {
          cur = cur->left;
        }
        else {
          cur->left = new;
          go = 0;
        }
      }
      else {
        if (cur->right) {
          cur = cur->right;
        }
        else {
          cur->right = new;
          go = 0;
        }
      }
    }
  }
  else {
    root = new;
  }
  return root;
}

void depth_print_inf(FILE* output, tree* root) {
  if (!root) {
    return;
  }
  depth_print_inf(output, root->left);
  fprintf(output, "%d ", root->value);
  depth_print_inf(output, root->right);
}

void depth_free(tree* root) {
  if (!root) {
    return;
  }
  depth_free(root->left);
  depth_free(root->right);
  free(root);
}

void readtree(FILE* input, tree** root) {
  int numb;
  while(fscanf(input, "%d", &numb) > 0) {
    *root = push_in_tree(*root, numb);
  }
}

void del_leaf(tree** root, int val) {
  if(!(root && *root)) {
    return;
  }
  if((*root)->value > val) {
    del_leaf(&((*root)->left), val);
  }
  else if((*root)->value < val) {
    del_leaf(&((*root)->right), val);
  }
  else {
    if((*root)->left && (*root)->right) {
      tree* cur = (*root)->right;
      tree* tmp = (*root);
      tree* prev = NULL;
      while(cur->left){
        prev = cur;
        cur = cur->left;
      }
      if(prev) {
        prev->left = cur->right;
        cur->left = (*root)->left;
        cur->right = (*root)->right;
        (*root) = cur;
      }
      else {
        cur->left = (*root)->left;
        (*root) = cur;
      }
      free(tmp);
    }
    else if((*root)->left) {
      tree* tmp = (*root);
      free(tmp);
      (*root) = (*root)->left;
    }
    else if((*root)->right) {
      tree* tmp = (*root);
      free(tmp);
      (*root) = (*root)->right;
    }
    else {
      tree* tmp = (*root);
      free(tmp);
      *root = NULL;
    }
  }
}

int main(int argc, char** argv) {
	if (argc > 1) {
		FILE* in;
		tree* root = NULL;
		if (in = fopen(argv[1], "r")) {
			int i;
			readtree(in, &root);
			for(i = 2; i < argc; i++){
				del_leaf(&root, atoi(argv[i]));
			}
			depth_print_inf(stdout, root);
      depth_free(root);
		}
	}
}