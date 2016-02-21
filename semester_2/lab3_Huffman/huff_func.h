#ifndef _HUFF_FUNC_H
#define _HUFF_FUNC_H

#define table_type_hf int // тип таблицы
#define table_width_hf 256 // кол-во элементов в таблице
#define table_counter_hf unsigned char // тип необходимый для хранения индекса таблицы

typedef struct _tree_hf{
  char code;
  table_type_hf count;
  struct _tree_hf* left;
  struct _tree_hf* right;
}tree_hf;

typedef struct _queue_hf {
  tree_hf* root;
  struct _queue_hf* next;
}queue_hf;

/**
 * добавление в очередь с приоритетом (по возрастанию)
 * @param  head  указатель на голову очереди
 * @param  code  код символа
 * @param  count кол-во встреч этого символа
 * @return       очередь с приоритетом (по возрастанию) с добавленным элементом
 */
queue_hf* push_ord_hf(queue_hf* queue, table_type_hf code, table_counter_hf count);

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
table_type_hf* read_file_hf(FILE* in);

/**
 * получение очереди с приоритетом (по возрастанию) из таблицы частот
 * @param  table корректная таблица частот
 * @return       очередь с приоритетом (по возрастанию) (состоит из деревьев единичной высоты)
 */
queue_hf* queue_from_table_hf(table_hf* table);

/**
 * построение дерева из очереди с приоритетом
 * @param  queue очередь с приоритетом (по возрастанию)
 * @return       готовое дерево (построенное для алгоритма сжатия хаффмана)
 */
tree_hf* tree_from_queue_hf(queue_hf* queue);

#endif