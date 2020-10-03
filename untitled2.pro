QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Test/decisionmodel.cpp \
    Test/decisionwidget.cpp \
    Test/testwidget.cpp \
    Test/testwidgetitem.cpp \
    dataLoader/dataloader.cpp \
    dataLoader/datathread.cpp \
    main.cpp \
    mainwindow.cpp \
    treewidget.cpp

HEADERS += \
    Test/decisionmodel.h \
    Test/decisionwidget.h \
    Test/testwidget.h \
    Test/testwidgetitem.h \
    dataLoader/dataloader.h \
    dataLoader/datathread.h \
    mainwindow.h \
    treewidget.h

FORMS += \
    Test/testwidget.ui \
    Test/testwidgetitem.ui \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

DISTFILES += \
    Основы алгоритмизации/Алгоритм и его свойства/Алгоритм и его свойства.files/colorschememapping.xml \
    Основы алгоритмизации/Алгоритм и его свойства/Алгоритм и его свойства.files/filelist.xml \
    Основы алгоритмизации/Алгоритм и его свойства/Алгоритм и его свойства.files/image001.png \
    Основы алгоритмизации/Алгоритм и его свойства/Алгоритм и его свойства.files/themedata.thmx \
    Основы алгоритмизации/Алгоритм и его свойства/Алгоритм и его свойства.htm \
    Основы алгоритмизации/Системы счисления/Системы счисления.files/colorschememapping.xml \
    Основы алгоритмизации/Системы счисления/Системы счисления.files/filelist.xml \
    Основы алгоритмизации/Системы счисления/Системы счисления.files/image001.png \
    Основы алгоритмизации/Системы счисления/Системы счисления.files/themedata.thmx \
    Основы алгоритмизации/Системы счисления/Системы счисления.htm \
    Процедурно ориентированный язык программирования/Работа с указателями/Работа с указателями.files/colorschememapping.xml \
    Процедурно ориентированный язык программирования/Работа с указателями/Работа с указателями.files/filelist.xml \
    Процедурно ориентированный язык программирования/Работа с указателями/Работа с указателями.files/themedata.thmx \
    Процедурно ориентированный язык программирования/Работа с указателями/Работа с указателями.htm

