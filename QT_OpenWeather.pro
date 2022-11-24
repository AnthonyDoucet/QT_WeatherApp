QT       += \
         core gui \
         network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    weather.cpp

HEADERS += \
    mainwindow.h \
    token.h \
    weather.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -LC:\Qt\Tools\OpenSSL\Win_x64\bin -llibssl-1_1-x64
LIBS += -LC:\Qt\Tools\OpenSSL\Win_x64\bin -llibcrypto-1_1-x64
INCLUDEPATH += C:\Qt\Tools\OpenSSL\Win_x64\bin