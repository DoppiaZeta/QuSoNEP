#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtCore>

/*
  Nomespazio GLOBAL
  contiene tutte le informazioni comuni a tutte le classi.
  contiene una classe Combinazione che fornisce con semplicità ogni informazione
  utile inerente le immagini.
*/

namespace GLOBAL {
   enum Immagine {RETTANGOLO, CERCHIO, TRIANGOLO, POLIGONO, RETTA, PUNTO, LINEAC, CERCHIOC};
   enum Tipo {CONTORNO, AREA};

   class Combinazione {
      public:
         Combinazione(Immagine i, int minVertici, int maxVerticim, Tipo tipo, const QString & n);
         Immagine getImmagine() const;
         int getMinVertici() const;
         int getMaxVertici() const;
         Tipo getTipo() const;
         bool operator==(Immagine i) const;
         QString getNome() const;

      private:
         Immagine immagine;
         int minV, maxV;
         Tipo t;
         QString nome;
   };

   extern QList<Combinazione> combinazioni;
   void riempiCombinazioni();
   Combinazione ottieniInformazioni(Immagine tipo);
}

#endif // GLOBAL_H
