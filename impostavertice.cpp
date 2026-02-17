#include "impostavertice.h"

ImpostaVertice::ImpostaVertice(Vertice *v, QWidget *parent)
      : QDialog(parent) {
   vertice = v;
   setAttribute(Qt::WA_DeleteOnClose);
   setModal(Qt::WindowModal);
   if(v == 0)
      close();
   else {
      setWindowTitle(QString("Vertice X:%1").arg(v->getX()) +
                     QString(" Y:%1").arg(v->getY()));

      QGridLayout *griglia = new QGridLayout;

      QLabel *label;

      label = new QLabel(QString("Coordinata X:"));
      xpos = new QLineEdit(QString::number(v->getX()));
      griglia->addWidget(label, 0, 0);
      griglia->addWidget(xpos, 0, 1);

      label = new QLabel(QString("Coordinata Y:"));
      ypos = new QLineEdit(QString::number(v->getY()));
      griglia->addWidget(label, 1, 0);
      griglia->addWidget(ypos, 1, 1);

      connect(xpos, SIGNAL(textEdited(QString)), this, SLOT(aggiornaTesto(QString)));
      connect(ypos, SIGNAL(textEdited(QString)), this, SLOT(aggiornaTesto(QString)));

      Colori *c = new Colori;
      c->setColore(v->getColore());
      connect(c, SIGNAL(nuovoColore(QColor)), SLOT(aggiornaColore(QColor)));
      griglia->addWidget(c, 2, 0, 1, 2);

      setLayout(griglia);
   }
}

void ImpostaVertice::aggiornaTesto(const QString & txt) {
   txt.isNull();
   aggiornaDisegno();
}

void ImpostaVertice::aggiornaDisegno() {
   int v;
   bool successo;
   v = xpos->text().toInt(&successo);
   if(successo) vertice->setX(v);
   v = ypos->text().toInt(&successo);
   if(successo) vertice->setY(v);

   emit aggiornaGL();
}

void ImpostaVertice::aggiornaColore(const QColor & c) {
   vertice->setColore(c);
   emit aggiornaGL();
}
