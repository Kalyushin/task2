#ifndef _TEXT_H
#define _TEXT_H
/**
 * _text.h -- внутренние структуры представления текста
 *
 * Этот файл не должен включаться в клиентские модули
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <assert.h>
#include <list>
using namespace std;

#include "text.h"

/**
 * @struct
 * @brief Представление курсора
 *
 */
typedef struct _crsr {
    list<string>::iterator line;         /**< указатель на соку с курсором */
    int position;     /**< позиция курсора в строке */ 
} crsr;


/**
 * @struct
 * @brief Линейный двунаправленный список строк текста
 *
 */

typedef struct _text1 {
    list <string> * listok;       /**< строки текста */
    struct _crsr *cursor;       /**< позиция в тексте, курсор */
} text1;

typedef struct _text1 *text;

#endif // _TEXT_H
