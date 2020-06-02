#ifndef COMMON_H

#define COMMON_H
#include "text/text.h"

/* Декларирует неиспользуемый аргумент,
 * корректно подавляя предупреждение вида "unused parameter" */
#define UNUSED(x) (void)(x)

/**
 * Выводит содержимое указанного файла на экран
 */
void show(text txt);

/**
 * Загружает содержимое указанного файла
 */
void load(text txt, char *filename);

/**
 * Сохраняет содержимое  в указанный файл
 */
void save(text txt, char *filename);

/**
 * Выводит содержимое указанного файла заглавными буквами на экран
 */
void showupper(text txt);

/**
 * Перемещает курсор
 */
void m(text txt, int number_line, int position_cursor);

/**
 * Перемещает курсор в начало строки
 */
void mlb(text txt);

/**
 * Удаляет строку из текста
 */
void rn(text txt, int line_number);

/**
 * Удаляет первую пустую строку из текста
 */
void r1e(text txt);
#endif // COMMON_H
