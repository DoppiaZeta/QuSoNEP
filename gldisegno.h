#ifndef GLDISEGNO_H
#define GLDISEGNO_H

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include <QtSql>
#include "figuraastratta.h"
#include "vertici.h"
#include "triangolo.h"
#include "rettangolo.h"
#include "cerchio.h"
#include "poligono.h"
#include "retta.h"
#include "punto.h"
#include "lineac.h"
#include "global.h"
#include "seleziona.h"
#include "verticemovimento.h"
#include "colori.h"
#include "impostavertice.h"

/*
  Classe GLDisegno
  è il widget che utilizza OpenGL mostrando il disegno.
  fornisce metodi per apertura e salvataggio su file (via SQL Lite).
  ottiene le informazioni dagli altri widget tramite slot rendendolo
  indipendente dal programma.
  contiene la lista delle figure, il colore attuale, la figura attuale e
  i vertici generati durante la costruzione di una figura.
  iteragisce con l'utente tramite il click del mouse.
*/

class GLDisegno : public QGLWidget {
   Q_OBJECT
   public:
      GLDisegno();
      ~GLDisegno();

      void initializeGL();
      void resizeGL(int w, int h);
      void paintGL();

      QColor getColoreAttuale() const;

      void premiTasto(QKeyEvent * evento);
      void rilasciaTasto(QKeyEvent * evento);


   public slots:
      void setColoreAttuale(const QColor & c);
      void setStrumentoAttuale(const GLOBAL::Immagine & i);
      void chiudiPercorso();
      void deseleziona();
      void ridisegna();
      void listaOggetti();
      void attivaSelezione();
      void cambiaSfondo(const QColor & c);
      void finestraColoreSfondo();
      void salva();
      void apri();

   protected:
      QList<FiguraAstratta*> figure;

      void mouseReleaseEvent(QMouseEvent * evento);
      void mouseMoveEvent(QMouseEvent * evento);
      void mousePressEvent(QMouseEvent * evento);
      void mouseDoubleClickEvent(QMouseEvent * evento);

      Vertice * verticeInMovimento;
      QList<Vertice> coordinate;
      bool prendiCoordinate;

      QColor coloreAttuale;
      GLOBAL::Immagine strumentoAttuale;
      QColor coloreSfondo;

      bool attivaRayCasting;
      VerticeMovimento *centro;

      QSqlDatabase db;

   signals:
      void coordinateAggiornate(QList<Vertice>* v);
};

#endif // GLDISEGNO_H
