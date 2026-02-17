#include <QApplication>
#include <QProcessEnvironment>
#include <QSurfaceFormat>
#include "mainwidget.h"
#include "global.h"
/*
  MAIN
  inizializza le informazioni in GLOBAL e genera la finestra
*/

namespace {
void configureOpenGLFormat() {
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);

    // Il renderer di QuSoNEP usa OpenGL fixed-pipeline (glMatrixMode, glOrtho, ...).
    // Con driver/Qt moderni può essere creato un Core Profile che disabilita queste API.
    // Per questo di default chiediamo Compatibility Profile.
    const bool modernMode = QProcessEnvironment::systemEnvironment().value(QString("QUSONEP_OPENGL_MODERN")) == QString("1");
    if(modernMode) {
        format.setVersion(3, 3);
        format.setProfile(QSurfaceFormat::CoreProfile);
    } else {
        format.setVersion(2, 1);
        format.setProfile(QSurfaceFormat::CompatibilityProfile);
    }

    QSurfaceFormat::setDefaultFormat(format);
}
}

int main(int argc, char *argv[]) {
    configureOpenGLFormat();

    QApplication a(argc, argv);
    GLOBAL::riempiCombinazioni();
    Widget w;
    w.show();
    return a.exec();
}
