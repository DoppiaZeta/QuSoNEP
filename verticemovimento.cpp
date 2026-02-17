#include "verticemovimento.h"

VerticeMovimento::VerticeMovimento(int x, int y) : Vertice(x, y) {

}

void VerticeMovimento::disegna(int profondita) const {
   QColor c(0x33, 0xcc, 0x55);
   profondita = profondita;

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
