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
#ifndef QVERTEX_HH
#define QVERTEX_HH

#include "Wsp.hh"
#include "Edge.hh"
#include "Graph.hh"
#include "QEdge.hh"
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include <QLabel>
#include <QPalette>
#include <QBrush>
#include <QPen>
#include <QFont>

// delkaracje dla kompilatora
class QEdge;
class Wsp;

/* klasa QVertex
 *
 * definiuje wierzchołek jako obiekt graficzny rysowany w programie
 * wraz z obsługą zdarzeń.
*/
class QVertex : public QGraphicsEllipseItem {
  int id; // nr wierzchołka
  int prev; // poprzednik (do testowanych algorytmów)
  int droga;
  Wsp * wsp;
  QGraphicsItemGroup * group;
  QGraphicsTextItem * label;
  QLabel *** labelWagi;
  QLabel **  labelListaK;
  QLabel *** labelListaS;
  QEdge ** lineE;
  Graph * graf;
  bool * linkM;
  bool * linkLk;
  bool * linkLs;
  bool clicked;
public:
  QVertex(int i, bool * m, bool * lk, bool * ls, qreal x, qreal y,
          qreal r=30.0, QGraphicsItem* parent=0)
    : QGraphicsEllipseItem(x,y,r,r,parent)
  {
    setAcceptHoverEvents(true);
    group = new QGraphicsItemGroup(this);
    id = i;
    wsp = new Wsp(x,y);
    linkM = m;
    linkLk = lk;
    linkLs = ls;
    clicked = false;
    QGraphicsEllipseItem::setBrush(QBrush(Qt::white));
    QGraphicsItem::setZValue(10);
    x+=3;
    if(id < 9) x+= 4;
    label = new QGraphicsTextItem(QString::number(i+1));
    label->setPos(x,y+2);
    label->setGroup(group);
    setCursor(QCursor(Qt::CrossCursor));
  }
protected:
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    highlightAllNeighbours(255,0,0,255);
    QGraphicsItem::hoverEnterEvent(event);
  }
  void hoverMoveEvent(QGraphicsSceneHoverEvent *event)
  {
    highlightAllNeighbours(255,0,0,255);
    QGraphicsItem::hoverMoveEvent(event);
  }
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
  {
    lightsoffAllNeighbours();
    QGraphicsItem::hoverLeaveEvent(event);
  }
//  void mousePressEvent(QGraphicsSceneMouseEvent *event)
//  {
//    do {
//      r = qrand()%256;
//      g = qrand()%256;
//      b = qrand()%256;
//    } while(r+g+b < 100);
//    if(!clicked)
//      highlight(r,g,b,255);
//     else
//      highlight(255,0,0,255);
//    clicked = !clicked;
//    QGraphicsItem::mousePressEvent(event);
//  }

public:
  void highlight(int r, int g, int b, int alpha);
  void lightsoff();
  void lightsoffDij();
  void highlightAllNeighbours(int r, int g, int b, int alpha);
  void lightsoffAllNeighbours();
  void lightsoffAllNeighboursDij();
  void setPtrs(QLabel *** w, QLabel ** lk, QLabel *** s, Graph * g, QEdge ** le)
  {
    lineE = le;
    labelWagi=w;
    labelListaK=lk;
    labelListaS=s;
    graf = g;
  }
  int Droga() { return droga; }
  void setDroga(int value) { droga=value; }
  int  Prev() { return  prev; }
  void setPrev(int value) { prev=value; }
  Wsp & getWsp() const { return *wsp; }
  void Click() { clicked=true; }
  bool isClicked() const { return clicked; }
  QGraphicsTextItem * Label() { return label; }
  QGraphicsItemGroup * Grupa() { return group; }
  static int minV(QVertex **tab, int size);
  QEdge * incidentEdge(int Vx);
  ~QVertex() { delete wsp; delete label; }
};

#endif // QVERTEX_HH
