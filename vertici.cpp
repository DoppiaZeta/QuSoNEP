#include "vertici.h"

Vertice::Vertice() {
   x = 0;
   y = 0;
   colore = Qt::red;
}

Vertice::Vertice(int xpos, int ypos) {
   x = xpos;
   y = ypos;
   colore = Qt::red;
}

Vertice::Vertice(const Vertice & v) : QObject(v.parent()) {
   x = v.x;
   y = v.y;
   colore = v.colore;
}

Vertice & Vertice::operator=(const Vertice & v) {
   QObject::setParent(v.parent());
   x = v.x;
   y = v.y;
   colore = v.colore;

   return *this;
}

int Vertice::getPixelCollisione() {
   return pixelCollisione;
}

int Vertice::getX() const {
   return x;
}

int Vertice::getY() const {
   return y;
}

void Vertice::setX(int xpos) {
   x = xpos;
}

void Vertice::setY(int ypos) {
   y = ypos;
}

void Vertice::setXY(int xpos, int ypos) {
   x = xpos;
   y = ypos;
}

bool Vertice::collisione(int xpos, int ypos) const {
   bool xcollisione = false;
   bool ycollisione = false;

   if(xpos > x - pixelCollisione && xpos < x + pixelCollisione)
      xcollisione = true;

   if(ypos > y - pixelCollisione && ypos < y + pixelCollisione)
      ycollisione = true;

   return xcollisione && ycollisione;
}

void Vertice::setColore(const QColor & c) {
   colore = c;
}

QColor Vertice::getColore() const {
   return colore;
}

void Vertice::disegna(int profondita) const {
   QColor c(160, 150, 255);

   glBegin(GL_QUADS);
      // alto sx
      glColor4f(c.redF(), c.greenF(), c.blueF(), 0);
      glVertex3i(x, y + pixelCollisione, profondita);
      glVertex3i(x - pixelCollisione, y + pixelCollisione, profondita);
      glVertex3i(x - pixelCollisione, y, profondita);
      glColor4f(c.redF(), c.greenF(), c.blueF(), 1);
      glVertex3i(x, y, profondita);

      // basso sx
      glColor4f(c.redF(), c.greenF(), c.blueF(), 0);
      glVertex3i(x - pixelCollisione, y, profondita);
      glVertex3i(x - pixelCollisione, y - pixelCollisione, profondita);
      glVertex3i(x, y - pixelCollisione, profondita);
      glColor4f(c.redF(), c.greenF(), c.blueF(), 1);
      glVertex3i(x, y, profondita);

      // basso dx
      glColor4f(c.redF(), c.greenF(), c.blueF(), 0);
      glVertex3i(x + pixelCollisione, y, profondita);
      glVertex3i(x + pixelCollisione, y - pixelCollisione, profondita);
      glVertex3i(x, y - pixelCollisione, profondita);
      glColor4f(c.redF(), c.greenF(), c.blueF(), 1);
      glVertex3i(x, y, profondita);

      // alto dx
      glColor4f(c.redF(), c.greenF(), c.blueF(), 0);
      glVertex3i(x, y + pixelCollisione, profondita);
      glVertex3i(x + pixelCollisione, y + pixelCollisione, profondita);
      glVertex3i(x + pixelCollisione, y, profondita);
      glColor4f(c.redF(), c.greenF(), c.blueF(), 1);
      glVertex3i(x, y, profondita);
   glEnd();
}

int Vertice::pixelCollisione(15);
