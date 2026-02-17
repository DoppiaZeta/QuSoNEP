#include "global.h"

QList<GLOBAL::Combinazione> GLOBAL::combinazioni;

GLOBAL::Combinazione::Combinazione(Immagine i, int minVertici, int maxVertici, Tipo tipo, const QString & n) {
   immagine = i;
   maxV = maxVertici;
   minV = minVertici;
   t = tipo;
   nome = n;
}

GLOBAL::Immagine GLOBAL::Combinazione::getImmagine() const {
   return immagine;
}

int GLOBAL::Combinazione::getMaxVertici() const {
   return maxV;
}

int GLOBAL::Combinazione::getMinVertici() const {
   return minV;
}

GLOBAL::Tipo GLOBAL::Combinazione::getTipo() const {
   return t;
}

bool GLOBAL::Combinazione::operator==(Immagine i) const {
   return i == immagine;
}

QString GLOBAL::Combinazione::getNome() const {
   return nome;
}

void GLOBAL::riempiCombinazioni() {
   Combinazione Triangolo(TRIANGOLO, 3, 3, AREA, QString("Triangolo"));
   Combinazione Rettangolo(RETTANGOLO, 2, 2, AREA, QString("Rettangolo"));
   Combinazione Cerchio(CERCHIO, 2, 2, AREA, QString("Cerchio"));
   Combinazione CerchioC(CERCHIOC, 2, 2, CONTORNO, QString("Cerchio"));
   Combinazione Poligono(POLIGONO, 3, 0, AREA, QString("Poligono"));
   Combinazione Retta(RETTA, 2, 0, CONTORNO, QString("Linee"));
   Combinazione LineaC(LINEAC, 2, 0, CONTORNO, QString("Linee"));
   Combinazione Punto(PUNTO, 1, 1, CONTORNO, QString("Punto"));

   combinazioni.push_back(Triangolo);
   combinazioni.push_back(Rettangolo);
   combinazioni.push_back(Cerchio);
   combinazioni.push_back(CerchioC);
   combinazioni.push_back(Poligono);
   combinazioni.push_back(Retta);
   combinazioni.push_back(LineaC);
   combinazioni.push_back(Punto);
}

GLOBAL::Combinazione GLOBAL::ottieniInformazioni(GLOBAL::Immagine tipo) {
   Combinazione *c = 0;
   for(int i = 0; i < combinazioni.size(); i++)
      if(combinazioni[i] == tipo)
         c = &combinazioni[i];
   return *c;
}

