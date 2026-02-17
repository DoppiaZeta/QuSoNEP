#include "rettangolo.h"

Rettangolo::Rettangolo() {
   immagine = GLOBAL::RETTANGOLO;
}

void Rettangolo::disegna(int profondita) const {
   disegnaPoligono(profondita);
}

void Rettangolo::disegnaLampeggio(int profondita) const {
   if(selezionato) {
      glLineWidth(dimensioneLinea);
      glBegin(GL_LINE_LOOP);
         glColor4f(lampeggioVal.redF(), lampeggioVal.greenF(),
                   lampeggioVal.blueF(), lampeggioVal.alphaF());
         glVertex3i(vertici[0].getX(), vertici[0].getY(), profondita + 1);
         glVertex3i(vertici[0].getX(), vertici[1].getY(), profondita + 1);
         glVertex3i(vertici[1].getX(), vertici[1].getY(), profondita + 1);
         glVertex3i(vertici[1].getX(), vertici[0].getY(), profondita + 1);
       glEnd();
    }
}

void Rettangolo::disegnaArea(int profondita) const {
      glBegin(GL_POLYGON);
      glColor4f(vertici[0].getColore().redF(),
                vertici[0].getColore().greenF(),
                vertici[0].getColore().blueF(),
                vertici[0].getColore().alphaF()
               );
      glVertex3i(vertici[0].getX(), vertici[0].getY(), profondita);
      glVertex3i(vertici[0].getX(), vertici[1].getY(), profondita);
      glColor4f(vertici[1].getColore().redF(),
                vertici[1].getColore().greenF(),
                vertici[1].getColore().blueF(),
                vertici[1].getColore().alphaF()
               );
      glVertex3i(vertici[1].getX(), vertici[1].getY(), profondita);
      glVertex3i(vertici[1].getX(), vertici[0].getY(), profondita);
   glEnd();
}

bool Rettangolo::rayCasting(int x, int y) const {
   bool xcollisione = false;
   bool ycollisione = false;
   int maxX = massimo(vertici[0].getX(), vertici[1].getX());
   int minX = minimo(vertici[0].getX(), vertici[1].getX());
   int maxY = massimo(vertici[0].getY(), vertici[1].getY());
   int minY = minimo(vertici[0].getY(), vertici[1].getY());

   if(x > minX && x < maxX)
      xcollisione = true;

   if(y > minY && y < maxY)
      ycollisione = true;

   return xcollisione && ycollisione;
}
