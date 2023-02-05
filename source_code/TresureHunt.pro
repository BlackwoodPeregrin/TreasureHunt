QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    viwe/view_game.cpp

HEADERS += \
    controller/controller_game.hpp \
    model/model_game.hpp \
    viwe/style_helper.h \
    viwe/victory_dialog.h \
    viwe/view_game.h

FORMS += \
    viwe/ui/victory_dialog.ui \
    viwe/ui/view_game.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES += \
    icon.ico \
    icon.png \
    icon.rc


win32:RC_FILE = icon.rc

ICON += icon.png
