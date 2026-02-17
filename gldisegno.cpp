#include "gldisegno.h"

GLDisegno::GLDisegno() {
   coloreAttuale = QColor(255, 255, 0);
   verticeInMovimento = 0;
   prendiCoordinate = true;
   strumentoAttuale = GLOBAL::TRIANGOLO;
   attivaRayCasting = false;
   centro = 0;
   coloreSfondo = Qt::black;
   db = QSqlDatabase::addDatabase(QString("QSQLITE"));
}

GLDisegno::~GLDisegno() {
   for(int i = 0; i < figure.size(); i++)
      delete figure[i];
}

void GLDisegno::mouseMoveEvent(QMouseEvent * evento) {
   bool selezionato = false;
   int i;
   for(i = 0; i < figure.size() && !selezionato; i++)
      selezionato = figure[i]->getSelezionato();
   i--;

   if(verticeInMovimento) {
      if(evento->x() > 0 && evento->x() < width())
         verticeInMovimento->setX(evento->x());
      if(evento->y() > 0 && evento->y() < height())
         verticeInMovimento->setY(height() - evento->y());
      if(centro)
         centro->operator=(figure[i]->verticeMedia());
      updateGL();
   } else if(centro) {
      int x = centro->getX();
      int y = centro->getY();
      if(evento->x() > 0 && evento->x() < width())
         centro->setX(evento->x());
      if(evento->y() > 0 && evento->y() < height())
         centro->setY(height() - evento->y());
      x = centro->getX() - x;
      y = centro->getY() - y;
      for(QList<Vertice>::iterator it = figure[i]->primoVertice(); it != figure[i]->ultimoVertice(); it++) {
         it->setX(it->getX() + x);
         it->setY(it->getY() + y);
      }
      updateGL();

   }
}

void GLDisegno::mouseReleaseEvent(QMouseEvent * evento) {
   evento->ignore();
   verticeInMovimento = 0;
}

void GLDisegno::mousePressEvent(QMouseEvent * evento) {
   if(attivaRayCasting) {
      bool trovato = false;
      for(int i = 0; i < figure.size() && !trovato; i++)
         if(figure[i]->rayCasting(evento->x(), height() - evento->y())) {
            trovato = true;
            figure[i]->setSelezionato(true);
            attivaRayCasting = false;
            updateGL();
         }
   } else {
      if(!verticeInMovimento) {
         bool trovato = false;
         for(int i = 0; i < figure.size() && !trovato; i++)
            if(figure[i]->getSelezionato())
               trovato = figure[i]->collisioneVertice(evento->x(),
                                                      height() - evento->y(),
                                                      verticeInMovimento
                                                      );
         if(centro && centro->collisione(evento->x(), height() - evento->y()))
            verticeInMovimento = 0;
      }

      bool selezionato = false;
      for(int i = 0; i < figure.size() && !selezionato; i++)
         selezionato = figure[i]->getSelezionato();

      if(prendiCoordinate && !verticeInMovimento && !selezionato) {
         Vertice v(evento->x(), height() - evento->y());
         v.setColore(coloreAttuale);
         coordinate.push_back(v);

         if(coordinate.size() == GLOBAL::ottieniInformazioni(strumentoAttuale).getMaxVertici()) {
            FiguraAstratta* f;
            switch(strumentoAttuale) {
               case GLOBAL::CERCHIO:
                  f = new Cerchio;
                  break;
               case GLOBAL::CERCHIOC:
                  f = new Cerchio;
                  dynamic_cast<Cerchio*>(f)->setTipo(Cerchio::CERCHIO_CONTORNO);
                  break;
               case GLOBAL::RETTANGOLO:
                  f = new Rettangolo;
                  break;
               case GLOBAL::PUNTO:
                  f = new Punto;
                  break;
               case GLOBAL::TRIANGOLO:
               default:
                  f = new Triangolo;
                  break;
            }
            for(int i = 0; i < coordinate.size(); i++)
               f->addVertice(coordinate[i]);
            coordinate.clear();
            figure.push_front(f);
            connect(f, SIGNAL(lampeggia()), SLOT(ridisegna()));
         }
         updateGL();
         emit coordinateAggiornate(&coordinate);
      }
   }
}

void GLDisegno::mouseDoubleClickEvent(QMouseEvent * evento) {
   Vertice *v = 0;

   bool trovato = false;
   for(int i = 0; i < figure.size() && !trovato; i++)
      if(figure[i]->getSelezionato())
         trovato = figure[i]->collisioneVertice(evento->x(),
                                                height() - evento->y(),
                                                v
                                                );

   if(v) {
      ImpostaVertice *imp = new ImpostaVertice(v);
      imp->show();
   }

}

void GLDisegno::ridisegna() {
   updateGL();
}

void GLDisegno::initializeGL() {
   qglClearColor(coloreSfondo);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_BLEND);
   glEnable(GL_LINE_SMOOTH);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLDisegno::resizeGL(int w, int h) {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glViewport(0, 0, w, h);
   glOrtho(0, w, 0, h, -4 - figure.size(), 1);
}

