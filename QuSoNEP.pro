# -------------------------------------------------
# Project created by QtCreator 2009-02-25T16:46:49
# -------------------------------------------------
QT += widgets
QT += openglwidgets
QT += opengl
QT += sql

win32:LIBS += -lopengl32

TARGET = QuSoNEP
TEMPLATE = app
SOURCES += main.cpp \
    mainwidget.cpp \
    gldisegno.cpp \
    figuraastratta.cpp \
    vertici.cpp \
    triangolo.cpp \
    impostavertice.cpp \
    rettangolo.cpp \
    cerchio.cpp \
    mathclass.cpp \
    strumenti.cpp \
    colori.cpp \
    contavertici.cpp \
    global.cpp \
    poligono.cpp \
    retta.cpp \
    lineac.cpp \
    seleziona.cpp \
    punto.cpp \
    verticemovimento.cpp
HEADERS += mainwidget.h \
    gldisegno.h \
    figuraastratta.h \
    vertici.h \
    triangolo.h \
    impostavertice.h \
    rettangolo.h \
    cerchio.h \
    mathclass.h \
    strumenti.h \
    colori.h \
    contavertici.h \
    global.h \
    poligono.h \
    retta.h \
    lineac.h \
    seleziona.h \
    punto.h \
    verticemovimento.h

OTHER_FILES += \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable/icon.png \
    android/res/drawable/logo.png \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-et/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-el/strings.xml \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/AndroidManifest.xml \
    android/version.xml
