#include "huff_func.h"


char isleaf_hf(tree_hf* root) {
	if(root && root->left && root->right) {
		return 1;
	}
	else {
		return 0;
	}
} 

table_type_hf* file_table_hf(FILE* in) {
	char c;
	table_type_hf* table = (table_type_hf*)calloc(table_width_hf, sizeof(table_type_hf));
	while((c = getc(in)) != EOF) {
		table[(unsigned char)c]++;
	}
	return table;
}

queue_hf* push_ord_hf(queue_hf* queue, tree_hf* new) {
	if(new) {
		queue_hf* tmp = (queue_hf*)calloc(1, sizeof(queue_hf));
		if(queue) {
			queue_hf* prev = NULL;
			queue_hf* cur = queue;
			tmp->root = new;
			char go = 1;
			while(go) {
				if (cur) {
					if (cur->root->count < new->count) {
						prev = cur;
						cur = cur->next;
					}
					else {
						if(prev) {
							prev->next = tmp;
						}
						else {
							queue = tmp;
						}
						tmp->next = cur;
						
						go = 0;
					}
				}
				else {
					prev->next = tmp;
					go = 0;
				}
			}
		}
		else {
			queue = tmp;
		}
	}
	else {
		return NULL;
	}
	return queue;
}

tree_hf* take_tree_ord_hf(queue_hf** queue) {
	if(queue && (*queue)) {
		tree_hf* tkd = (*queue)->root;
		queue_hf* tmp = *queue;
		(*queue) = (*queue)->next;
		free(tmp);
		return tkd;
	}
	else {
		return NULL;
	}
}

queue_hf* queue_from_table_hf(table_type_hf* table) {//, table_counter_hf* count) {
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
		return queue;
	}
	else {
		return NULL;
	}
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

void depth_table_hf(tree_hf* root, sym_code* table, sym_code cur) {
  if (!root || !table) {
    return;
  }
  if(!isleaf_hf(root)) {
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
		if (isleaf_hf(root)) {
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
	if (cur.bts) {
		if (pos + cur.bts >= sym_code_MAXbts_hf) {
			tmp = ((tmp << (sym_code_MAXbts_hf - pos)) + (cur.code >> (cur.bts - sym_code_MAXbts_hf + pos)));
			fwrite(&tmp, 1, sizeof(sym_code_code_hf), out);
			cur.bts -= sym_code_MAXbts_hf - pos;
			cur.code = cur.code % (2^(cur.bts - sym_code_MAXbts_hf + pos));
			pos = 0;
		}
		else {
			tmp = (tmp << cur.bts) + cur.code;
			pos += cur.bts;
		}
	}
	else {
		if (pos) {
			tmp = (tmp << (sym_code_MAXbts_hf - pos));
			fwrite(&tmp, 1, sizeof(sym_code_code_hf), out);
		}
	}
}

void write_count_hf(FILE* out, table_type_hf* table_in, sym_code* table_out) {
	unsigned long long count = 0;
	table_counter_hf i;
	for (i = 0; i < table_width_hf; i++) {
		count+=table_in[i] * (table_out[i]).bts;
	}
	fwrite(&count, 1, sizeof(unsigned long long), out);
}

void write_tree_hf(FILE* out, tree_hf* root) {
	if(isleaf_hf(root)){
		static sym_code tmp = {0,1};
		write_code_hf(out, tmp);
		write_tree_hf(out, root->left);
		write_tree_hf(out, root->right);
	}
	else {
		static sym_code tmp = {1,1};
		write_code_hf(out, tmp);
	}
}

void compress_file_hf(FILE* in, FILE* out, sym_code* table) {
	char c;
	sym_code end = {0,0};
	while ((c = getc(in)) != EOF) {
		write_code_hf(out, table[(unsigned char)c]);
	}
	write_code_hf(out, end);
}

void complete_compress_hf(FILE*in, FILE* out){
	table_type_hf* tmp_table_in = file_table_hf(in);
	queue_hf* tmp_queue = queue_from_table_hf(tmp_table_in);
	tree_hf* tmp_tree = tree_from_queue_hf(tmp_queue);
	sym_code* tmp_table_out = table_from_tree_hf(tmp_tree);
	// free_queue_hf(tmp_queue); // сделать
	write_count_hf(out, tmp_table_in, tmp_table_out);
	free(tmp_table_in);
	write_tree_hf(out, tmp_tree);
	// depth_tree_free_hf(tmp_tree); //сделать
	compress_file_hf(in, out, tmp_table_out);
	free(tmp_table_out);
	return;
}