#ifndef RETTA_H
#define RETTA_H

#include <QtCore>
#include <QtOpenGL>
#include "figuraastratta.h"
#include "global.h"

/*
  Classe Retta
  eredita da FiguraAstratta e rappresenta una serie di linee aperte
*/

class Retta : public FiguraAstratta {
   public:
      Retta();

      void disegna(int profondita) const;
      void disegnaLampeggio(int profondita) const;
};

#endif // RETTA_H
