TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += DBUSER DBPASS

INCLUDEPATH += /usr/local/include/tango \
            /usr/local/include \
            /usr/include/mysql

SOURCES += main.cpp \
*.cpp \
*.h 

