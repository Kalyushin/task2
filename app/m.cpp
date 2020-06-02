/**
 * m.cpp -- функция перемещения курсора
 *
 * Copyright (c) 2020, Sergey Kalyushin <kalyushi@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include "common.h"
#include "text/text.h"

/**
 * Перемещает курсор
 */
void m(text txt, int number_line, int position_cursor)
{
    int code = move_cursor(txt, number_line, position_cursor);
    if(code == -1) {
    printf("Строка с данным номером отсутствует в тексте \n");
    }
    if(code == -2) {
    printf("Позиция с данным номером отсутсвует в строке \n");
    }
}
