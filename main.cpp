#include <QApplication>
#include <QSurfaceFormat>
#include "mainwidget.h"
#include "global.h"
/*
  MAIN
  inizializza le informazioni in GLOBAL e genera la finestra
*/

int main(int argc, char *argv[]) {
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(2, 1);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(format);

    QApplication a(argc, argv);
    GLOBAL::riempiCombinazioni();
    Widget w;
    w.show();
    return a.exec();
}
