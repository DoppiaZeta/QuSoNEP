#include <QApplication>
#include "mainwidget.h"
#include "global.h"
/*
  MAIN
  inizializza le informazioni in GLOBAL e genera la finestra
*/

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GLOBAL::riempiCombinazioni();
    Widget w;
    w.show();
    return a.exec();
}
