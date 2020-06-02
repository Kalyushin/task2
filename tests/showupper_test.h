#ifndef SHOWUPPER_TEST_H
#define SHOWUPPER_TEST_H

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

TEST(showupperTestPositive, base) {
    text txt = create_text();

    char *outputTest = (char *)malloc(sizeof(char)*2048);
    char *inputTest = (char *)malloc(sizeof(char)*2048);
    snprintf(outputTest, 2048, "%s/outputTest.txt", INPUTDIRSHOWUPPER);
    snprintf(inputTest, 2048, "%s/input.txt", INPUTDIRSHOWUPPER);

    load(txt, inputTest);
    free(inputTest);

    int newSTDout = open(outputTest, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    ASSERT_NE(newSTDout, -1);
    int oldSTDout = dup(STDOUT_FILENO);
    close(STDOUT_FILENO);
    dup2(newSTDout, STDOUT_FILENO);

    showupper(txt);

    fflush(stdout);
    close(newSTDout);
    dup2(oldSTDout, STDOUT_FILENO);

    char *correctOutput = (char *)malloc(sizeof(char)*2048);
    snprintf(correctOutput, 2048, "%s/output.txt", INPUTDIRSHOWUPPER);

    int testFD = open(outputTest, O_RDONLY);
    int correctFD = open(correctOutput, O_RDONLY);
    char *outBuffer = (char *)malloc(sizeof(char)*16);
    char *testBuffer = (char *)malloc(sizeof(char)*16);
    int testCount, outputCount;
    free(correctOutput);

    testCount = read(testFD, testBuffer, 16);
    outputCount = read(correctFD, outBuffer, 16);
    close(testFD);
    close(correctFD);

    ASSERT_EQ(testCount, outputCount);
    for(int i = 0; i < testCount; i++)
        ASSERT_EQ(outBuffer[i], testBuffer[i]);

    free(outBuffer);
    free(testBuffer);
    remove_all(txt);

    int ret = std::remove(outputTest);
    ASSERT_EQ(ret, 0);
    free(outputTest);
}


TEST(showupperTestPositive, withterminal) {
    char cmdline[MAXLINE + 1];
    char *cmd;

    text txt = create_text();

    char *inputTest = (char *)malloc(sizeof(char)*2048);
    char *outputTest = (char *)malloc(sizeof(char)*2048);
    snprintf(inputTest, 2048, "%s/input.txt", INPUTDIRSHOWUPPER);
    snprintf(outputTest, 2048, "%s/outputTest.txt", INPUTDIRSHOWUPPER);

    load(txt, inputTest);
    free(inputTest);

    char *command = (char *)malloc(sizeof(char)*2048);
    snprintf(command, 2048, "%s/command.txt", INPUTDIRSHOWUPPER);

    int newSTDin = open(command, O_RDONLY);
    int oldSTDin = dup(STDIN_FILENO);
    dup2(newSTDin, STDIN_FILENO);
    free(command);

    // Original line from editor.cpp
    char* success = fgets(cmdline, MAXLINE, stdin);
    EXPECT_STRNE(success, NULL);

    close(newSTDin);
    dup2(oldSTDin, STDIN_FILENO);

    int newSTDout = open(outputTest, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    ASSERT_NE(newSTDout, -1);
    int oldSTDout = dup(STDOUT_FILENO);
    close(STDOUT_FILENO);
    dup2(newSTDout, STDOUT_FILENO);

    // Original lines from editor.cpp
    cmd = strtok(cmdline, " \n");
    if (strcmp(cmd, "showupper") == 0) {
        EXPECT_TRUE(true);
        showupper(txt);
    } else
        EXPECT_TRUE(false);

    fflush(stdout);
    close(newSTDout);
    dup2(oldSTDout, STDOUT_FILENO);

    char *correctOutput = (char *)malloc(sizeof(char)*2048);
    snprintf(correctOutput, 2048, "%s/output.txt", INPUTDIRSHOWUPPER);

    int testFD = open(outputTest, O_RDONLY);
    int correctFD = open(correctOutput, O_RDONLY);
    free(correctOutput);

    char *outBuffer = (char *)malloc(sizeof(char)*256);
    char *testBuffer = (char *)malloc(sizeof(char)*256);
    int outCount, testCount;

    outCount = read(correctFD, outBuffer, 256);
    testCount = read(testFD, testBuffer, 256);
    close(correctFD);
    close(testFD);

    ASSERT_EQ(outCount, testCount);
    for(int i = 0; i < testCount; i++)
        ASSERT_EQ(outBuffer[i], testBuffer[i]);

    free(outBuffer);
    free(testBuffer);
    remove_all(txt);

    int ret = std::remove(outputTest);
    ASSERT_EQ(ret, 0);
    free(outputTest);
}

#endif // SHOWUPPER_TEST_H
