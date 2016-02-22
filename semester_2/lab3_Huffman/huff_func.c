#include "huff_func.h"


table_type_hf* file_table_hf(FILE* in) {
	table_counter_hf* c;
	table_type_hf* table = (table_type_hf*)calloc(table_width_hf, sizeof(table_type_hf));
	while((c = getc(in)) != EOF) {
		table[c]++;
	}
	return table;
}

queue_hf* push_ord_hf(queue_hf* queue, tree_hf* new) {
	if(!new) {
		return NULL;
	}
	if(queue) {
		tree_hf* prev = NULL;
		tree_hf* cur = queue;
		while(cur) {
			if (cur->count < new->count) {
				prev = cur;
				cur = cur->next;
			}
			else {
				prev->next = new;
				new->next = cur;
			}
		}
		if (!cur) {
			prev->next = new;
		}
	}
	else {
		queue = new;
	}
	return queue;
}

tree_hf* take_tree_ord_hf(queue_hf** queue) {
	if(queue && (queue*)) {
		tree_hf* tkd = (queue*)->root;
		queue_hf* tmp = queue*;
		(queue*) = (queue*)->next;
		free(tmp);
		return tkd;
	}
	else {
		return NULL;
	}
}

queue_hf* queue_from_table_hf(table_hf* table) {//, table_counter_hf* count) {
	if(table) {
		table_counter_hf i;
		queue_hf* queue = (queue_hf*)calloc(1, sizeof(queue_hf));
		// if (count) {
		// 	(count*) = 0;
		// }
		for (i = 0; i < table_width_hf; i++) {
			if(table[i]) {
				tree_hf* new = (tree_hf*)calloc(1, sizeof(tree_hf));
				new->code = i;
				new->count = table[i];
				queue = push_ord_hf(queue, new);
				// if (count) {
				// 	(count*)++;
				// }
			}
		}
	}
	else {
		return NULL;
	}
	return queue;
}

tree_hf* merge_tree_hf(tree_hf* root1, tree_hf* root2) {
	tree_hf* new = (tree_hf*)calloc(1, sizeof(tree_hf));
	new->count = (new->left = root1)->count + (new->right = root2)->count;
	return new;
}

tree_hf* tree_from_queue_hf(queue_hf* queue) {
	if(!queue) {
		return NULL;
	}
	while(queue->next){
		queue = push_ord_hf(queue, merge_tree_hf(take_tree_ord_hf(&queue),take_tree_ord_hf(&queue)));
	}
	return take_tree_ord_hf(&queue);
}

void depth_table_hf(tree* root, sym_code* table, sym_code cur) {
  if (!head || !table) {
    return;
  }
  if(root->count) {
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
		if (root->left) {
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

void write_code_hf(FILE* out, sym_code cur) {
	static sym_code_code_hf tmp;
	static sym_code_bts_hf pos;
	if (pos + cur.bts > sym_code_MAXbts_hf) {
		fwrite(&((tmp << ) + (cur.code &)), 1, sizeof(sym_code_code_hf), out);
		pos = 0;
	}
	else {
		tmp <<
	}
}

void write_tree_hf(FILE* out, tree_hf* root) {

}

void compress_file_hf(FILE* in, FILE* out, sym_code* table) {
	char c;
	while ((c = getc(in)) != EOF) {
		write_code_hf(table[c]);
	}
}

void complete_compress_hf(FILE*in, FILE* out){

}