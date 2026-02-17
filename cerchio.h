#ifndef CERCHIO_H
#define CERCHIO_H

#include <QtCore>
#include <QOpenGLFunctions>
#include "mathclass.h"
#include "figuraastratta.h"
#include "global.h"

/*
  Classe Cerchio
  eredita da FiguraAstratta e rappresenta un cerchio pieno o il contorno
*/

class Cerchio : public FiguraAstratta {
   public:
      Cerchio();

      enum tipoCerchio {CERCHIO_NORMALE, CERCHIO_CONTORNO};
      void setTipo(tipoCerchio t);

      void disegna(int profondita) const;
      void disegnaPoligono(int profondita) const;
      bool rayCasting(int x, int y) const;
      VerticeMovimento verticeMedia() const;

   private:
      class xypos {
      public:
         xypos(int x, int y);
         int xpos, ypos;
   };
};

#endif // CERCHIO_H
