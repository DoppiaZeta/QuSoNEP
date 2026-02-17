#ifndef STRUMENTI_H
#define STRUMENTI_H

#include <QtWidgets>
#include <QtCore>
#include "global.h"

/*
  Classe Strumenti
  widget che permette di sceglere una figura da disegnare.
  fornisce anche strumenti per deselezionare, attivare il ray-casting e
  aprire la finestra che mostra tutte le figure disegnate.
*/

class Strumenti : public QDialog {
   Q_OBJECT
   public:
      class Attuale;

      Strumenti(QWidget *parent = 0);

   signals:
      void nuovoStrumento(const GLOBAL::Immagine & i);
      void chiudiPercorso();
      void deselezionaTutto();
      void listaOggetti();
      void attivaRayCasting();

   protected:
      QPushButton *triangolo;
      QPushButton *rettangolo;
      QPushButton *poligono;
      QPushButton *cerchio;
      QPushButton *cerchioC;
      QPushButton *linee;
      QPushButton *lineeC;
      QPushButton *punto;

      QPushButton *chiudi;
      QPushButton *seleziona;
      QPushButton *deseleziona;
      QPushButton *oggetti;

      Attuale *immagineAttuale;

   public:
      // classe Attuale che mostra un'anteprima
      class Attuale : public QWidget {
         public:
            Attuale();
            void setImmagine(GLOBAL::Immagine i);
         protected:
            GLOBAL::Immagine attuale;
            void paintEvent(QPaintEvent *event);
      };

   private slots:
      void clickTriangolo();
      void clickRettangolo();
      void clickPoligono();
      void clickCerchio();
      void clickCerchioC();
      void clickLinee();
      void clickLineeC();
      void clickPunto();

      void clickChiudi();
      void clickDeseleziona();
      void clickOggetti();
      void clickSeleziona();
};

#endif // STRUMENTI_H
