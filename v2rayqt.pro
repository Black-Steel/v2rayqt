#-------------------------------------------------
#
# Project created by QtCreator 2019-04-21T11:00:39
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = v2rayqt
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

CONFIG += c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    vmess_link.cpp \
    v2ray_json_config.cpp \
    vmess_subscription.cpp \
    os_clipboard.cpp \
    qt_os_filesystem.cpp \
    dialog_gui_config.cpp \
    gui_config_object.cpp \
    dialog_set_server.cpp \
    qt_json_path.cpp \
    os_system_environment.cpp \
    translate_environment_path.cpp \
    v2ray_core_data.cpp

HEADERS += \
        mainwindow.h \
    vmess_link.h \
    v2ray_json_config.h \
    vmess_subscription.h \
    os_clipboard.h \
    qt_os_filesystem.h \
    dialog_gui_config.h \
    config_constexpr.h \
    gui_config_object.h \
    dialog_set_server.h \
    qt_json_path.h \
    os_system_environment.h \
    translate_environment_path.h \
    v2ray_core_data.h \
    os_define.h

FORMS += \
        mainwindow.ui \
    dialog_gui_config.ui \
    dialog_set_server.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    gui_resource.qrc
