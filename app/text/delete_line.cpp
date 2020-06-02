/**
 * delete_line.cpp -- реализует функцию удаление строки
 *
 * Copyright (c) 2020, Sergey Kalyushin <kalyushi@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "_text.h"
#include <assert.h>

/**
 * Удаляет строку
 *
 * @param txt текст
 * @returns code
 */
int delete_line(
    text txt,
    int line_number
)
{
    /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->listok->size() == 0) {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return -2;
    }

    assert(!(txt->listok->empty()));

    /* Проверяем наличие данной строчки */
    if ((static_cast<int>(txt->listok->size()) < line_number) || (line_number < 1)){
        return -3;
    }

    /* Стартуем с начальной строки текста */
    list<string>::iterator current = txt->listok->begin();
    
    /* Переходим к новой строке */
    for (int i = 1; i < line_number; i++){
        current++;
    }

    if (current==txt->cursor->line) {
        txt->listok->erase(current);
        return -1;
    }
    txt->listok->erase(current);
    return 0;
}
