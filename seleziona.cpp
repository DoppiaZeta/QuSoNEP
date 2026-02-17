#include "seleziona.h"

Seleziona::Seleziona(QList<FiguraAstratta*> *l) {
   lista = l;
   setWindowTitle(QString("Seleziona un'oggetto"));
   setAttribute(Qt::WA_DeleteOnClose);
   setModal(Qt::WindowModal);
   setMinimumHeight(400);
   setMinimumWidth(480);
   QGridLayout *griglia = new QGridLayout;
   setLayout(griglia);

   tabella = new QTableWidget;
   griglia->addWidget(tabella, 0, 0, 1, 2);
   tabella->setColumnCount(5);
   connect(tabella, SIGNAL(cellClicked(int,int)), SLOT(attivaSelezionato(int,int)));

   chiudi = new QPushButton(QString("Finito"));
   griglia->addWidget(chiudi, 1, 0, 1, 2);
   connect(chiudi, SIGNAL(clicked()), SLOT(chiudiFinestra()));

   caricaTabella();
}

void Seleziona::chiudiFinestra() {
   close();
}

void Seleziona::attivaSelezionato(int r, int c) {
   emit deseleziona();
   if(c == 4) {
      QList<FiguraAstratta*>::iterator it = lista->begin();
      for(int k = 0; k < lista->size() - r - 1; k++)
         it++;
      lista->erase(it);
      caricaTabella();
   } else
      lista->operator[](lista->size() - r - 1)->setSelezionato(true);
   emit ridisegna();
}

Seleziona::Cancella::Cancella() {
   setMinimumSize(60, 40);
}

void Seleziona::Cancella::paintEvent(QPaintEvent *event) {
   event->ignore();
   QPainter paint;
   int xoffset = 7;
   int yoffset = 5;
   paint.begin(this);
      paint.setPen(QColor(0xff, 0x33, 0x33, 0xff));
      paint.drawLine(xoffset, yoffset, width() - xoffset, height() - yoffset * 3);
      paint.drawLine(xoffset, height() - yoffset * 3, width() - xoffset, yoffset);
      paint.setPen(Qt::blue);
      paint.drawText(xoffset, height() - yoffset, QString("Cancella"));
   paint.end();
}

void Seleziona::caricaTabella() {
   QFont font;
   font.setPointSize(12);
   int indiceTabella = 0;
   tabella->setRowCount(lista->size());
   tabella->setColumnWidth(0, 50);
   tabella->setColumnWidth(1, 120);
   tabella->setColumnWidth(2, 50);
   tabella->setColumnWidth(3, 120);
   tabella->setColumnWidth(4, 65);
   for(int i = lista->size() - 1; i >= 0 ; i--) {
      tabella->setRowHeight(indiceTabella, 45);
      QTableWidgetItem *it = new QTableWidgetItem(QString("Id: %1").arg(indiceTabella + 1));
      it->setFont(font);
      it->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
      tabella->setItem(indiceTabella, 0, it);
      it = new QTableWidgetItem(GLOBAL::ottieniInformazioni(lista->operator[](i)->getImmagine()).getNome());
      it->setFont(font);
      it->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
      tabella->setItem(indiceTabella, 1, it);
      Strumenti::Attuale *icona = new Strumenti::Attuale;
      icona->setImmagine(lista->operator[](i)->getImmagine());
      tabella->setCellWidget(indiceTabella, 2, icona);
      it = new QTableWidgetItem(QString("Vertici: %1").arg(lista->operator[](i)->contaVertici()));
      it->setFont(font);
      it->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
      tabella->setItem(indiceTabella, 3, it);
      Cancella *canc = new Cancella;
      tabella->setCellWidget(indiceTabella, 4, canc);
      indiceTabella++;
   }
}