void GLDisegno::paintGL() {
   resizeGL(width(), height());
   qglClearColor(coloreSfondo);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   int maxprofondita = 0;
   for(int i = 0; i < figure.size(); i++)
      if(figure[figure.size() - i - 1]->getSelezionato() == false) {
         figure[figure.size() - i - 1]->disegna(maxprofondita);
         maxprofondita++;
      }

   for(int i = 0; i < coordinate.size(); i++)
      coordinate[i].disegna(maxprofondita);
   maxprofondita++;

   for(int i = 0; i < figure.size(); i++)
      if(figure[i]->getSelezionato()) {
         figure[i]->disegna(maxprofondita);
         maxprofondita++;
      }

   if(centro)
      centro->disegna(maxprofondita + 2);

   swapBuffers();
}

QColor GLDisegno::getColoreAttuale() const {
   return coloreAttuale;
}

void GLDisegno::setColoreAttuale(const QColor & c) {
   coloreAttuale = c;
}

void GLDisegno::setStrumentoAttuale(const GLOBAL::Immagine & i) {
   strumentoAttuale = i;
}

void GLDisegno::chiudiPercorso() {
   FiguraAstratta* f;
   if(coordinate.size() < GLOBAL::ottieniInformazioni(strumentoAttuale).getMinVertici())
      return;
   switch(strumentoAttuale) {
      case GLOBAL::POLIGONO:
         f = new Poligono;
         break;
      case GLOBAL::RETTA:
         f = new Retta;
         break;
      case GLOBAL::LINEAC:
         f = new Lineac;
         break;
      default:
         return;
   }
   for(int i = 0; i < coordinate.size(); i++)
      f->addVertice(coordinate[i]);
   coordinate.clear();
   figure.push_front(f);
   connect(f, SIGNAL(lampeggia()), SLOT(ridisegna()));

   updateGL();
   emit coordinateAggiornate(&coordinate);
}

void GLDisegno::deseleziona() {
   for(int i = 0; i < figure.size(); i++)
      figure[i]->setSelezionato(false);
   attivaRayCasting = false;
   updateGL();
}

void GLDisegno::attivaSelezione() {
   attivaRayCasting = true;
}

void GLDisegno::listaOggetti() {
   Seleziona *s = new Seleziona(&figure);
   connect(s, SIGNAL(deseleziona()), SLOT(deseleziona()));
   connect(s, SIGNAL(ridisegna()), SLOT(ridisegna()));
   s->show();
}

void GLDisegno::premiTasto(QKeyEvent * evento) {
   bool selezionato = false;
   int i;
   for(i = 0; i < figure.size() && !selezionato; i++)
      selezionato = figure[i]->getSelezionato();
   if(selezionato && evento->key() == Qt::Key_Shift) {
      if(centro)
         delete centro;
      centro = new VerticeMovimento(figure[i - 1]->verticeMedia());
      updateGL();
   }
}

void GLDisegno::rilasciaTasto(QKeyEvent * evento) {
   if(centro && evento->key() == Qt::Key_Shift) {
      delete centro;
      centro = 0;
      updateGL();
   }
}

void GLDisegno::cambiaSfondo(const QColor & c) {
   coloreSfondo = c;
   updateGL();
}

void GLDisegno::finestraColoreSfondo() {
   static Colori *c = new Colori(false);
   c->setModal(Qt::WindowModal);
   c->setColore(coloreSfondo);
   connect(c, SIGNAL(nuovoColore(QColor)), SLOT(cambiaSfondo(QColor)));
   c->show();
}

