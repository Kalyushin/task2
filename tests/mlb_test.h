#ifndef MLB_TEST_H
#define MLB_TEST_H
#include <gtest/gtest.h>

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

extern "C++" {
#include "common.h"
#include "text/text.h"
#include "text/_text.h"
}



TEST(mlbTestPositive, base) {
    text txt = create_text();

    char *inputTest = (char *)malloc(sizeof(char)*2048);
    snprintf(inputTest, 2048, "%s/input.txt", INPUTDIRMLB);

    load(txt, inputTest);
    free(inputTest);

    int oldLine = 1;
    list<string>::iterator current = txt->listok->begin();
    while (current != txt->cursor->line) {
        current++;
        oldLine++;
    }
    mlb(txt);

    int newPos = txt->cursor->position;

    current = txt->listok->begin();
    int newLine = 1;

    while (current != txt->cursor->line) {
        current++;
        newLine++;
    }

    ASSERT_EQ(newLine, oldLine);
    ASSERT_EQ(newPos, 0);
    remove_all(txt);
}

TEST(mlbTestPositive, withterminal) {
    char cmdline[MAXLINE + 1];
    char *cmd;

    text txt = create_text();

    char *inputTest = (char *)malloc(sizeof(char)*2048);
    snprintf(inputTest, 2048, "%s/input.txt", INPUTDIRMLB);

    load(txt, inputTest);
    free(inputTest);

    int oldLine = 1;
    list<string>::iterator current = txt->listok->begin();
    while (current != txt->cursor->line) {
        current++;
        oldLine++;
    }

    char *command = (char *)malloc(sizeof(char)*2048);
    snprintf(command, 2048, "%s/command.txt", INPUTDIRMLB);

    int newSTDin = open(command, O_RDONLY);
    int oldSTDin = dup(STDIN_FILENO);
    dup2(newSTDin, STDIN_FILENO);
    free(command);

    // Original line from editor.cpp
    char* success = fgets(cmdline, MAXLINE, stdin);
    EXPECT_STRNE(success, NULL);

    close(newSTDin);
    dup2(oldSTDin, STDIN_FILENO);

    // Original lines from editor.cpp
    cmd = strtok(cmdline, " \n");
    if (strcmp(cmd, "mlb") == 0) {
        mlb(txt);
    } else
        EXPECT_TRUE(false);

    int newPos = txt->cursor->position;

    current = txt->listok->begin();
    int newLine = 1;

    while (current != txt->cursor->line) {
        current++;
        newLine++;
    }

    ASSERT_EQ(newLine, oldLine);
    ASSERT_EQ(newPos, 0);
    remove_all(txt);
}

TEST(mlbTestNegative, emptyText) {
    text txt = create_text();

    char *debug = (char *)malloc(sizeof(char)*64);
    snprintf(debug, 64, "file.log");

    int newSTDerr = open(debug, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    ASSERT_NE(newSTDerr, -1);
    int oldSTDerr = dup(STDERR_FILENO);
    close(STDERR_FILENO);
    dup2(newSTDerr, STDERR_FILENO);

    mlb(txt);

    fflush(stderr);
    close(newSTDerr);
    dup2(oldSTDerr, STDERR_FILENO);

    int testFD = open(debug, O_RDONLY);
    char *outBuffer = (char *)malloc(sizeof(char)*64);
    char *testBuffer = (char *)malloc(sizeof(char)*64);
    int testCount;

    testCount = read(testFD, testBuffer, 64);
    snprintf(outBuffer, 64, "There are already no any lines in the text!\nThere are already no any lines in the text!\n");
    ASSERT_TRUE(testCount > 0);
    close(testFD);

    for(int i = 0; i < testCount; i++)
        ASSERT_EQ(outBuffer[i], testBuffer[i]);

    free(outBuffer);
    free(testBuffer);

    int ret = std::remove(debug);
    ASSERT_EQ(ret, 0);
    free(debug);
    remove_all(txt);
}
#endif // MLB_TEST_H
