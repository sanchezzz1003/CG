QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    glabstractpainting.cpp \
    glcuboid.cpp \
    glcylinder.cpp \
    glfigureengine.cpp \
    gllight.cpp \
    glsphere.cpp \
    glwidget.cpp \
    lightsettingswidget.cpp \
    main.cpp \
    viewwidget.cpp \
    widget.cpp

HEADERS += \
    glabstractpainting.h \
    glcuboid.h \
    glcylinder.h \
    glfigureengine.h \
    gllight.h \
    glsphere.h \
    glwidget.h \
    lightsettingswidget.h \
    viewwidget.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lopengl32
