#include "strumenti.h"

Strumenti::Strumenti(QWidget *parent)
      : QDialog(parent) {
   setWindowTitle(QString("Figure e strumenti"));
   QGridLayout *griglia = new QGridLayout;
   setLayout(griglia);
   setMinimumWidth(180);
   setFixedHeight(500);
   int pos = 0;

   triangolo = new QPushButton(QString("Triangolo"));
   griglia->addWidget(triangolo, pos++, 0, 1, 2);
   connect(triangolo, SIGNAL(clicked()), SLOT(clickTriangolo()));

   rettangolo = new QPushButton(QString("Rettangolo"));
   griglia->addWidget(rettangolo, pos++, 0, 1, 2);
   connect(rettangolo, SIGNAL(clicked()), SLOT(clickRettangolo()));

   poligono = new QPushButton(QString("Poligono"));
   griglia->addWidget(poligono, pos++, 0, 1, 2);
   connect(poligono, SIGNAL(clicked()), SLOT(clickPoligono()));

   cerchio = new QPushButton(QString("Cerchio (pieno)"));
   griglia->addWidget(cerchio, pos++, 0, 1, 2);
   connect(cerchio, SIGNAL(clicked()), SLOT(clickCerchio()));

   cerchioC = new QPushButton(QString("Cerchio (bordo)"));
   griglia->addWidget(cerchioC, pos++, 0, 1, 2);
   connect(cerchioC, SIGNAL(clicked()), SLOT(clickCerchioC()));

   linee = new QPushButton(QString("Linee (Aperte)"));
   griglia->addWidget(linee, pos++, 0, 1, 2);
   connect(linee, SIGNAL(clicked()), SLOT(clickLinee()));

   lineeC = new QPushButton(QString("Linee (Chiuse)"));
   griglia->addWidget(lineeC, pos++, 0, 1, 2);
   connect(lineeC, SIGNAL(clicked()), SLOT(clickLineeC()));

   punto = new QPushButton(QString("Punto"));
   griglia->addWidget(punto, pos++, 0, 1, 2);
   connect(punto, SIGNAL(clicked()), SLOT(clickPunto()));

   immagineAttuale = new Attuale;
   immagineAttuale->setMinimumSize(80, 60);
   griglia->addWidget(immagineAttuale, pos++, 0, 1, 2, Qt::AlignCenter);

   chiudi = new QPushButton(QString("Fine/Chiudi"));
   griglia->addWidget(chiudi, pos++, 0, 1, 2);
   connect(chiudi, SIGNAL(clicked()), SLOT(clickChiudi()));

   seleziona = new QPushButton(QString("Seleziona"));
   griglia->addWidget(seleziona, pos++, 0, 1, 2);
   connect(seleziona, SIGNAL(clicked()), SLOT(clickSeleziona()));

   deseleziona = new QPushButton(QString("Deseleziona"));
   griglia->addWidget(deseleziona, pos++, 0, 1, 2);
   connect(deseleziona, SIGNAL(clicked()), SLOT(clickDeseleziona()));

   oggetti = new QPushButton(QString("Lista oggetti"));
   griglia->addWidget(oggetti, pos++, 0, 1, 2);
   connect(oggetti, SIGNAL(clicked()), SLOT(clickOggetti()));

   chiudi->setEnabled(false);
}

Strumenti::Attuale::Attuale() {
   attuale = GLOBAL::TRIANGOLO;
   setMinimumHeight(40);
   setMinimumWidth(50);
}

void Strumenti::Attuale::setImmagine(GLOBAL::Immagine i) {
   attuale = i;
   repaint();
}

