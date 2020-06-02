/**
 * move_cursor.cpp -- реализует обобщенную функцию перемещения курсора
 *
 * Copyright (c) 2020, Sergey Kalyushin <kalyushi@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "_text.h"
#include <string>
#include <list>
/**
 * Меняет позицию курсора
 *
 * @param txt текст
 * @returns code
 */
int move_cursor(
    text txt,
    int line_cursor,
    int position_cursor
)
{
    /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->listok->size() == 0) {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return -3;
    }
    assert(!(txt->listok->empty()));

    /* Проверка номера строки */
    if ((line_cursor > static_cast<int>(txt->listok->size())) || (line_cursor <= 0)) {
    return -1;
    }

    /* Стартуем с начальной строки текста */
    list<string>::iterator current = txt->listok->begin();
    advance(current, line_cursor - 1);
    txt->cursor->line = current;
    std::string stroka = *current;

    /* Переходим к позиции курсора в строке */
    if ((static_cast<int>(stroka.length()) - 1 < position_cursor) || (position_cursor < 0)) {
    return -2;
    }

    txt->cursor->position = position_cursor;
    return 0;
}
