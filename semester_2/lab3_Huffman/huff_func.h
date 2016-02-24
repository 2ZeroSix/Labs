#ifndef _HUFF_FUNC_H
#define _HUFF_FUNC_H

#include <stdio.h>
#include <stdlib.h>
// таблица частот
#define table_type_hf int // тип таблицы
#define table_width_hf 256 // кол-во элементов в таблице
#define table_counter_hf unsigned char // тип необходимый для хранения индекса таблицы

typedef struct _tree_hf{
  char code; //код символа
  table_type_hf count;
  struct _tree_hf* left;
  struct _tree_hf* right;
}tree_hf;

typedef struct _queue_hf {
  tree_hf* root;
  struct _queue_hf* next;
}queue_hf;

#define sym_code_MAXbts_hf 64 // максимальное кол-во значимых бит
#define sym_code_code_hf unsigned long long // тип для кода символа
#define sym_code_bts_hf unsigned char // тип для хранения кол-ва значимых бит

//элемент таблицы кодов символов
typedef struct _sym_code {
  unsigned long long code; // код после сжатия
  unsigned char bts; // кол-во значимых бит
}sym_code;

/**
 * добавление в очередь с приоритетом (по возрастанию)
 * @param  head  указатель на голову очереди
 * @param  code  код символа
 * @param  count кол-во встреч этого символа
 * @return       очередь с приоритетом (по возрастанию) с добавленным элементом
 */
queue_hf* push_ord_hf(queue_hf* queue, tree_hf* new);

/**
 * достает хранящееся в голове очереди дерево
 * @param  head указатель на указатель на очередь
 * @return      дерево хранящееся в голове очереди
 * (сдвигает указатель на голову очереди на следующий элемент очереди)
 */
tree_hf* take_tree_ord_hf(queue_hf** queue);

/**
 * таблица частот из файла (таблица кол-ва встреч символов в файле)
 * @param  in указатель на поток
 * @return    таблица частот 
 * (массив из table_width_hf (смотри в #define) элементов (a[i] = кол-во элементов с кодом i)
 */
table_type_hf* file_table_hf(FILE* in);

/**
 * получение очереди с приоритетом (по возрастанию) из таблицы частот
 * @param  table корректная таблица частот
 * @return       очередь с приоритетом (по возрастанию) (состоит из деревьев единичной высоты)
 */
queue_hf* queue_from_table_hf(table_type_hf* table);

/**
 * слияние деревьев
 * @param  root1 ненулевой указатель на дерево
 * @param  root2 ненулевой указатель на дерево
 * @return       дерево полученное в результате слияния
 *  */
tree_hf* merge_tree_hf(tree_hf* root1, tree_hf* root2);

/**
 * построение дерева из очереди с приоритетом
 * @param  queue очередь с приоритетом (по возрастанию)
 * @return       готовое дерево (построенное для алгоритма сжатия хаффмана)
 */
tree_hf* tree_from_queue_hf(queue_hf* queue);

/**
 * построение таблицы из дерева проходом в глубину
 * @param root  указатель на дерево с ненулевыми поддеревьями (либо на нулевое дерево)
 * @param table указатель на таблицу из 256 элементов(либо на нулевую)
 * @param cur   текущее состояние(для начала работы должно быть {0, 0})
 */
void depth_table_hf(tree_hf* root, sym_code* table, sym_code cur);

/**
 * полное построение таблицы из дерева
 * @param  root указатель на дерево
 * @return      если указатель ненулевой, то таблица, иначе NULL
 */
sym_code* table_from_tree_hf(tree_hf* root);

/**
 * для вывода с символами величиной меньше байта
 * @param out указатель на выходной поток
 * @param cur новый символ
 */
void write_code_hf(FILE* out, sym_code cur);

void complete_compress_hf(FILE*in, FILE* out);

#endif