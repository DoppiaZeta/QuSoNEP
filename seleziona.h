#ifndef SELEZIONA_H
#define SELEZIONA_H

#include <QtCore>
#include <QtWidgets>
#include "figuraastratta.h"
#include "strumenti.h"
#include "global.h"

/*
  Classe Seleziona
  Finestra che visualizza la lista delle figure attualmente disegnate e ne
  permette sia la selezione (in caso il ray-casting non sia attuabile) sia
  l'eliminazione
*/

class Seleziona : public QDialog{
   Q_OBJECT
   public:
      Seleziona(QList<FiguraAstratta*> *l);

   signals:
      void ridisegna();
      void deseleziona();

   private:
      QTableWidget *tabella;
      QList<FiguraAstratta*> *lista;
      QPushButton *chiudi;

      void caricaTabella();

   public:
      class Cancella : public QWidget {
         public:
            Cancella();
         protected:
            void paintEvent(QPaintEvent *event);
      };

   protected slots:
      void chiudiFinestra();
      void attivaSelezionato(int r, int c);
};

#endif // SELEZIONA_H
