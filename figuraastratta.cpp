#include "figuraastratta.h"

FiguraAstratta::FiguraAstratta() {
   selezionato = false;
   spessoreLinea = 3.0;
   lampeggioVal = Qt::white;
   cresciLampeggio = false;
   immagine = GLOBAL::TRIANGOLO;

   connect(&lampeggio, SIGNAL(timeout()), this, SLOT(lampeggiaVertici()));
}

const float FiguraAstratta::dimensioneLinea(4.0);

QList<Vertice>::iterator FiguraAstratta::primoVertice() {
   return vertici.begin();
}

QList<Vertice>::const_iterator FiguraAstratta::primoVerticeConst() const {
   return vertici.begin();
}

QList<Vertice>::const_iterator FiguraAstratta::ultimoVertice() const {
   return vertici.end();
}

bool FiguraAstratta::addVertice(const Vertice & v) {
   int maxV = GLOBAL::ottieniInformazioni(immagine).getMaxVertici();
   if(vertici.size() == maxV && maxV != 0)
      return false;
   else {
      vertici.push_back(v);
      return true;
   }
}

bool FiguraAstratta::cancellaVertice(QList<Vertice>::iterator & iteratore) {
   if(vertici.size() <= GLOBAL::ottieniInformazioni(immagine).getMinVertici())
      return false;
   else {
      iteratore = vertici.erase(iteratore);
      return true;
   }
}

bool FiguraAstratta::collisioneVertice(int x, int y, Vertice * & v) const {
   bool trovato = false;
   for(int i = 0; i < vertici.size() && !trovato; i++)
      if(vertici[i].collisione(x, y)) {
         trovato = true;
         v = const_cast<Vertice*>(&vertici[i]);
      }
   return trovato;
}

void FiguraAstratta::setSelezionato(bool s) {
   selezionato = s;

   if(s)
      lampeggio.start(75);
   else {
      lampeggio.stop();
      cresciLampeggio = false;
      lampeggioVal = Qt::white;
   }

}

bool FiguraAstratta::getSelezionato() const {
   return selezionato;
}

void FiguraAstratta::setSpessoreLinea(unsigned short int s) {
   spessoreLinea = s;
}

unsigned short int FiguraAstratta::getSpessoreLinea() const {
   return spessoreLinea;
}

void FiguraAstratta::lampeggiaVertici() {
   if(cresciLampeggio)
      if(lampeggioVal.alpha() > 200)
         cresciLampeggio = false;
      else
         lampeggioVal.setAlpha(lampeggioVal.alpha() + 18);
   else
      if(lampeggioVal.alpha() < 75)
         cresciLampeggio = true;
      else
         lampeggioVal.setAlpha(lampeggioVal.alpha() - 18);
   emit lampeggia();
}

void FiguraAstratta::disegnaPoligono(int profondita) const {

   disegnaLampeggio(profondita);

   if(GLOBAL::ottieniInformazioni(immagine).getTipo() == GLOBAL::AREA)
      disegnaArea(profondita);
   else
      disegnaContorno(profondita);

   disegnaVertici(profondita);
}

void FiguraAstratta::disegnaArea(int profondita) const {
   glBegin(GL_POLYGON);
      for(int i = 0; i < vertici.size(); i++) {
         glColor4f(vertici[i].getColore().redF(),
                   vertici[i].getColore().greenF(),
                   vertici[i].getColore().blueF(),
                   vertici[i].getColore().alphaF()
                  );
         glVertex3i(vertici[i].getX(), vertici[i].getY(), profondita);
      }
   glEnd();
}

void FiguraAstratta::disegnaContorno(int profondita) const {
   glLineWidth(spessoreLinea);
   glBegin(GL_LINE_LOOP);
      for(int i = 0; i < vertici.size(); i++) {
         glColor4f(vertici[i].getColore().redF(),
                   vertici[i].getColore().greenF(),
                   vertici[i].getColore().blueF(),
                   vertici[i].getColore().alphaF()
                  );
         glVertex3i(vertici[i].getX(), vertici[i].getY(), profondita);
      }
   glEnd();
}

void FiguraAstratta::disegnaContornoAperto(int profondita) const {
   glLineWidth(spessoreLinea);
   glBegin(GL_LINE_STRIP);
      for(int i = 0; i < vertici.size(); i++) {
         glColor4f(vertici[i].getColore().redF(),
                   vertici[i].getColore().greenF(),
                   vertici[i].getColore().blueF(),
                   vertici[i].getColore().alphaF()
                  );
         glVertex3i(vertici[i].getX(), vertici[i].getY(), profondita);
      }
   glEnd();
}

void FiguraAstratta::disegnaVertici(int profondita) const {
   if(selezionato)
      for(int i = 0; i < vertici.size(); i++)
         vertici[i].disegna(profondita + 2);
}

void FiguraAstratta::disegnaLampeggio(int profondita) const {
   if(selezionato) {
      glLineWidth(dimensioneLinea);
      glBegin(GL_LINE_LOOP);
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

GLOBAL::Immagine FiguraAstratta::getImmagine() const {
   return immagine;
}

int FiguraAstratta::contaVertici() const {
   return vertici.size();
}

int FiguraAstratta::minimo(int a, int b) const {
   if(a > b)
      return b;
   else
      return a;
}

int FiguraAstratta::massimo(int a, int b) const {
   if(a < b)
      return b;
   else
      return a;
}

bool FiguraAstratta::rayCasting(int x, int y) const {
   int conta = 0;
   Vertice const *v1, *v2;
   double tmp;

   if(vertici.size() <= 2)
      return false;

   v1 = &vertici[0];

   for(int i = 1; i <= vertici.size(); i++) {
      v2 = &vertici[i % vertici.size()];
      if(y > minimo(v1->getY(), v2->getY()))
         if(y <= massimo(v1->getY(), v2->getY()))
            if(x <= massimo(v1->getX(), v2->getX()))
               if(v1->getY() != v2->getY()) {
                  tmp = (y - v1->getY()) * (v2->getX() - v1->getX()) / (v2->getY() - v1->getY()) + v1->getX();
                  if (v1->getX() == v2->getX() || x <= tmp)
                     conta++;
               }
      v1 = v2;
   }

   if(conta % 2 == 0)
      return false;
   else
      return true;
}

VerticeMovimento FiguraAstratta::verticeMedia() const {
   int x = 0;
   int y = 0;
   for(int i = 0; i < vertici.size(); i++) {
      x += vertici[i].getX();
      y += vertici[i].getY();
   }
   return VerticeMovimento(x / vertici.size(), y / vertici.size());
}

