QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databasestorage.cpp \
    item.cpp \
    itemdragwidget.cpp \
    itemfactory.cpp \
    iteminventory_delegate.cpp \
    iteminventory_model.cpp \
    iteminventory_view.cpp \
    itemmimedata.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp

HEADERS += \
    constants.h \
    databasestorage.h \
    item.h \
    itemdragwidget.h \
    itemfactory.h \
    iteminventory_delegate.h \
    iteminventory_model.h \
    iteminventory_view.h \
    itemmimedata.h \
    mainmenu.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
