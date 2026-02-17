#ifndef VERTICI_H
#define VERTICI_H

#include <QtCore>
#include <QtWidgets>
#include <QOpenGLFunctions>

/*
  Classe Vertice
  rappresenta un qualsiasi vertice.
  contiene informazioni sul colore e coordinate.
  fornisce anche un metodo per il disegno OpenGL del vertice e un metodo per
  far capire se il mouse ha cliccato nell'area del vertice o no.
  la dimensione dell'area cliccabile e anche l'immagine del vertice viene
  pilotata dalla variabile pixelCollisione.
*/

class Vertice : public QObject {
   public:
      Vertice();
      Vertice(int xpos, int ypos);
      Vertice(const Vertice & v);
      Vertice & operator=(const Vertice & v);

      int getX() const;
      void setX(int xpos);

      int getY() const;
      void setY(int ypos);

      void setXY(int xpos, int ypos);

      bool collisione(int xpos, int ypos) const;

      virtual void disegna(int profondita) const;

      void setColore(const QColor & c);
      QColor getColore() const;

      static int getPixelCollisione();

   protected:
      int x, y;
      QColor colore;

      static int pixelCollisione;
};

#endif // VERTICI_H
