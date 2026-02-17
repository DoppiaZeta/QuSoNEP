#include "mainwidget.h"

Widget::Widget(QWidget *parent)
    : QMainWindow(parent) {

   strumenti = new Strumenti();
   colori = new Colori();
   contavertici = new Contavertici();
   disegno = new GLDisegno;

   QDockWidget *docV = new QDockWidget(QString("Vertici inseriti"));
   docV->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
   docV->setWidget(contavertici);

   QDockWidget *docC = new QDockWidget(colori->windowTitle());
   docC->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
   docC->setFeatures(QDockWidget::DockWidgetVerticalTitleBar | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
   docC->setWidget(colori);

   QDockWidget *docS = new QDockWidget(strumenti->windowTitle());
   docS->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
   docS->setFeatures(QDockWidget::DockWidgetVerticalTitleBar | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
   docS->setWidget(strumenti);

   connect(disegno, SIGNAL(coordinateAggiornate(QList<Vertice>*)), contavertici, SLOT(aggiornaVertici(QList<Vertice>*)));
   connect(colori, SIGNAL(nuovoColore(QColor)), disegno, SLOT(setColoreAttuale(QColor)));
   connect(strumenti, SIGNAL(nuovoStrumento(GLOBAL::Immagine)), disegno, SLOT(setStrumentoAttuale(GLOBAL::Immagine)));
   connect(strumenti, SIGNAL(chiudiPercorso()), disegno, SLOT(chiudiPercorso()));
   connect(strumenti, SIGNAL(deselezionaTutto()), disegno, SLOT(deseleziona()));
   connect(contavertici, SIGNAL(ridisegna()), disegno, SLOT(ridisegna()));
   connect(strumenti, SIGNAL(listaOggetti()), disegno, SLOT(listaOggetti()));
   connect(strumenti, SIGNAL(attivaRayCasting()), disegno, SLOT(attivaSelezione()));

   setCentralWidget(disegno);
   addDockWidget(Qt::LeftDockWidgetArea, docS);
   addDockWidget(Qt::RightDockWidgetArea, docC);
   addDockWidget(Qt::BottomDockWidgetArea, docV);

   QMenuBar *menuBar;
   QAction *action;
   QMenu *menu;
   menuBar = new QMenuBar;
   menu = new QMenu(QString("File"));
   menuBar->addMenu(menu);
   action = menu->addAction(QString("Apri"));
   connect(action, SIGNAL(triggered()), disegno, SLOT(apri()));
   action = menu->addAction(QString("Salva"));
   connect(action, SIGNAL(triggered()), disegno, SLOT(salva()));
   menu->addSeparator();
   action = menu->addAction(QString("Esci"));
   connect(action, SIGNAL(triggered()), SLOT(close()));
   menu = new QMenu(QString("Modifica"));
   action = menu->addAction(QString("Cambia sfondo"));
   connect(action, SIGNAL(triggered()), disegno, SLOT(finestraColoreSfondo()));
   menuBar->addMenu(menu);
   menu = new QMenu(QString("?"));
   menuBar->addMenu(menu);
   action = menu->addAction(QString("Informazioni su Qt"));
   connect(action, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
   action = menu->addAction(QString("Informazioni su QuSoNEP"));
   connect(action, SIGNAL(triggered()), SLOT(QuSoNEP()));
   setMenuBar(menuBar);

   setMinimumSize(800, 600);
   showMaximized();
}

Widget::~Widget() {

}

void Widget::keyPressEvent(QKeyEvent * evento) {
   disegno->premiTasto(evento);
}

void Widget::keyReleaseEvent(QKeyEvent * evento) {
   disegno->rilasciaTasto(evento);
}

void Widget::QuSoNEP() {
   static aboutQuSoNEP *a = new aboutQuSoNEP;
   a->show();
}

Widget::aboutQuSoNEP::aboutQuSoNEP(QWidget *parent) : QDialog(parent) {
   setWindowTitle(QString("Informazioni su QuSoNEP"));
   setModal(Qt::WindowModal);
   QLayout *g = new QGridLayout;
   QLabel *l = new QLabel;
   g->addWidget(l);
   setLayout(g);
   l->setText(QString(
         "<div style=\"color:red; font-size: 30px\">QuSoNEP</div>"
         "<div style=\"color:green; font-size: 14px\">Questo Software Non &Egrave; Phun</div>"
         "<div style=\"font-size: 10px\"><a style=\"color: gray\" href=\"http://www.phunland.com\">http://www.phunland.com</a><br /></div>"
         "<div style=\"color:blue; font-size: 17px\">Creato da Tommaso Moro come progetto di<br />informatica grafica e multimedialit&agrave;</div>"
         "<div style=\"color:gray; font-size: 14px\">Versione 1.0</div>"
         "<div style=\"color:gray; font-size: 14px\">Settembre 2009</div>"
   ));
}
