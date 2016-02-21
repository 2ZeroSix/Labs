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
	if(!queue || !(queue*)){
		return NULL;
	}
	tree_hf* tkd = (queue*)->root;
	queue_hf* tmp = queue*;
	(queue*) = (queue*)->next;
	free(tmp);
	return tkd;
}

queue_hf* queue_from_table_hf(table_hf* table) {
	table_counter_hf i;
	queue_hf* queue = (queue_hf*)calloc(1, sizeof(queue_hf));
	for (i = 0; i < table_width_hf; i++) {
		if(table[i]) {
			tree_hf* new = (tree_hf*)calloc(1, sizeof(tree_hf));
			new->code = i;
			new->count = table[i];
			queue = push_ord_hf(queue, new);
		}
	}
	return queue;
}

tree_hf* merge_tree_hf(tree_hf* root1, tree_hf* root2) {
	tree_hf* new = (tree_hf*)calloc(1, sizeof(tree_hf));
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

long long* table_from_tree_hf() {
	long long* table = (long long*)calloc()
}

void write_tree_hf(FILE* out, tree_hf* root) {

}

void compress_file_hf(FILE* in, FILE* out, ) {

}

