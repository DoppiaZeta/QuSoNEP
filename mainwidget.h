#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets>
#include <QOpenGLFunctions>
#include "gldisegno.h"
#include "strumenti.h"
#include "colori.h"
#include "contavertici.h"

/*
  Classe Widget(MainWindow)
  rappresenta la finestra principale del programma che contiene tutti gli altri
  widget.
  attiva le connessioni tra i widget e i menù.
*/

class Widget : public QMainWindow {
   Q_OBJECT

   public:
      Widget(QWidget *parent = 0);
      ~Widget();

   private:
      QGridLayout *griglia;
      GLDisegno *disegno;
      Strumenti *strumenti;
      Colori *colori;
      Contavertici *contavertici;

      class aboutQuSoNEP : public QDialog {
         public:
            aboutQuSoNEP(QWidget *parent = 0);
      };

   protected:
      void keyPressEvent(QKeyEvent * evento);
      void keyReleaseEvent(QKeyEvent * evento);

   public slots:
      void QuSoNEP();
};

#endif // MAINWIDGET_H
