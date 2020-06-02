#ifndef M_H
#define M_H
#include <gtest/gtest.h>

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

extern "C++" {
#include "common.h"
#include "text/text.h"
#include "text/_text.h"
}



TEST(mTestPositive, base) {
    text txt = create_text();

    char *inputTest = (char *)malloc(sizeof(char)*2048);
    snprintf(inputTest, 2048, "%s/input.txt", INPUTDIRM);

    load(txt, inputTest);
    free(inputTest);

    m(txt, 1, 5);

    int newPos = txt->cursor->position;

    list<string>::iterator current = txt->listok->begin();
    int newLine = 1;

    while (current != txt->cursor->line) {
        current++;
        newLine++;
    }

    ASSERT_EQ(newLine, 1);
    ASSERT_EQ(newPos, 5);
    remove_all(txt);
}



TEST(mTestPositive, withterminal) {
    char cmdline[MAXLINE + 1];
    char *cmd;
    char *arg;

    text txt = create_text();

    char *inputTest = (char *)malloc(sizeof(char)*2048);
    snprintf(inputTest, 2048, "%s/input.txt", INPUTDIRM);

    load(txt, inputTest);
    free(inputTest);

    char *command = (char *)malloc(sizeof(char)*2048);
    snprintf(command, 2048, "%s/command.txt", INPUTDIRM);

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
    if (strcmp(cmd, "m") == 0) {
        if ((arg = strtok(NULL, " \n")) == NULL) {
            EXPECT_TRUE(false);
            fprintf(stderr, "Usage: m line position\n");
        } else {
            int line = atoi(arg);
            if ((arg = strtok(NULL, " \n")) == NULL) {
                EXPECT_TRUE(false);
                fprintf(stderr, "Usage: m position\n");
            } else {
                int pos = atoi(arg);
                EXPECT_TRUE(true);
                m(txt, line, pos);
            }
        }
    } else
        EXPECT_TRUE(false);

    int newPos = txt->cursor->position;

    list<string>::iterator current = txt->listok->begin();
    int newLine = 1;

    while (current != txt->cursor->line) {
        current++;
        newLine++;
    }

    ASSERT_EQ(newLine, 3);
    ASSERT_EQ(newPos, 4);
    remove_all(txt);
}

TEST(mTestNegative, emptyText) {
    text txt = create_text();

    char *debug = (char *)malloc(sizeof(char)*64);
    snprintf(debug, 64, "file.log");

    int newSTDerr = open(debug, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    ASSERT_NE(newSTDerr, -1);
    int oldSTDerr = dup(STDERR_FILENO);
    close(STDERR_FILENO);
    dup2(newSTDerr, STDERR_FILENO);

    m(txt, 0, 0);

    fflush(stderr);
    close(newSTDerr);
    dup2(oldSTDerr, STDERR_FILENO);

    int testFD = open(debug, O_RDONLY);
    char *outBuf = (char *)malloc(sizeof(char)*64);
    char *testBuf = (char *)malloc(sizeof(char)*64);
    int testCount;

    testCount = read(testFD, testBuf, 64);
    snprintf(outBuf, 64, "There are already no any lines in the text!\n");
    ASSERT_TRUE(testCount > 0);
    close(testFD);

    for(int i = 0; i < testCount; i++)
        ASSERT_EQ(outBuf[i], testBuf[i]);

    free(outBuf);
    free(testBuf);

    int ret = std::remove(debug);
    ASSERT_EQ(ret, 0);
    free(debug);
    remove_all(txt);
}

TEST(mTestNegative, withoutArguments) {
    char cmdline[MAXLINE + 1];
    char *cmd;
    char *arg;

    text txt = create_text();

    char *debug = (char *)malloc(sizeof(char)*64);
    char *command = (char *)malloc(sizeof(char)*2048);
    sprintf(command, "%s/command2.txt", INPUTDIRM);
    sprintf(debug, "file.log");

    int newSTDin = open(command, O_RDONLY);
    int oldSTDin = dup(STDIN_FILENO);
    close(STDIN_FILENO);
    int go = dup2(newSTDin, STDIN_FILENO);
    ASSERT_EQ(go, 0);
    free(command);

    // Original line from editor.cpp
    char* success = fgets(cmdline, MAXLINE, stdin);
    EXPECT_STRNE(success, NULL);

    close(newSTDin);
    go = dup2(oldSTDin, STDIN_FILENO);
    ASSERT_EQ(go, 0);

    int newSTDout = open(debug, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    ASSERT_NE(newSTDout, -1);
    int oldSTDout = dup(STDOUT_FILENO);
    close(STDOUT_FILENO);
    dup2(newSTDout, STDOUT_FILENO);

    // Original lines from editor.cpp
    cmd = strtok(cmdline, " \n");
    if (strcmp(cmd, "m") == 0) {
        if ((arg = strtok(NULL, " \n")) == NULL) {
            EXPECT_TRUE(true);
            fprintf(stdout, "Usage: m line position\n");
        } else {
            int line = atoi(arg);
            if ((arg = strtok(NULL, " \n")) == NULL) {
                EXPECT_TRUE(true);
                fprintf(stdout, "Usage: m position\n");
            } else {
                int pos = atoi(arg);
                EXPECT_TRUE(false);
                m(txt, line, pos);
            }
        }
    } else
        EXPECT_TRUE(false);

    fflush(stdout);
    close(newSTDout);
    dup2(oldSTDout, STDOUT_FILENO);

    int testFD = open(debug, O_RDONLY);
    char *outBuffer = (char *)malloc(sizeof(char)*64);
    char *testBuffer = (char *)malloc(sizeof(char)*64);
    int testCount;

    testCount = read(testFD, testBuffer, 64);
    sprintf(outBuffer, "Usage: m line position\n");
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
#endif // M_H
