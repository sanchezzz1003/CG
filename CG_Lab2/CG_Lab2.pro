QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractpaintitng3d.cpp \
    abstractpolygon3d.cpp \
    main.cpp \
    polygon3d.cpp \
    pyramidclass.cpp \
    rectpolygon3d.cpp \
    scenemodifier.cpp \
    transform.cpp \
    transformer.cpp \
    widget3d.cpp

HEADERS += \
    abstractpaintitng3d.h \
    abstractpolygon3d.h \
    polygon3d.h \
    pyramidclass.h \
    rectpolygon3d.h \
    scenemodifier.h \
    transform.h \
    transformer.h \
    widget3d.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
