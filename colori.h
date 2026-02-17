#ifndef COLORI_H
#define COLORI_H

#include <QtGui>
#include <QtCore>

/*
  Classe Colori
  Widget o finestra per la selezione del colore
*/

class Colori : public QDialog {
   Q_OBJECT
   protected: class Anteprima;

   public:
      Colori(bool enableAlfa = true, QWidget *parent = 0);
      void setColore(const QColor & c);

   signals:
      void nuovoColore(const QColor &);

   protected:
      QSlider *alpha;
      QSlider *rosso;
      QSlider *verde;
      QSlider *blu;
      QLabel *labelAlpha;
      QLabel *labelRosso;
      QLabel *labelVerde;
      QLabel *labelBlu;

      Anteprima *esempio;
      QColor colore;

      void aggiornaColore();

   private slots:
       void aggiornaLabelAlpha(int v);
       void aggiornaLabelRosso(int v);
       void aggiornaLabelVerde(int v);
       void aggiornaLabelBlu(int v);

   protected:
       // classe per disegnare l'anteprima
       class Anteprima : public QWidget {
          public:
             Anteprima(QWidget *parent = 0);

             void setColore(const QColor & c);

          protected:
             QColor colore;
             void paintEvent(QPaintEvent *event);
       };
};

#endif // COLORI_H
