#-------------------------------------------------
#
# Project created by QtCreator 2019-05-28T11:20:30
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlightPlaner
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    drawablemapwidget.cpp \
    addroutedialog.cpp

HEADERS += \
        mainwindow.h \
    dbmanager.h \
    route.h \
    drawablemapwidget.h \
    airport.h \
    airline.h \
    searchalgorithm.h \
    customsearchalgorithm.h \
    dijkstrasearchalgorithm.h \
    breadthfirstsearchalgorithm.h \
    addroutedialog.h

FORMS += \
        mainwindow.ui \
    addroutedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    static/AirlineRoutes.db \
    static/Earthmap.jpg \
    static/Latitude and Longitude of the Earth.png

# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# add the desired if not present
QMAKE_CXXFLAGS_RELEASE *= -O2

# Copy DB File to executable

copydata.commands = $(COPY_DIR) $$PWD/static/AirlineRoutes.db $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
