/**
 * get_line_cursor.cpp -- возвращает номер строки с  курсором
 *
 * Copyright (c) 2020, Sergey Kalyushin <kalyushi@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "_text.h"
#include <string>
using namespace std;

/**
 * Меняет позицию курсора
 *
 * @param txt текст
 * @returns line_cursor
 */
int  get_line_cursor (text txt)
{
    int number_line =  0;
    /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->listok->size() == 0) {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return number_line;
    }
    assert(!(txt->listok->empty()));
    number_line++;

    /* Стартуем с начальной строки текста */
    list <string>::iterator current = txt->listok->begin();
    if (current == txt->cursor->line) {
	return number_line;
    } else {
	/* Переходим к новой строке */
	while (current != txt->cursor->line) {
	    current++;
	    number_line++;
    }
    return number_line;
    }
}