void Strumenti::Attuale::paintEvent(QPaintEvent *event) {
   event->ignore();
   QPainter paint;
   paint.begin(this);
   paint.setRenderHint(QPainter::Antialiasing, true);
      paint.setPen(Qt::transparent);
      paint.setBrush(QBrush(QColor(0x0, 0x88, 0x22, 0xff)));
      int xoffset = 5;
      int yoffset = 5;
      switch(attuale) {
         case GLOBAL::PUNTO:
            paint.setBrush(Qt::blue);
            paint.drawEllipse(width() / 2 - xoffset * 2, height() / 2 - yoffset * 2, xoffset * 4, yoffset * 4);
            break;
         case GLOBAL::CERCHIO:
            paint.drawEllipse(xoffset, yoffset, width() - xoffset * 2, height() - yoffset * 2);
            break;
         case GLOBAL::CERCHIOC:
            paint.setBrush(Qt::transparent);
            paint.setPen(Qt::red);
            paint.drawEllipse(xoffset, yoffset, width() - xoffset * 2, height() - yoffset * 2);
            break;
         case GLOBAL::RETTANGOLO:
            paint.drawRect(xoffset, yoffset, width() - xoffset * 2, height() - yoffset * 2);
            break;
         case GLOBAL::POLIGONO: {
               QPolygon p;
               int xcentro = width() / 2;
               int ycentro = height() / 2;
               p.push_back(QPoint(xcentro, yoffset));
               p.push_back(QPoint(xcentro + xoffset, ycentro - yoffset));
               p.push_back(QPoint(width() - xoffset, ycentro));
               p.push_back(QPoint(xcentro + xoffset, ycentro + yoffset));
               p.push_back(QPoint(xcentro, height() - yoffset));
               p.push_back(QPoint(xcentro - xoffset, ycentro + yoffset));
               p.push_back(QPoint(xoffset, ycentro));
               p.push_back(QPoint(xcentro - xoffset, ycentro - yoffset));
               paint.drawPolygon(p);
            }
            break;
         case GLOBAL::LINEAC:
         case GLOBAL::RETTA: {
               paint.setPen(Qt::red);
               int verso = -1;
               int ycentro = height() / 2 - yoffset * 2;
               int xstep = 7;
               int lastx = 0;
               int lasty = 0;
               for(int i = xoffset; i < width() - xoffset - xstep; i += xstep) {
                  lastx = i + xstep;
                  lasty = ycentro + ycentro * (-verso) + yoffset;
                  paint.drawLine(i, ycentro + ycentro * verso + yoffset, lastx, lasty);
                  verso *= -1;
               }
               if(attuale == GLOBAL::LINEAC)
                  paint.drawLine(xoffset, yoffset, lastx, lasty);
            }
            break;
         case GLOBAL::TRIANGOLO:
         default: {
               QPolygon p;
               p.push_back(QPoint(width() / 2, yoffset));
               p.push_back(QPoint(xoffset, height() - yoffset));
               p.push_back(QPoint(width() - xoffset, height() - yoffset));
               paint.drawPolygon(p);
            }
            break;
      }
   paint.end();
}

void Strumenti::clickCerchio() {
   immagineAttuale->setImmagine(GLOBAL::CERCHIO);
   emit nuovoStrumento(GLOBAL::CERCHIO);
   chiudi->setEnabled(false);
}

void Strumenti::clickCerchioC() {
   immagineAttuale->setImmagine(GLOBAL::CERCHIOC);
   emit nuovoStrumento(GLOBAL::CERCHIOC);
   chiudi->setEnabled(false);
}

void Strumenti::clickLinee() {
   immagineAttuale->setImmagine(GLOBAL::RETTA);
   emit nuovoStrumento(GLOBAL::RETTA);
   chiudi->setEnabled(true);
}

void Strumenti::clickLineeC() {
   immagineAttuale->setImmagine(GLOBAL::LINEAC);
   emit nuovoStrumento(GLOBAL::LINEAC);
   chiudi->setEnabled(true);
}

void Strumenti::clickPoligono() {
   immagineAttuale->setImmagine(GLOBAL::POLIGONO);
   emit nuovoStrumento(GLOBAL::POLIGONO);
   chiudi->setEnabled(true);
}

void Strumenti::clickPunto() {
   immagineAttuale->setImmagine(GLOBAL::PUNTO);
   emit nuovoStrumento(GLOBAL::PUNTO);
   chiudi->setEnabled(false);
}

void Strumenti::clickRettangolo() {
   immagineAttuale->setImmagine(GLOBAL::RETTANGOLO);
   emit nuovoStrumento(GLOBAL::RETTANGOLO);
   chiudi->setEnabled(false);
}

void Strumenti::clickTriangolo() {
   immagineAttuale->setImmagine(GLOBAL::TRIANGOLO);
   emit nuovoStrumento(GLOBAL::TRIANGOLO);
   chiudi->setEnabled(false);
}

void Strumenti::clickChiudi() {
   emit chiudiPercorso();
}

void Strumenti::clickDeseleziona() {
   triangolo->setEnabled(true);
   rettangolo->setEnabled(true);
   poligono->setEnabled(true);
   cerchio->setEnabled(true);
   cerchioC->setEnabled(true);
   linee->setEnabled(true);
   lineeC->setEnabled(true);
   punto->setEnabled(true);
   emit deselezionaTutto();
}

void Strumenti::clickOggetti() {
   emit listaOggetti();
}

void Strumenti::clickSeleziona() {
   triangolo->setEnabled(false);
   rettangolo->setEnabled(false);
   poligono->setEnabled(false);
   cerchio->setEnabled(false);
   cerchioC->setEnabled(false);
   linee->setEnabled(false);
   lineeC->setEnabled(false);
   punto->setEnabled(false);
   emit attivaRayCasting();
}


