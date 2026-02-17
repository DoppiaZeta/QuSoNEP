#ifndef FIGURAASTRATTA_H
#define FIGURAASTRATTA_H

#include <QtCore>
#include <QtGui>
#include <math.h>
#include "vertici.h"
#include "global.h"
#include "verticemovimento.h"

/*
  Classe FiguraAstratta
  rappresenta una qualsiasi figura dotata di vertici;
  contiene i metodo per il lampeggio (se selezionato), il disegno di un generico
  poligono o del suo contorno.
  è una classe virtuale pura, bisogna eredirarla e implementare il metodo
  disegna().
  tutti i metodi forniti per il disegno sono virtuali in modo che la sottoclasse
  possa sovrascrivere solo i metodi necessari ed utilizzare quelli forniti negli
  altri casi.
  viene fornito anche un metodo di ray-casting virtuale anch'esso in modo che
  cerchi o altre figure non-poligoni possano essere selezionati con il click
  del mouse.
  le due variabili spessoreLinea e dimensioneLinea si riferiscono
  rispettivamente allo spessore del bordo della figura e allo spessore delle
  linee di lampeggio.
  il metodo disegnaPoligono disegna automaticamente la figura visualizzando
  o il bordo o l'area a seconda dell'immagine.
*/

class FiguraAstratta : public QObject {
   Q_OBJECT
   public:
      FiguraAstratta();

      virtual void disegna(int profondita) const = 0;

      bool addVertice(const Vertice & v);
      QList<Vertice>::iterator primoVertice();
      QList<Vertice>::const_iterator primoVerticeConst() const;
      QList<Vertice>::const_iterator ultimoVertice() const;
      bool cancellaVertice(QList<Vertice>::iterator & iteratore);
      void sostituisciVertice(const QList<Vertice>::iterator & it, const Vertice & v);
      int contaVertici() const;
      virtual bool rayCasting(int x, int y) const;

      void setSelezionato(bool s);
      bool getSelezionato() const;

      void setSpessoreLinea(unsigned short int s);
      unsigned short int getSpessoreLinea() const;

      bool collisioneVertice(int x, int y, Vertice * & v) const;

      virtual void disegnaPoligono(int profondita) const;
      virtual void disegnaArea(int profondita) const;
      virtual void disegnaContorno(int profondita) const;
      virtual void disegnaContornoAperto(int profondita) const;
      virtual void disegnaVertici(int profondita) const;
      virtual void disegnaLampeggio(int profondita) const;

      virtual VerticeMovimento verticeMedia() const;

      GLOBAL::Immagine getImmagine() const;

      static const float dimensioneLinea;

   protected:
      bool selezionato;
      QList<Vertice> vertici;
      float spessoreLinea;

      void esternoXY(const QList<Vertice>::const_iterator & it,
                     int & xpos,
                     int & ypos
                    ) const;

      QColor lampeggioVal;
      GLOBAL::Immagine immagine;

      int minimo(int a, int b) const;
      int massimo(int a, int b) const;

   signals:
      void lampeggia();

   private:
      QTimer lampeggio;
      bool cresciLampeggio;

   protected slots:
      void lampeggiaVertici();
};

#endif // FIGURAASTRATTA_H
