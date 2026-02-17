#ifndef POLIGONO_H
#define POLIGONO_H

#include <QtCore>
#include <QtOpenGL>
#include "figuraastratta.h"
#include "global.h"

/*
  Classe Poligono
  eredita da FiguraAstratta e rappresenta un poligono pieno (area)
*/

class Poligono : public FiguraAstratta {
   public:
      Poligono();

      void disegna(int profondita) const;
};

#endif // POLIGONO_H
