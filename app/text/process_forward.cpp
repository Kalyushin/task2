/**
 * process_forward.cpp -- реализует обобщенную функцию обработки текста
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "_text.h"

/**
 * Обрабатывает список, применяя заданную функцию к каждой строке
 *
 * @param txt текст
 * @param process функция-обработчик
 * @returns none
 */
void process_forward(
    text txt,
    void (*process)(int index, std::string contents, int cursor, void *data),
    void *data
)
{
    /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->listok->size() == 0) {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return;
    }
    assert(!(txt->listok->empty()));

    /* Стартуем с начальной строки текста */
    list<string>::iterator current = txt->listok->begin();
    int index = 0;
    int cursor_position = -1;

    /* К каждой строке текста применяем обработчик */
    do {
        if (txt->cursor->line == current)
            cursor_position = txt->cursor->position;
        else
            cursor_position = -1;
        process(index, *current, cursor_position, data);
        current++;
        index++;
    } while (current != txt->listok->end());
}
