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
 * проверка лист ли это
 * @param  root указатель на дерево
 * @return      если лист, то 1,
 *              иначе 0
 */
char isleaf_hf(tree_hf* root);

/**
 * таблица частот из файла (таблица кол-ва встреч символов в файле)
 * @param  in ненулевой указатель на входной поток
 * @return    таблица частот 
 * (массив из table_width_hf (смотри в #define) элементов (a[i] = кол-во элементов с кодом i)
 */
table_type_hf* file_table_hf(FILE* in);

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
 * @return      если head и *head ненулевые, то дерево хранящееся в голове очереди,
 *              иначе NULL
 * (сдвигает указатель на голову очереди на следующий элемент очереди)
 */
tree_hf* take_tree_ord_hf(queue_hf** queue);

/**
 * получение очереди с приоритетом (по возрастанию) из таблицы частот
 * @param  table корректная таблица частот
 * @return       если указатель на таблицу ненулевой, то очередь с приоритетом (по возрастанию) (состоит из деревьев единичной высоты),
 *               иначе NULL
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
 * @return       Если queue ненулевой, то готовое дерево (построенное для алгоритма сжатия хаффмана)
 *               Иначе NULL
 */
tree_hf* tree_from_queue_hf(queue_hf* queue);

/**
 * построение таблицы из дерева проходом в глубину
 * @param root  указатель на дерево с ненулевыми поддеревьями (либо на нулевое дерево)
 * @param table указатель на таблицу из 256 элементов(либо на нулевую)
 * @param cur   текущее состояние(для начала работы должно быть {0, 0})
 *
 * Если root или table нулевые, то ничего не происходит
 */
void depth_table_hf(tree_hf* root, sym_code* table, sym_code cur);

/**
 * полное построение таблицы из дерева
 * @param  root указатель на дерево
 * @return      Если root ненулевой, то таблица,
 *              Иначе NULL
 */
sym_code* table_from_tree_hf(tree_hf* root);

/**
 * Вывод по 8 байт
 * @param out ненулевой указатель на выходной поток
 * @param cur новый символ
 *
 * Для вывода оставшихся в буфере бит cur.bts должен быть равен 0
 */
void write_code_hf(FILE* out, sym_code cur);

/**
 * считает число выходных бит(только сжатые данные, без дерева и этого числа) и выводит его в поток
 * @param out       ненулевой указатель на выходной поток
 * @param table_in  таблица частот из 256 элементов
 * @param table_out таблица кодов из 256 элементов
 *
 * выводит long long
 */
void write_count_hf(FILE* out, table_type_hf* table_in, sym_code* table_out);

/**
 * выводит дерево в поток
 * @param out  ненулевой указатель на выходной поток 
 * @param root ненулевой указатель на дерево
 */
void write_tree_hf(FILE* out, tree_hf* root);

/**
 * сжатие файла
 * @param in    ненулевой указатель на входной поток 
 * @param out   ненулевой указатель на выходной поток 
 * @param table таблица кодов из 256 элементов
 */
void compress_file_hf(FILE* in, FILE* out, sym_code* table);

/**
 * полное сжатие файла
 * @param in  ненулевой указатель на входной файл
 * @param out ненулевой указатель на выходной файл
 */
void complete_compress_hf(FILE*in, FILE* out);

/**
 * чтение одного бита с помощью буфера
 * @param  in ненулевой указатель на входной поток
 * @return    1 и 0 соответственно
 */
char read_bit_hf(FILE* in);

/**
 * чтение одного байта с помощью буфера(для правильного считывания при использовании функции read_bit_hf)
 * @param  in ненулевой указатель на входной поток
 * @return    один байт типом char
 */
char read_byte_hf(FILE* in);

/**
 * восстановление дерева
 * @param  in указатель на входной поток с правильно закодированным деревом
 * @return    указатель на восстановленное дерево
 */
tree_hf* tree_from_file_hf(FILE* in);

/**
 * восстановление сжатого файла
 * @param in    ненулевой указатель на входной поток
 * @param out   ненулевой указатель на выходной поток
 * @param root  восстановленное дерево
 * @param count кол-во бит сжатой информации(не учитывая дополнительной информации записанной в файле)
 */
void decompress_file_hf(FILE* in, FILE* out, tree_hf* root, unsigned long long count);

/**
 * полное восстановление сжатого файла
 * @param in  ненулевой указатель на входной поток
 * @param out ненулевой указатель на выходной поток
 */
void complete_decompres_hf(FILE* in, FILE* out);

#endif
