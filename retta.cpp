#include "retta.h"

Retta::Retta() {
   immagine = GLOBAL::RETTA;
}

void Retta::disegna(int profondita) const {
   disegnaLampeggio(profondita);
   disegnaContornoAperto(profondita);
   disegnaVertici(profondita);
}

void Retta::disegnaLampeggio(int profondita) const {
   if(selezionato) {
      glLineWidth(dimensioneLinea);
      glBegin(GL_LINE_STRIP);
         QList<Vertice>::const_iterator it(primoVerticeConst());
         while(it != vertici.end()) {
            glColor4f(lampeggioVal.redF(), lampeggioVal.greenF(),
                      lampeggioVal.blueF(), lampeggioVal.alphaF());
            glVertex3i(it->getX(), it->getY(), profondita + 1);
            it++;
         }
       glEnd();
    }
}
