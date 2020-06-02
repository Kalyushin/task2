TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    editor.cpp \
    load.cpp \
    m.cpp \
    mlb.cpp \
    save.cpp \
    r1e.cpp \
    rn.cpp \
    show.cpp \
    showupper.cpp \
    text/append_line.cpp \
    text/create_text.cpp \
    text/get_line_cursor.cpp \
    text/move_cursor.cpp \
    text/delete_line.cpp \
    text/empty_line.cpp \
    text/process_forward.cpp \
    text/remove_all.cpp

HEADERS += \
    common.h \
    text/_text.h \
    text/text.h

QMAKE_CFLAGS += -Wall -Wextra -Werror

# gcov
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov
