#include "huff_func.h"


char isleaf_hf(tree_hf* root) {
	if(root && root->left && root->right) {
		return 0;
	}
	else {
		return 1;
	}
} 

table_type_hf* file_table_hf(FILE* in) {
	int c;
	table_type_hf* table = (table_type_hf*)calloc(table_width_hf, sizeof(table_type_hf));
	while((c = getc(in)) != EOF) {
		table[(unsigned char)c]++;
	}
	return table;
}

queue_hf* push_ord_hf(queue_hf* queue, tree_hf* new) {
	if(new) {
		queue_hf* tmp = (queue_hf*)calloc(1, sizeof(queue_hf));
		tmp->root = new;
		if(queue) {
			queue_hf* prev = NULL;
			queue_hf* cur = queue;
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

queue_hf* queue_from_table_hf(table_type_hf* table) {
	if(table) {
		int i;
		queue_hf* queue = NULL;
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

void write_code_hf(FILE* out, sym_code cur) {
	static sym_code_code_hf tmp = 0;
	static sym_code_bts_hf pos = 0;
	if (cur.bts) {
		if (pos + cur.bts >= sym_code_MAXbts_hf) {
			tmp = ((tmp << (sym_code_MAXbts_hf - pos)) + (cur.code >> (cur.bts - sym_code_MAXbts_hf + pos)));
			fwrite(&tmp, 1, sizeof(sym_code_code_hf), out);
			// printf("1: tmp: %llu; pos: %u; cur.code: %llu; cur.bts: %u\t", tmp, pos, cur.code, cur.bts);
			cur.bts -= sym_code_MAXbts_hf - pos;
			// printf("2: tmp: %llu; pos: %u; cur.code: %llu; cur.bts: %u\t", tmp, pos, cur.code, cur.bts);
			cur.code = (cur.code << (sym_code_MAXbts_hf - cur.bts)) >> (sym_code_MAXbts_hf - cur.bts);
			// printf("3: tmp: %llu; pos: %u; cur.code: %llu; cur.bts: %u\n", tmp, pos, cur.code, cur.bts);
			pos = 0;
			tmp = 0;
		}
		tmp = (tmp << cur.bts) + cur.code;
		pos += cur.bts;
		// printf("4: tmp: %llu; pos: %u; cur.code: %llu; cur.bts: %u\n", tmp, pos, cur.code, cur.bts);
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
	int i;
	for (i = 0; i < table_width_hf; i++) {
		count+=table_in[i] * (table_out[i]).bts;
	}
	printf("Кол-во бит: %llu", count);
	fwrite(&count, 1, sizeof(unsigned long long), out);
}

void write_tree_hf(FILE* out, tree_hf* root) {
	if(!isleaf_hf(root)){
		static sym_code tmp = {0,1};
		write_code_hf(out, tmp);
		write_tree_hf(out, root->left);
		write_tree_hf(out, root->right);
	}
	else {
		static sym_code tmp = {1,1};
		write_code_hf(out, tmp);
		tmp.code = root->code;
		tmp.bts = 8;
		write_code_hf(out, tmp);
	}
}

void compress_file_hf(FILE* in, FILE* out, sym_code* table) {
	int c;
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
	_fseeki64(in, 0, SEEK_SET);
	compress_file_hf(in, out, tmp_table_out);
	free(tmp_table_out);
	return;
}


char read_bit_hf(FILE* in) {
	static unsigned long long buf_dec_hf = 0;
	static unsigned char pos_dec_hf = 64;
	if (pos_dec_hf == 64) {
		fread(&buf_dec_hf, sizeof(unsigned long long), 1, in);
		pos_dec_hf = 0;
	}
	return (char)((buf_dec_hf >> pos_dec_hf++) % 2);
}

char read_byte_hf(FILE* in) {
	char i;
	unsigned char c = 0;
	for (i = 0; i < 8; i++) {
		c = (c << 1) | read_bit_hf(in);
	}
	return (char)c;
}

tree_hf* tree_from_file_hf(FILE* in) {
	tree_hf* root = (tree_hf*)calloc(1, sizeof(tree_hf));
	if(read_bit_hf(in)) {
		root->code = read_byte_hf(in);
	}
	else {
		root->left = tree_from_file_hf(in);
		root->right = tree_from_file_hf(in);
	}
	return root;
}

void decompress_file_hf(FILE* in, FILE* out, tree_hf* root, unsigned long long count) {
	unsigned long long i;
	tree_hf* cur = root;
	for (i = 0; i < count; i++) {
		if(read_bit_hf(in)) {
			if(cur->right)	{
				cur = cur->right;
			}
			else {
				fprintf(out, "%d", cur->code);
				cur = (root->right) ? root->right : root;
			}
		}
		else {
			if (cur->left) {
				cur = cur->right;
			}
			else {
				fprintf(out, "%d", cur->code);
				cur = (root->left) ? root->left : root;
			}
		}
	}
}


void complete_decompres_hf(FILE* in, FILE* out) {
	tree_hf* root;
	unsigned long long count;
	fread(&count, sizeof(unsigned long long), 1, in);
	root = tree_from_file_hf(in);
	decompress_file_hf(in, out, root, count);
}