/**
 * mlb.cpp -- функция перемещения курсора в начало строки
 *
 * Copyright (c) 2020, Sergey Kalyushin <kalyushi@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include "common.h"
#include "text/text.h"

void mlb(text txt)
{
   int code = get_line_cursor(txt);
   if (code == -1) return;
   move_cursor(txt,code, 0);
}
