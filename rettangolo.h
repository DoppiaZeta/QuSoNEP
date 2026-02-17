#ifndef RETTANGOLO_H
#define RETTANGOLO_H

#include <QtCore>
#include <QtOpenGL>
#include "figuraastratta.h"
#include "global.h"

/*
  Classe Rettangolo
  eredita da FiguraAstratta e rappresenta un rettangolo di 2 vertici
*/

class Rettangolo : public FiguraAstratta {
   public:
      Rettangolo();

      void disegna(int profondita) const;
      void disegnaLampeggio(int profondita) const;
      void disegnaArea(int profondita) const;
      bool rayCasting(int x, int y) const;
};

#endif // RETTANGOLO_H
