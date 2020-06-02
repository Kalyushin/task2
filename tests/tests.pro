include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -Wextra -Werror
QMAKE_CFLAGS += -Wall -Wextra -Werror

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

DEFINES += INPUTDIRSAVE=\\\"$$PWD/testsave\\\" \
    INPUTDIRSHOWUPPER=\\\"$$PWD/testshowupper\\\" \
    INPUTDIRM=\\\"$$PWD/testm\\\" \
    INPUTDIRMLB=\\\"$$PWD/testmlb\\\" \
    INPUTDIRMR1E=\\\"$$PWD/testr1e\\\"

HEADERS +=     \
    ../app/common.h \
    ../app/text/text.h \
    ../app/text/_text.h \
    m_test.h \
    mlb_test.h \
    r1e_test.h \
    save_test.h \
    showupper_test.h

SOURCES +=     main.cpp \
    ../app/load.cpp \
    ../app/show.cpp \
    ../app/save.cpp \
    ../app/showupper.cpp \
    ../app/m.cpp \
    ../app/mlb.cpp \
    ../app/r1e.cpp \
    ../app/text/append_line.cpp \
    ../app/text/create_text.cpp \
    ../app/text/delete_line.cpp \
    ../app/text/empty_line.cpp \
    ../app/text/move_cursor.cpp \
    ../app/text/get_line_cursor.cpp \
    ../app/text/process_forward.cpp \
    ../app/text/remove_all.cpp

INCLUDEPATH += ../app
