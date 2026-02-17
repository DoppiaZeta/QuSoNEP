#ifndef LINEAC_H
#define LINEAC_H

#include <QtCore>
#include <QOpenGLFunctions>
#include "figuraastratta.h"
#include "global.h"

/*
  Classe Lineac
  eredita da FiguraAstratta e rappresenta una serie di linee chiuse
*/

class Lineac : public FiguraAstratta {
   public:
      Lineac();

      void disegna(int profondita) const;
};

#endif // LINEAC_H
