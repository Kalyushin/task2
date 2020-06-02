#ifndef TEXT_H
#define TEXT_H
/**
 * text.h -- внешний интерфейс библиотеки для работы с текстом
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */
#include <string>

#define MAXLINE 255
/**
 * Абстрактный тип текстовых объектов
 */
typedef struct _text1 *text;

/**
 * Абстрактный тип курсора
 */
typedef struct _crsr *cursor;


/**
 * Создает новый текстовый объект
 * @returns текст
 */
text create_text();

/**
 * Добавляет одну строку к тексту
 * @param txt текст
 * @param contents новая строка
 * @returns none
 */
void append_line(text txt, std::string contents);


/**
 * Обрабатывает текст, применяя заданную функцию к каждой строке
 *
 * @param txt текст
 * @param process функция-обработчик
 * @returns none
 */
void process_forward(
    text txt,
    void (*process)(int index, std::string contents, int cursor_position, void *data),
    void *data
);


/**
 * Удаляет весь текст
 *
 * @param txt текст
 * @returns none
 */
void remove_all(text txt);

/**
 * Меняет позицию курсора
 *
 * @param txt текст
 * @returns code
 */
int move_cursor(
    text txt,
    int line_cursor,
    int position_cursor
);

/**
 * Меняет позицию курсора
 * @param txt текст
 * @returns line_cursor
 */
int get_line_cursor (text txt);

/**
 *Возвращает номер пустой строчки
 *@param txt текст
 *@returns empty_number_line
 */
int empty_line(text txt);

/**
 * Удаляет строку
 * @param txt текст
 * @returns code
 */
int delete_line(
    text txt,
    int line_number
);
#endif // TEXT_H
