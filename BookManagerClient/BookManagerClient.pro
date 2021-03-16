QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataController.cpp \
    DataProxy.cpp \
    MyApplication.cpp \
    datacommonfunc.cpp \
    main.cpp \
    mainwindow.cpp \
    usermodel.cpp

HEADERS += \
    DataController.h \
    DataProxy.h \
    MyApplication.h \
    commonmsg.h \
    datacommonfunc.h \
    mainwindow.h \
    usermodel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /home/zhangfengli/vscode-projects/BookManagerSystem/include/component
INCLUDEPATH += /home/zhangfengli/vscode-projects/BookManagerSystem/include/common
LIBS += -LD:/home/zhangfengli/vscode-projects/BookManagerSystem/lib/ -lcomponent
