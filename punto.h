#ifndef PUNTO_H
#define PUNTO_H

#include <QtCore>
#include <QtOpenGL>
#include "figuraastratta.h"
#include "global.h"

/*
  Classe Punto
  eredita da FiguraAstratta e rappresenta un punto(pixel) nello schermo
*/

class Punto : public FiguraAstratta {
   public:
      Punto();

      void disegna(int profondita) const;
      void disegnaContorno(int profondita) const;
};

#endif // PUNTO_H
