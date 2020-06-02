/**
 * save.cpp -- реализует команду сохранения хранимого текста в файл
 *
 * Copyright (c) 2020, ЛKalyushin Sergey <kalyushi@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <cstdio>
#include <assert.h>
#include "common.h"
#include "text/text.h"

static void save_line(int index, std::string contents, int cursor, void *data);

/**
 * Выводит содержимое указанного файла на экран
 */
void save(text txt, char *filename)
{
    FILE * f = fopen(filename, "w");
    /* Применяем функцию save_line к каждой строке текста */
    process_forward(txt, save_line,f );
    fclose (f);
}

/**
 * Сохраняем содержимое в указанный файл
 */
static void save_line(int index, std::string contents, int cursor, void *data)
{
    assert(!contents.empty());

    /* Декларируем неиспользуемые параметры */
    UNUSED(index);
    UNUSED(cursor);

    FILE * fl = static_cast <FILE*> (data);
    /* Сохраняем каждую строчку */
    fprintf(fl, "%s", contents.c_str());
}
