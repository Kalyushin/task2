/**
 * editor.cpp -- строковый текстовый редактор
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
using namespace std;

#include "text/text.h"
#include "common.h"

#define MAXLINE 255

int main()
{
    char cmdline[MAXLINE + 1];
    char *cmd;
    char *arg;
    char *arg1;
    char *arg2;

    /* Создаем объект для представления текста */
    text txt = create_text();

    /* Цикл обработки команд */
    while (1) {

	printf("ed > ");

        /* Получаем команду */
	char* success = fgets(cmdline, MAXLINE, stdin);
        assert(success != NULL);

        /* Извлекаем имя команды */
        if ((cmd = strtok(cmdline, " \n")) == NULL) {
            continue;
        }

        /* Распознаем поддерживаемую команду */

        /* Завершаем работу редактора */
        if (strcmp(cmd, "quit") == 0) {
            fprintf(stderr, "Bye!\n");
            break;
        }

        /* Загружаем содержимое файла, заданного параметром */
        if (strcmp(cmd, "load") == 0) {
            if ((arg = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: load filename\n");
            } else {
                load(txt, arg);
            }
            continue;
        }

        /* Выводим текст */
        if (strcmp(cmd, "show") == 0) {
            show(txt);
            continue;
        }

    /* Сохраняем содержимое в указанный параметром файл */
        if (strcmp(cmd, "save") == 0) {
            if ((arg = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: load filename\n");
            } else {
                save(txt, arg);
            }
            continue;
        }

	/* Выводим текст заглавными буквами */
        if (strcmp(cmd, "showupper") == 0) {
            showupper(txt);
            continue;
        }

	/* Меняем позицию курсора */
    if (strcmp(cmd, "m") == 0) {
        if ((arg1 = strtok(NULL, " \n")) == NULL) {
        fprintf(stderr, "Usage: line number \n");
        } else {
        if ((arg2 = strtok(NULL, " \n")) == NULL) {
            fprintf(stderr, "Usage: cursor position \n");
        } else {
            unsigned int number_line = atoi(arg1);
            unsigned int position = atoi(arg2);
            m(txt, number_line, position);
        }
        continue;
        }
    }

    /* Передвигаем курсор в начало строки */
    if (strcmp (cmd, "mlb") == 0) {
        mlb(txt);
        continue;
    }

    /* Удаляем заданную строку */
    if (strcmp(cmd, "rn") == 0) {
        if ((arg = strtok(NULL, " \n")) == NULL) {
        fprintf(stderr, "Usage: load filename\n");
        } else {
        unsigned int line_number = atoi(arg);
        rn(txt, line_number);
        }
        continue;
    }

    /* Удаляет первую пустую строку из текста */
        if (strcmp (cmd, "r1e") == 0) {
            r1e(txt);
            continue;
        } 


        /* Если команда не известна */
        fprintf(stderr, "Unknown command: %s\n", cmd);
    }

    return 0;
}
