/*******************************************
 * Written in 2014 by Kamil Niemczyk
 *
 * PL:
 * ! Kod kopiować wraz z tym komentarzem !
 * W przypadku wprowadzenia zmian
 * dopisać się do listy autorów kodu.
 * Rozprowadzać bezpłatnie.
 * Wyrażam zgodę na używanie programu oraz
 * jego kodu w celach dydaktycznych.
 *
 * EN:
 * ! Copy only with this comment !
 * In case of any changes add your nick/name
 * to authors list.
 * Distribute free of charge.
 * I agree to use this program and its code
 * for educational purposes.
 *******************************************/
#ifndef QEDGE_HH
#define QEDGE_HH

#include "Graph.hh"
#include "QVertex.hh"
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneHoverEvent>
#include <QLabel>
#include <QPalette>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QCursor>
#include <cmath>

// deklaracja dla kompilatora
class QVertex;

/* klasa QEdge
 *
 * definiuje krawędź jako obiekt graficzny rysowany w programie
 * wraz z obsługą zdarzeń.
*/
class QEdge : public QGraphicsLineItem {
  int wP; // wierzcholek poczatkowy
  int wK; // wierzcholek koncowy
  int droga; // waga
  QVertex ** elltextV;
  QGraphicsItemGroup * group;
  QGraphicsTextItem * label;

  QLabel *** labelWagi;
  QLabel **  labelListaK;
  QLabel *** labelListaS;
  Graph * graf;
  int Ki;
  bool * linkM;
  bool * linkLk;
  bool * linkLs;
protected:
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    highlight(255,0,0,255);
    QGraphicsItem::hoverEnterEvent(event);
  }
  void hoverMoveEvent(QGraphicsSceneHoverEvent *event)
  {
    highlight(255,0,0,255);

    QGraphicsItem::hoverMoveEvent(event);
  }
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
  {
    lightsoff();
    QGraphicsItem::hoverLeaveEvent(event);
  }
public:
  QEdge(int i,int j, bool * m, bool * lk, bool * ls, qreal x1=0, qreal y1=0,\
        qreal x2=0, qreal y2=0, QGraphicsItem* parent=0)
    : QGraphicsLineItem(x1,y1,x2,y2,parent)
  {
    setAcceptHoverEvents(true);
    group = new QGraphicsItemGroup(this);
    wP = i;
    wK = j;
    linkM = m;
    linkLk = lk;
    linkLs = ls;
    setZValue(0);
    label = new QGraphicsTextItem;
    label->setZValue(30);
    x1 = ((x1<x2)?x2-x1:-1*(x1-x2))/2;
    y1 = ((y1<y2)?y2-y1:-1*(y1-y2))/2;
    label->setPos(x2-x1-12,y2-y1-12);
    label->setGroup(group);
    QFont f;
    f.setBold(true);
    label->setFont(f);
    //label->setVisible(false);
    setCursor(QCursor(Qt::CrossCursor));
    isBlue = false;
  }
  void highlight(int r, int g, int b, int alpha);
  void highlightDij(int r, int g, int b, int alpha);
  void lightsoff()
  {
    highlight(0,0,0,255);
    setZValue(0);
    elltextV[wP]->setZValue(10);
    elltextV[wK]->setZValue(10);
    //label->setVisible(false);
  }
  void lightsoffDij()
  {
    highlightDij(180,180,180,255);
    setZValue(0);
    elltextV[wP]->setZValue(50);
    elltextV[wK]->setZValue(50);
  }
  void setPtrs(QLabel *** w, QLabel ** lk, int i, QLabel *** s, Graph * g,\
               QVertex ** etV)
  {
    elltextV = etV;
    labelWagi=w;
    labelListaK=lk;
    labelListaS=s;
    Ki=i;
    graf = g;
    droga = *graf->MacierzWag()->operator()(wP,wK);
    label->setHtml("<div style='background-color: white;'>" \
                   + QString::number(droga) + "</div>");
    droga=*graf->MacierzWag()->operator()(wP,wK);
  }
  int WP() const { return wP; }
  int WK() const { return wK; }
  int Droga() const { return droga; }
  void setDroga(int value)
  {
    droga=value;
  }
  bool isBlue;
};

#endif // QEDGE_HH
