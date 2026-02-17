#include "colori.h"

Colori::Colori(bool enableAlfa, QWidget *parent)
      : QDialog(parent) {
   setWindowTitle(QString("Colori"));
   QGridLayout *griglia = new QGridLayout;
   setLayout(griglia);
   setMinimumWidth(180);
   setFixedHeight(300);
   int pos = 0;

   QLabel *label;

   // ALPHA
   label = new QLabel(QString("Alpha:"));
   if(enableAlfa)
   griglia->addWidget(label, pos, 0, 1, 1);

   labelAlpha = new QLabel(QString("255"));
   if(enableAlfa)
      griglia->addWidget(labelAlpha, pos, 1, 1, 1);

   if(enableAlfa)
      pos++;

   alpha = new QSlider(Qt::Horizontal);
   if(enableAlfa)
      griglia->addWidget(alpha, pos++, 0, 1, 2);
   alpha->setRange(0, 255);
   alpha->setValue(255);
   connect(alpha, SIGNAL(valueChanged(int)), this, SLOT(aggiornaLabelAlpha(int)));

   // ROSSO
   label = new QLabel(QString("Rosso:"));
   griglia->addWidget(label, pos, 0, 1, 1);

   labelRosso = new QLabel(QString("255"));
   griglia->addWidget(labelRosso, pos, 1, 1, 1);

   pos++;

   rosso = new QSlider(Qt::Horizontal);
   griglia->addWidget(rosso, pos++, 0, 1, 2);
   rosso->setRange(0, 255);
   rosso->setValue(255);
   connect(rosso, SIGNAL(valueChanged(int)), this, SLOT(aggiornaLabelRosso(int)));

   // VERDE
   label = new QLabel(QString("Verde:"));
   griglia->addWidget(label, pos, 0, 1, 1);

   labelVerde = new QLabel(QString("255"));
   griglia->addWidget(labelVerde, pos, 1, 1, 1);

   pos++;

   verde = new QSlider(Qt::Horizontal);
   griglia->addWidget(verde, pos++, 0, 1, 2);
   verde->setRange(0, 255);
   verde->setValue(255);
   connect(verde, SIGNAL(valueChanged(int)), this, SLOT(aggiornaLabelVerde(int)));

   // BLU
   label = new QLabel(QString("Blu:"));
   griglia->addWidget(label, pos, 0, 1, 1);

   labelBlu = new QLabel(QString("0"));
   griglia->addWidget(labelBlu, pos, 1, 1, 1);

   pos++;

   blu = new QSlider(Qt::Horizontal);
   griglia->addWidget(blu, pos++, 0, 1, 2);
   blu->setRange(0, 255);
   blu->setValue(0);
   connect(blu, SIGNAL(valueChanged(int)), this, SLOT(aggiornaLabelBlu(int)));

   esempio = new Anteprima;
   esempio->setFixedSize(100, 50);
   griglia->addWidget(esempio, pos++, 0, 1, 2, Qt::AlignHCenter);

   aggiornaColore();
}

void Colori::aggiornaLabelAlpha(int v) {
   labelAlpha->setText(QString::number(v));
   aggiornaColore();
}

void Colori::aggiornaLabelRosso(int v) {
   labelRosso->setText(QString::number(v));
   aggiornaColore();
}

void Colori::aggiornaLabelVerde(int v) {
   labelVerde->setText(QString::number(v));
   aggiornaColore();
}

void Colori::aggiornaLabelBlu(int v) {
   labelBlu->setText(QString::number(v));
   aggiornaColore();
}

void Colori::aggiornaColore() {
   colore.setAlpha(alpha->value());
   colore.setRed(rosso->value());
   colore.setGreen(verde->value());
   colore.setBlue(blu->value());

   esempio->setColore(colore);
   emit nuovoColore(colore);
}

Colori::Anteprima::Anteprima(QWidget *parent) : QWidget(parent) {

}

void Colori::Anteprima::setColore(const QColor & c) {
   colore = c;
   repaint();
}

void Colori::Anteprima::paintEvent(QPaintEvent *event) {
   event->ignore();
   QPainter paint;
   paint.begin(this);
      paint.setPen(Qt::black);
      paint.setBrush(QBrush(Qt::black));
      paint.drawRect(1, 1, width() - 1, height() - 1);
      paint.setBrush(QBrush(Qt::white));
      paint.drawRect(10 + 1, 10 + 1, width() - 10 - 10 - 1, height() - 10 - 10 - 1);
      paint.setBrush(QBrush(colore));
      paint.drawRect(1, 1, width() - 1, height() - 1);
   paint.end();
}

void Colori::setColore(const QColor & c) {
   colore = c;
   alpha->setValue(c.alpha());
   aggiornaLabelAlpha(c.alpha());
   rosso->setValue(c.red());
   aggiornaLabelRosso(c.red());
   verde->setValue(c.green());
   aggiornaLabelVerde(c.green());
   blu->setValue(c.blue());
   aggiornaLabelBlu(c.blue());
   esempio->setColore(c);
   emit nuovoColore(c);
}
