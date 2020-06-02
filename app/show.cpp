/**
 * show.cpp -- реализует команду вывода хранимого текста на экран
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "text/text.h"

static void show_line(int index, std::string contents, int cursor, void *data);

/**
 * Выводит содержимое указанного файла на экран
 */
void show(text txt)
{
    /* Применяем функцию show_line к каждой строке текста */
    process_forward(txt, show_line, NULL);
}

/**
 * Выводит содержимое указанного файла на экран
 */
static void show_line(int index, std::string contents, int cursor, void *data)
{
    assert(!contents.empty());
    /* Декларируем неиспользуемые параметры */
    UNUSED(index);
    UNUSED(data);

    /* Выводим строку на экран */
    if (cursor != -1) {
    int i = 0;
    while (i != cursor) {
        putchar(contents[i]);
        i++;
    }
    printf("|");
    while (contents[i] != '\0')  {
        putchar(contents[i]);
        i++;
    }
    }

    if (cursor == -1) {
        std::cout << contents;
    }
}
