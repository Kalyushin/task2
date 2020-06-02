/**
 * append_line.cpp -- функции для добавления строк
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "_text.h"
#include <string>
using namespace std;


/**
 * Добавляет одну строку к тексту
 * @param txt текст
 * @param contents новая строка
 * @returns none
 */
void append_line(text txt, string contents)
{
    txt->listok->push_back(contents);

    /* Устанавливаем курсор в конец добавленной строки */
    txt->cursor->line++;
    string last_string = txt->listok->back();
    txt->cursor->position = last_string.length() - 1;
}
