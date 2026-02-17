#include "punto.h"

Punto::Punto() {
   immagine = GLOBAL::PUNTO;
   spessoreLinea = 4.0;
}

void Punto::disegna(int profondita) const {
   disegnaContorno(profondita);
   disegnaVertici(profondita);
}

void Punto::disegnaContorno(int profondita) const {
   glLineWidth(spessoreLinea);
   glBegin(GL_POINT);
      glColor4f(vertici[0].getColore().redF(),
                vertici[0].getColore().greenF(),
                vertici[0].getColore().blueF(),
                vertici[0].getColore().alphaF()
               );
      glVertex3i(vertici[0].getX(), vertici[0].getY(), profondita);
   glEnd();
}

