/**
 * empty_line.cpp -- реализует функцию поиска пустой строки
 *
 * Copyright (c) 2020, Sergey Kalyushin <kalyushi@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "_text.h"
#include <string>
#include <list>
#include <iterator>
/**
 * Возвращает номер пустой строчки
 *
 * @param txt текст
 * @returns empty_number
 */
int empty_line(text txt)
{
    /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->listok->size() == 0) {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return -3;
    }
    assert(!(txt->listok->empty()));

    /* Текст ненулевой длины должен содержать хотя бы одну строку
       assert(txt->begin != NULL && txt->end != NULL); */

    /* Стартуем с начальной строки текста */
    list<string>::iterator current = txt->listok->begin();
    int empty_number = 1;
    std::string stroka;
    do {
	stroka = *current;
	if (stroka[0] == '\n') return empty_number;
	empty_number++;
	current++;
    }while (current != txt->listok->end());

    return 0;
}
