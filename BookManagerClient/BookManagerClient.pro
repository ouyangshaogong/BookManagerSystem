QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    UserManagerWidget.cpp \
    adduserdialog.cpp \
    bookmodel.cpp \
    dataController.cpp \
    datacommonfunc.cpp \
    dataproxy.cpp \
    main.cpp \
    mainwindow.cpp \
    modifypasswddialog.cpp \
    myapplication.cpp \
    searchbox.cpp \
    usermodel.cpp

HEADERS += \
    UserManagerWidget.h \
    adduserdialog.h \
    bookmodel.h \
    commonmsg.h \
    datacommonfunc.h \
    datacontroller.h \
    dataproxy.h \
    mainwindow.h \
    modifypasswddialog.h \
    myapplication.h \
    searchbox.h \
    usermodel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /home/zhangfengli/vscode-projects/BookManagerSystem/include/component
INCLUDEPATH += /home/zhangfengli/vscode-projects/BookManagerSystem/include/common
LIBS += -LD:/home/zhangfengli/vscode-projects/BookManagerSystem/lib/ -lcomponent

FORMS += \
    UserManagerWidget.ui \
    adduserdialog.ui \
    modifypasswddialog.ui \
    searchbox.ui

RESOURCES += \
    res.qrc
