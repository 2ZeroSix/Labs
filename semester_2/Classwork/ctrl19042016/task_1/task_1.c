#include <stdio.h>
#include <stdlib.h>
#define sym_code_MAXbts_hf 64 // максимальное кол-во значимых бит
#define sym_code_code_hf unsigned long long // тип для кода символа
#define sym_code_bts_hf unsigned char // тип для хранения кол-ва значимых бит

typedef struct _tree_hf{
  unsigned char code;
  struct _tree_hf* left;
  struct _tree_hf* right;
}tree_hf;

typedef struct _sym_code {
  sym_code_code_hf code; // код после сжатия
  sym_code_bts_hf bts; // кол-во значимых бит
}sym_code;

char isleaf_hf(tree_hf* root) {
	if(root && (root->left || root->right)) {
		return 0;
	}
	else {
		return 1;
	}
}

tree_hf* tree_from_file_hf(FILE* in) {
	tree_hf* root;
	if(getc(in) == '1') {
		root = (tree_hf*)calloc(1, sizeof(tree_hf));
		root->code = getc(in);
	}
	else {
		root = (tree_hf*)calloc(1, sizeof(tree_hf));
		root->left = tree_from_file_hf(in);
		root->right = tree_from_file_hf(in);
	}
	return root;
}

void depth_table_hf(tree_hf* root, sym_code* table, sym_code cur) {
  if (!root || !table) {
    return;
  }
  if(isleaf_hf(root)) {
  	table[root->code] = cur;
  }
  cur.code = cur.code << 1;
  cur.bts++;
  depth_table_hf(root->left, table, cur);
  cur.code++;
  depth_table_hf(root->right, table, cur);
}

sym_code* table_from_tree_hf(tree_hf* root) {
	if (root) {
		sym_code* table = (sym_code*)calloc(256, sizeof(sym_code));
		sym_code cur = {0, 0};
		if (!isleaf_hf(root)) {
			depth_table_hf(root, table, cur);
		}
		else {
			cur.code = 1;
			cur.bts = 1;
			table[root->code] = cur;
		}
		return table;
	}
	else {
		return NULL;
	}
}


int main() {
	tree_hf* root = tree_from_file_hf(stdin);
	sym_code* table = table_from_tree_hf(root);
	int i;
	for (i = 0; i < 256; i++) {
		if(table[i].bts) {
			int j;
			printf("%c - ", i);
			for (j = table[i].bts; j > 0; j--) {
				printf("%d", (table[i].code >> (j - 1)) & 1);
			}
			printf("\n");
		}
	}
	return 1;
}
