/**
 * r1e.cpp -- функция удаления gпервой пустой строки из текста
 *
 * Copyright (c) 2020, Kalyushin Sergey <kalyushi@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include "common.h"
#include "text/text.h"

/**
 * Удаляет первую пустую строку из текста
 */
void r1e(text txt)
{
    int empty = empty_line(txt);
    if (empty == 0) return;
    int code = delete_line(txt,empty_line(txt));
    if (code == -1){
	if(empty > 1)
	    move_cursor(txt, empty - 1, 0);
	else move_cursor(txt, empty, 0);
    }
	
}


