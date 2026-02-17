#ifndef CONTAVERTICI_H
#define CONTAVERTICI_H

#include <QtCore>
#include <QtGui>
#include "vertici.h"

/*
  Classe Contavertici
  è la barra in basso che mostra i vertici mentre si crea una figura;
  è possibile cliccare nei vertici per cancellari (in caso di errore)
*/

class Contavertici : public QWidget {
   Q_OBJECT
   public:
      Contavertici();

   private:
      QList<Vertice> *coordinate;
      int xoffset;
      int yoffset;

   protected:
      void paintEvent(QPaintEvent *event);
      void mouseReleaseEvent(QMouseEvent * evento);

   public slots:
      void aggiornaVertici(QList<Vertice> *coo);

   signals:
      void ridisegna();
};

#endif // CONTAVERTICI_H
