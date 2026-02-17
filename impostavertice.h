#ifndef IMPOSTAVERTICE_H
#define IMPOSTAVERTICE_H

#include <QtCore>
#include <QtWidgets>
#include "vertici.h"
#include "colori.h"

/*
  Classe ImpostaVertice
  genera una fiestra che permette di modificare le proprietà del vertice.
*/

class Vertice;

class ImpostaVertice : public QDialog {
   Q_OBJECT
   public:
       ImpostaVertice(Vertice * v = 0, QWidget *parent = 0);

   signals:
       void aggiornaGL();

   private:
       Vertice *vertice;

       QLineEdit *xpos;
       QLineEdit *ypos;

       void aggiornaDisegno();

    private slots:
       void aggiornaColore(const QColor & c);
       void aggiornaTesto(const QString & txt);
};

#endif // IMPOSTAVERTICE_H
