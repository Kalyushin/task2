/**
 * create_text.cpp -- создает в памяти структуры для представления текста
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "_text.h"
#include <list>
#include <string>
using namespace std;

/**
 * Создает новый текстовый объект 
 * @returns текст
 */
text create_text()
{
    text1 *txt = new text1;
    txt->listok = new list <string>;
    /* Создаем структуру описания текста */
    txt->cursor = new crsr;

    /* Создаем структуру описания курсора */
    if (txt->cursor == NULL) {
        fprintf(stderr, "Not enough memory!\n");
        exit(EXIT_FAILURE);
	} 

    /* Курсор не настроен ни на какой символ текста */
    txt->cursor->line = txt->listok->begin();
    txt->cursor->position = 0;

    return txt;
}
