#include "cerchio.h"
#include <cmath>

Cerchio::Cerchio() {
   immagine = GLOBAL::CERCHIO;
}

Cerchio::xypos::xypos(int x, int y) : xpos(x), ypos(y) {
}

void Cerchio::disegna(int profondita) const {
   disegnaPoligono(profondita);
}

void Cerchio::disegnaPoligono(int profondita) const {
   // calcolo dei vertici attorno il perimetro del cerchio
   QList<xypos> listaVertici;
   int xdistanza = vertici[0].getX() - vertici[1].getX();
   int ydistanza = vertici[0].getY() - vertici[1].getY();
   int distanza = qRound(std::sqrt(static_cast<double>(xdistanza * xdistanza + ydistanza * ydistanza)));
   for(int i = 0; i < 360; i++)
      listaVertici.push_back(xypos(vertici[0].getX() + distanza * MathClass::degSine(i),
                                   vertici[0].getY() + distanza * MathClass::degCosine(i)
                                  )
                            );
   listaVertici.push_back(listaVertici[0]);
   
   // lampeggio
   if(selezionato) {
      glLineWidth(dimensioneLinea);
      glBegin(GL_LINE_LOOP);
         glColor4f(lampeggioVal.redF(), lampeggioVal.greenF(),
                   lampeggioVal.blueF(), lampeggioVal.alphaF());
         for(int i = 0; i < listaVertici.size(); i++)
            glVertex3i(listaVertici[i].xpos, listaVertici[i].ypos, profondita + 1);
       glEnd();
       glBegin(GL_LINES);
         glColor4f(lampeggioVal.redF(), lampeggioVal.greenF(),
                   lampeggioVal.blueF(), lampeggioVal.alphaF());
         glVertex3i(vertici[0].getX(), vertici[0].getY(), profondita + 1);
         glVertex3i(vertici[1].getX(), vertici[1].getY(), profondita + 1);
       glEnd();
    }

   // disegno del cerchio
   if(immagine == GLOBAL::CERCHIO) {
      glBegin(GL_TRIANGLE_FAN);
         // primo vertice
         glColor4f(vertici[0].getColore().redF(),
                   vertici[0].getColore().greenF(),
                   vertici[0].getColore().blueF(),
                   vertici[0].getColore().alphaF()
                  );
         glVertex3i(vertici[0].getX(), vertici[0].getY(), profondita);
         // altri vertici
         glColor4f(vertici[1].getColore().redF(),
                   vertici[1].getColore().greenF(),
                   vertici[1].getColore().blueF(),
                   vertici[1].getColore().alphaF()
                  );
         for(int i = 0; i < listaVertici.size(); i++)
         glVertex3i(listaVertici[i].xpos, listaVertici[i].ypos, profondita);
      glEnd();
   } else {
      glLineWidth(spessoreLinea);
      glBegin(GL_LINE_LOOP);
         glColor4f(vertici[0].getColore().redF(),
             vertici[0].getColore().greenF(),
             vertici[0].getColore().blueF(),
             vertici[0].getColore().alphaF()
            );
         for(int i = 0; i < listaVertici.size(); i++)
            glVertex3i(listaVertici[i].xpos, listaVertici[i].ypos, profondita);
      glEnd();
   }

   disegnaVertici(profondita);
}

void Cerchio::setTipo(tipoCerchio t) {
   if(t == CERCHIO_CONTORNO)
      immagine = GLOBAL::CERCHIOC;
   else
      immagine = GLOBAL::CERCHIO;
}

bool Cerchio::rayCasting(int x, int y) const {
   int xdistanza = vertici[0].getX() - vertici[1].getX();
   int ydistanza = vertici[0].getY() - vertici[1].getY();
   int raggio = qRound(std::sqrt(static_cast<double>(xdistanza * xdistanza + ydistanza * ydistanza)));

   xdistanza = vertici[0].getX() - x;
   ydistanza = vertici[0].getY() - y;
   int mouseRaggio = qRound(std::sqrt(static_cast<double>(xdistanza * xdistanza + ydistanza * ydistanza)));

   if(mouseRaggio <= raggio)
      return true;
   else
      return false;
}

VerticeMovimento Cerchio::verticeMedia() const {
   return VerticeMovimento(vertici[0].getX(), vertici[0].getY());
}
