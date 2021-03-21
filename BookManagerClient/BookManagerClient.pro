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
    loginhistorymodel.cpp \
    main.cpp \
    mainwindow.cpp \
    modifypasswddialog.cpp \
    myapplication.cpp \
    mylistwidget.cpp \
    mytablewidget.cpp \
    searchbox.cpp \
    searchcondition.cpp \
    usermodel.cpp

HEADERS += \
    SystemOperateCmd.h \
    UserManagerWidget.h \
    adduserdialog.h \
    bookmodel.h \
    commonmsg.h \
    datacommonfunc.h \
    datacontroller.h \
    dataproxy.h \
    loginhistorymodel.h \
    mainwindow.h \
    modifypasswddialog.h \
    myapplication.h \
    mylistwidget.h \
    mytablewidget.h \
    searchbox.h \
    searchcondition.h \
    usermodel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /home/zhangfengli/vscode-projects/BookManagerSystem/include/component
INCLUDEPATH += /home/zhangfengli/vscode-projects/BookManagerSystem/include/common
INCLUDEPATH += /home/zhangfengli/vscode-projects/BookManagerSystem/include/utils
LIBS += -LD:/home/zhangfengli/vscode-projects/BookManagerSystem/lib/ -lcomponent -lbookutils

FORMS += \
    UserManagerWidget.ui \
    adduserdialog.ui \
    modifypasswddialog.ui \
    searchbox.ui \
    searchcondition.ui

RESOURCES += \
    res.qrc
