#ifndef TRIANGOLO_H
#define TRIANGOLO_H

#include <QtCore>
#include <QOpenGLFunctions>
#include "figuraastratta.h"
#include "global.h"

/*
  Classe Triangolo
  eredita da FiguraAstratta e rappresenta un triangolo
*/

class Triangolo : public FiguraAstratta {
   public:
      Triangolo();

      void disegna(int profondita) const;
};

#endif // TRIANGOLO_H