void GLDisegno::salva() {
   db.setDatabaseName(QFileDialog::getSaveFileName(this, QString("Salva un file"), QString("."), QString("SQL Lite database (*.db)")));
   if(!db.open())
      QMessageBox::critical(0, QString("Errore"), QString("Non riesco a salvare"));
   else {
      QString query;
      QSqlQuery q(db);

      query = QString("drop table if exists VERTICI");
      q.exec(query);
      query = QString("drop table if exists IMMAGINI");
      q.exec(query);
      query = QString("drop table if exists INFORMAZIONI");
      q.exec(query);
      query = QString("create table if not exists VERTICI ("
                      "codvertice integer primary key autoincrement,"
                      "codimmagine integer,"
                      "x integer,"
                      "y integer,"
                      "alpha integer,"
                      "rosso integer,"
                      "verde integer,"
                      "blu integer"
                      ")"
                     );
      q.exec(query);
      query = QString("create table if not exists IMMAGINI ("
                      "codimmagine integer primary key autoincrement,"
                      "immagine integer,"
                      "tipo integer"
                      ")"
                     );
      q.exec(query);
      query = QString("create table if not exists INFORMAZIONI ("
                      "codinformazione integer primary key autoincrement,"
                      "codice text,"
                      "valore text"
                      ")"
                     );
      q.exec(query);

      for(int i = figure.size() - 1; i >= 0; i--) {
         QList<Vertice>::iterator it = figure[i]->primoVertice();
         query = QString("insert into IMMAGINI (immagine, tipo) values(");
         query += QString::number(figure[i]->getImmagine());
         query += QChar(',');
         query += QString::number(GLOBAL::ottieniInformazioni(figure[i]->getImmagine()).getTipo());
         query += QChar(')');
         q.exec(query);
         query = QString("select max(codimmagine) from IMMAGINI");
         q.exec(query);
         q.first();
         QString codimmagine = q.value(0).toString();
         while(it != figure[i]->ultimoVertice()) {
            query = QString("insert into VERTICI (codimmagine, x, y, alpha, rosso, verde, blu) values(");
            query += codimmagine;
            query += QChar(',');
            query += QString::number(it->getX());
            query += QChar(',');
            query += QString::number(it->getY());
            query += QChar(',');
            query += QString::number(it->getColore().alpha());
            query += QChar(',');
            query += QString::number(it->getColore().red());
            query += QChar(',');
            query += QString::number(it->getColore().green());
            query += QChar(',');
            query += QString::number(it->getColore().blue());
            query += QChar(')');
            QSqlQuery q2(db);
            q2.exec(query);
            it++;
         }
      }

      query = QString("insert into INFORMAZIONI (codice, valore) values('VERSIONE', '1.0')");
      q.exec(query);
      query = QString("insert into INFORMAZIONI (codice, valore) values('VERSIONEDB', '1.0')");
      q.exec(query);
      query = QString("insert into INFORMAZIONI (codice, valore) values('BGROSSO', '");
      query += QString::number(coloreSfondo.red());
      query += QString("')");
      q.exec(query);
      query = QString("insert into INFORMAZIONI (codice, valore) values('BGVERDE', '");
      query += QString::number(coloreSfondo.green());
      query += QString("')");
      q.exec(query);
      query = QString("insert into INFORMAZIONI (codice, valore) values('BGBLU', '");
      query += QString::number(coloreSfondo.blue());
      query += QString("')");
      q.exec(query);

      db.close();
   }
}

void GLDisegno::apri() {
   db.setDatabaseName(QFileDialog::getOpenFileName(this, QString("Apri un file"), QString("."), QString("SQL Lite database (*.db)")));
   if(!db.open())
      QMessageBox::critical(0, QString("Errore"), QString("Non riesco ad aprire"));
   else {
      for(int i = 0; i < figure.size(); i++)
         delete figure[i];
      figure.clear();

      QString query;
      QSqlQuery q(db), q2(db), q3(db);

      query = QString("select codimmagine, immagine from IMMAGINI order by codimmagine asc");
      q.exec(query);
      q.first();
      query = QString("select count(codimmagine) from IMMAGINI");
      q2.exec(query);
      q2.first();
      int record = q2.value(0).toInt();
      for(int i = 0; i < record; i++) {
         FiguraAstratta *fig;
         switch(static_cast<GLOBAL::Immagine>(q.value(1).toInt())) {
            case GLOBAL::RETTANGOLO:
               fig = new Rettangolo;
               break;
            case GLOBAL::CERCHIO:
               fig = new Cerchio;
               break;
            case GLOBAL::TRIANGOLO:
               fig = new Triangolo;
               break;
            case GLOBAL::POLIGONO:
               fig = new Poligono;
               break;
            case GLOBAL::RETTA:
               fig = new Retta;
               break;
            case GLOBAL::PUNTO:
               fig = new Punto;
               break;
            case GLOBAL::LINEAC:
               fig = new Lineac;
               break;
            case GLOBAL::CERCHIOC:
            default:
               fig = new Cerchio;
               dynamic_cast<Cerchio*>(fig)->setTipo(Cerchio::CERCHIO_CONTORNO);
               break;
         }

         query = QString("select x, y, alpha, rosso, verde, blu from VERTICI where codimmagine = ");
         query += q.value(0).toString();
         query += QString(" order by codvertice asc");
         q3.exec(query);
         q3.first();
         query = QString("select count(codvertice) from VERTICI where codimmagine = ");
         query += q.value(0).toString();
         q2.exec(query);
         q2.first();

         int record2 = q2.value(0).toInt();
         for(int k = 0; k < record2; k++) {
            Vertice v;
            QColor c;
            v.setX(q3.value(0).toInt());
            v.setY(q3.value(1).toInt());
            c.setAlpha(q3.value(2).toInt());
            c.setRed(q3.value(3).toInt());
            c.setGreen(q3.value(4).toInt());
            c.setBlue(q3.value(5).toInt());
            v.setColore(c);
            fig->addVertice(v);
            q3.next();
         }

         figure.push_front(fig);
         connect(fig, SIGNAL(lampeggia()), SLOT(ridisegna()));
         q.next();
      }

      query = QString("select valore from INFORMAZIONI where codice = 'BGROSSO'");
      q.exec(query);
      q.first();
      coloreSfondo.setRed(q.value(0).toInt());
      query = QString("select valore from INFORMAZIONI where codice = 'BGVERDE'");
      q.exec(query);
      q.first();
      coloreSfondo.setGreen(q.value(0).toInt());
      query = QString("select valore from INFORMAZIONI where codice = 'BGBLU'");
      q.exec(query);
      q.first();
      coloreSfondo.setBlue(q.value(0).toInt());

      db.close();
      updateGL();
   }
}

