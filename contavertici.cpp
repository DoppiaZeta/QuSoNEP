#include "contavertici.h"

namespace {
QPoint mousePoint(const QMouseEvent *evento) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
   return evento->position().toPoint();
#else
   return evento->pos();
#endif
}
}

Contavertici::Contavertici() {
   coordinate = 0;
   setFixedHeight(50);
   xoffset = 30;
   yoffset = 20;
}

void Contavertici::aggiornaVertici(QList<Vertice> *coo) {
   coordinate = coo;
   repaint();
}

void Contavertici::paintEvent(QPaintEvent *event) {
   event->ignore();
   QPainter paint;
   paint.begin(this);
   paint.setRenderHint(QPainter::Antialiasing, true);
      paint.setPen(Qt::black);
      paint.drawText(5, 15, QString("Numero di vertici:"));
      paint.setPen(Qt::red);
      if(coordinate == 0)
         paint.drawText(5, 30, QChar('0'));
      else {
         paint.drawText(5, 30, QString::number(coordinate->size()));
         for(int i = 0; i < coordinate->size(); i++) {
            paint.setBrush(QBrush(QColor(0xcc, 0xcc, 0xff, 0xff)));
            paint.setPen(Qt::blue);
            QPolygon p;
            p.push_back(QPoint(10 + xoffset + 80 * i, yoffset));
            p.push_back(QPoint(xoffset + 80 * i, yoffset + 10));
            p.push_back(QPoint(10 + xoffset + 80 * i, yoffset + 20));
            p.push_back(QPoint(20 + xoffset + 80 * i, yoffset + 10));
            paint.drawPolygon(p);
            paint.setPen(QColor(0xff, 0x44, 0x44, 0xff));
            paint.drawLine(xoffset + 80 * i, yoffset, 20 + xoffset + 80 * i, yoffset + 20);
            paint.drawLine(xoffset + 80 * i, yoffset + 20, 20 + xoffset + 80 * i, yoffset);
            paint.setPen(Qt::black);
            paint.drawText(xoffset + 80 * i + 25, yoffset + 8, QString("x: %1").arg(coordinate->operator[](i).getX()));
            paint.drawText(xoffset + 80 * i + 25, yoffset + 22, QString("y: %1").arg(coordinate->operator[](i).getY()));
         }
      }
   paint.end();
}

void Contavertici::mouseReleaseEvent(QMouseEvent * evento) {
   int x = mousePoint(evento).x();
   int y = mousePoint(evento).y();
   x -= xoffset;
   y -= yoffset;
   int i = x / 80;
   if(y >= 0 && i >= 0 && i < coordinate->size()) {
      QList<Vertice>::iterator it = coordinate->begin();
      for(int k = 0; k < i; k++)
         it++;
      coordinate->erase(it);
      emit ridisegna();
      repaint();
   }
}
