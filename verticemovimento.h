#ifndef VERTICEMOVIMENTO_H
#define VERTICEMOVIMENTO_H

#include <QtCore>
#include <QtWidgets>
#include "vertici.h"

/*
  Classe VerticeMovimento
  eredita da Vertice e rappresenta un vertice speciale (attivabile con SHIFT)
  che sposta tutti i vertici contemporaneamente spostando di conseguenza tutta
  la figura.
  Lo spostamento viene fatto in GLDisengo
*/

class VerticeMovimento : public Vertice {
   public:
       VerticeMovimento(int x, int y);
       void disegna(int profondita) const;
};

#endif // VERTICEMOVIMENTO_H
