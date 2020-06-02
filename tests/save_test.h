#ifndef SAVE_TEST_H
#define SAVE_TEST_H

#include <gtest/gtest.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>

extern "C++" {
#include "common.h"
#include "text/text.h"
}



TEST(saveTestPositive, base) {
    text txt = create_text();

    char *inputTest = (char *)malloc(sizeof(char)*1024);
    snprintf(inputTest, 1024, "%s/input.txt", INPUTDIRSAVE);

    load(txt, inputTest);
    free(inputTest);

    append_line(txt, "Test line.");

    char *testOutput = (char *)malloc(sizeof(char)*1024);
    char *correctOutput = (char *)malloc(sizeof(char)*1024);
    snprintf(correctOutput, 1024, "%s/output.txt", INPUTDIRSAVE);
    snprintf(testOutput, 1024, "%s/outputTest.txt", INPUTDIRSAVE);

    save(txt, testOutput);

    int test = open(testOutput, O_RDONLY);
    int correct = open(correctOutput, O_RDONLY);
    free(correctOutput);

    char *outBuffer = (char *)malloc(sizeof(char)*256);
    char *testBuffer = (char *)malloc(sizeof(char)*256);
    int outCount, testCount;

    outCount = read(correct, outBuffer, 256);
    testCount = read(test, testBuffer, 256);
    close(correct);
    close(test);

    ASSERT_EQ(outCount, testCount);
    for(int i = 0; i < testCount; i++)
        ASSERT_EQ(outBuffer[i], testBuffer[i]);

    free(outBuffer);
    free(testBuffer);
    remove_all(txt);

    int ret = std::remove(testOutput);
    ASSERT_EQ(ret, 0);
    free(testOutput);
}

TEST(saveTestNegative, noFilename) {
    char cmdline[MAXLINE + 1];
    char *cmd;
    char *arg;

    text txt = create_text();
    append_line(txt, "This is a test line.");

    char *command = (char *)malloc(sizeof(char)*2048);
    snprintf(command, 2048, "%s/command2.txt", INPUTDIRSAVE);
    char *debug = (char *)malloc(sizeof(char)*64);
    snprintf(debug, 64, "file.log");

    int newSTDin = open(command, O_RDONLY);
    int oldSTDin = dup(STDIN_FILENO);
    dup2(newSTDin, STDIN_FILENO);
    free(command);

    // Original line from editor.cpp
    char* success = fgets(cmdline, MAXLINE, stdin);
    EXPECT_STRNE(success, NULL);

    close(newSTDin);
    dup2(oldSTDin, STDIN_FILENO);

    int newSTDerr = open(debug, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    ASSERT_NE(newSTDerr, -1);
    int oldSTDerr = dup(STDERR_FILENO);
    close(STDERR_FILENO);
    dup2(newSTDerr, STDERR_FILENO);

    // Original lines from editor.cpp
    cmd = strtok(cmdline, " \n");
    if (strcmp(cmd, "save") == 0) {
        if ((arg = strtok(NULL, " \n")) == NULL) {
            EXPECT_TRUE(true);
            fprintf(stderr, "Usage: save filename\n");
        } else {
            EXPECT_TRUE(false);
            save(txt, arg);
        }
    }

    fflush(stderr);
    close(newSTDerr);
    dup2(oldSTDerr, STDERR_FILENO);

    int testFD = open(debug, O_RDONLY);
    char *outBuffer = (char *)malloc(sizeof(char)*64);
    char *testBuffer = (char *)malloc(sizeof(char)*64);
    int testCount;

    testCount = read(testFD, testBuffer, 64);
    snprintf(outBuffer, 64, "Usage: save filename\n");
    ASSERT_TRUE(testCount > 0);
    close(testFD);

    for(int i = 0; i < testCount; i++)
        ASSERT_EQ(outBuffer[i], testBuffer[i]);

    free(outBuffer);
    free(testBuffer);
    remove_all(txt);

    int ret = std::remove(debug);
    ASSERT_EQ(ret, 0);
    free(debug);
}

#endif // SAVE_TEST_H
