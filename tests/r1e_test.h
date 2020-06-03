#ifndef R1E_TEST_H
#define R1E_TEST_H

#include <gtest/gtest.h>

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

extern "C++" {
#include "common.h"
#include "text/text.h"
#include "text/_text.h"
}



TEST(r1eTestPositive, base) {
    text txt = create_text();

    char *inputTest = (char *)malloc(sizeof(char)*1024);
    snprintf(inputTest, 1024, "%s/input.txt", INPUTDIRMR1E);

    load(txt, inputTest);
    free(inputTest);

    char *testOutput = (char *)malloc(sizeof(char)*1024);
    char *correctOutput = (char *)malloc(sizeof(char)*1024);
    snprintf(correctOutput, 1024, "%s/output.txt", INPUTDIRMR1E);
    snprintf(testOutput, 1024, "%s/outputTest.txt", INPUTDIRMR1E);

    r1e(txt);
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

TEST(r1eTestPositive, withterminal) {
    char cmdline[MAXLINE + 1];
    char *cmd;

    text txt = create_text();

    char *inputTest = (char *)malloc(sizeof(char)*2048);
    snprintf(inputTest, 2048, "%s/input.txt", INPUTDIRMR1E);

    load(txt, inputTest);
    free(inputTest);

    char *command = (char *)malloc(sizeof(char)*2048);
    snprintf(command, 2048, "%s/command.txt", INPUTDIRMR1E);

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
    if (strcmp(cmd, "r1e") == 0) {
        r1e(txt);
    } else
        EXPECT_TRUE(false);

    char *testOutput = (char *)malloc(sizeof(char)*1024);
    char *correctOutput = (char *)malloc(sizeof(char)*1024);
    snprintf(correctOutput, 1024, "%s/output.txt", INPUTDIRMR1E);
    snprintf(testOutput, 1024, "%s/outputTest.txt", INPUTDIRMR1E);

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

TEST(r1eTestPositive, morethan1) {
    text txt = create_text();

    char *inputTest = (char *)malloc(sizeof(char)*1024);
    snprintf(inputTest, 1024, "%s/input.txt", INPUTDIRMR1E);

    load(txt, inputTest);
    free(inputTest);

    char *testOutput = (char *)malloc(sizeof(char)*1024);
    char *correctOutput = (char *)malloc(sizeof(char)*1024);
    snprintf(correctOutput, 1024, "%s/output2.txt", INPUTDIRMR1E);
    snprintf(testOutput, 1024, "%s/outputTest.txt", INPUTDIRMR1E);

    //ставим курсор на пустую строчку
    m(txt,3,0);

    r1e(txt);

    //узнаем позицию курсора
    int oldLine = 1;
    list<string>::iterator current = txt->listok->begin();
    while (current != txt->cursor->line) {
        current++;
        oldLine++;
    }
    ASSERT_EQ(oldLine, 2);
    
    r1e(txt);
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

TEST(r1eTestPositive, withoutEmptyLine) {
    text txt = create_text();

    char *inputTest = (char *)malloc(sizeof(char)*1024);
    snprintf(inputTest, 1024, "%s/input3.txt", INPUTDIRMR1E);

    load(txt, inputTest);
    free(inputTest);

    char *testOutput = (char *)malloc(sizeof(char)*1024);
    char *correctOutput = (char *)malloc(sizeof(char)*1024);
    snprintf(correctOutput, 1024, "%s/output3.txt", INPUTDIRMR1E);
    snprintf(testOutput, 1024, "%s/outputTest.txt", INPUTDIRMR1E);

    r1e(txt);
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

TEST(r1eTestNegative, emptyText) {
    text txt = create_text();

    char *debug = (char *)malloc(sizeof(char)*64);
    snprintf(debug, 64, "file.log");

    int newSTDerr = open(debug, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    ASSERT_NE(newSTDerr, -1);
    int oldSTDerr = dup(STDERR_FILENO);
    close(STDERR_FILENO);
    dup2(newSTDerr, STDERR_FILENO);

    r1e(txt);

    fflush(stderr);
    close(newSTDerr);
    dup2(oldSTDerr, STDERR_FILENO);

    int testFD = open(debug, O_RDONLY);
    char *outBuffer = (char *)malloc(sizeof(char)*64);
    char *testBuffer = (char *)malloc(sizeof(char)*64);
    int testCount;

    testCount = read(testFD, testBuffer, 64);
    snprintf(outBuffer, 64, "There are already no any lines in the text!\n");
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
#endif // R1E_TEST_H
