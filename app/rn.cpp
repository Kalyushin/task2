/**
 * rn.cpp -- функция удаления строки из текста
 *
 * Copyright (c) 2020, Kalyushin Sergey <kalyushi@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include "common.h"
#include "text/text.h"

/**
 * Удаляет строку из текста
 */
void rn(text txt, int line_number)
{
    int code = delete_line(txt, line_number);
    if (code == -3) {
    printf("Данная строка отсутсвует \n");
    }
    if (code == -1)
    {
	if (line_number > 1) 
	    move_cursor(txt, line_number - 1, 0);
	else move_cursor(txt,line_number, 0);
    }
}
