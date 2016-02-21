#ifndef _HUFF_FUNC_H
#define _HUFF_FUNC_H

#define table_type_hf int // тип данных хранящихся в таблице


/**
 * таблица кол-ва встреч символов в файле
 * @param  in указатель на поток
 * @return    массив из 256 элементов (a[i] = кол-во элементов с кодом i)
 */
table_type_hf* read_file_hf(FILE* in);

#endif