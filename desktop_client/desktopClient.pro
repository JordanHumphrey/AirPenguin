QT += core \
      network \
      xml \
      multimedia \
      multimediawidgets \
      widgets \
      gui

CONFIG += c++11

TARGET = desktopClient
CONFIG += console
CONFIG -= app_bundle

QT += script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000

TEMPLATE = app

SOURCES += main.cpp \
    qtinterface/volumeslider.cpp \
    qtinterface/scrubber.cpp \
    qtinterface/playbutton.cpp \
    qtinterface/stopbutton.cpp \
    qtinterface/fullscreenbutton.cpp \
    qtinterface/videoframe.cpp \
    qtinterface/mutebutton.cpp \
    qtinterface/error.cpp \
    ui/penguinview.cpp \
    player/localplayer.cpp \
    player/castplayer.cpp \     
    vlc/args.cpp \
    vlc/audio.cpp \
    vlc/media.cpp \
    vlc/mediaplayer.cpp \
    vlc/networkmanager.cpp \
    vlc/vlcinstance.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    vlc/vlcinstance.h \
    vlc/audio.h \
    vlc/networkmanager.h \
    vlc/mediaplayer.h \
    vlc/media.h \
    vlc/args.h \
    player/localplayer.h \
    player/castplayer.h \
    qtinterface/volumeslider.h \
    qtinterface/scrubber.h \
    qtinterface/playbutton.h \
    qtinterface/stopbutton.h \
    qtinterface/mutebutton.h \
    qtinterface/fullscreenbutton.h \
    qtinterface/videoframe.h \
    qtinterface/error.h \
    ui/penguinview.h \
    ui_penguinview.h \
    vlc/state.h


DISTFILES += \
    ui/resources/airPenguin.jpg \
    ui/resources/peng.jpg \
    ui/resources/pengu.jpg \
    ui/resources/connect_1.png \
    ui/resources/help_1.png \
    ui/resources/open_1.png \
    ui/resources/options_1.png \
    ui/resources/options_2.png \
    ui/resources/plus.png \
    ui/resources/recent_1.png \
    ui/resources/Peng1rev1.2.svg \
    ui/resources/QTDark.css

FORMS += \
    ui/penguinview.ui



RESOURCES += \
    ui/resources/airpenguin.qrc

macx: LIBS += -L$$PWD/lib/ -lvlc.5
else:unix: LIBS += -L$$PWD/lib/ -lvlc

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
