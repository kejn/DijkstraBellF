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
#include "QEdge.hh"
#include "QVertex.hh"

void QEdge::highlight(int r, int g, int b, int alpha)
{
  setZValue(50);
  elltextV[wP]->setZValue(100);
  elltextV[wK]->setZValue(100);

  QPalette palette;
  QColor color(r,g,b,alpha);
  QBrush brush(color);
  QPen pen(color);
  pen.setStyle(Qt::SolidLine);
  brush.setStyle(Qt::SolidPattern);

  palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
  palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);

  if(*linkM){
    labelWagi[wP][wK]->setPalette(palette);
    labelWagi[wK][wP]->setPalette(palette);
  }
  if(*linkLk){
    labelListaK[Ki]->setPalette(palette);
  }
  if(*linkLs){
    int a = 1;
    QString * s = new QString("V");
    s->append(QString::number(wK+1));
    s->append(",");
    while(labelListaS[wP][a]->text().contains(s) == false) a++;
    labelListaS[wP][a]->setPalette(palette);
    delete s;
    a = 1;
    s = new QString("V");
    s->append(QString::number(wP+1));
    s->append(",");
    while(labelListaS[wK][a]->text().contains(s) == false) a++;
    labelListaS[wK][a]->setPalette(palette);
    delete s;
  }
  elltextV[wP]->setPen(pen);
  elltextV[wK]->setPen(pen);
  elltextV[wP]->Label()->setDefaultTextColor(color);
  elltextV[wK]->Label()->setDefaultTextColor(color);
  this->QGraphicsLineItem::setPen(pen);
  label->setDefaultTextColor(color);
  label->setVisible(true);
}

void QEdge::highlightDij(int r, int g, int b, int alpha)
{
  setAcceptHoverEvents(false);
  QColor color(r,g,b,alpha);
  QPen pen(color);
  pen.setStyle(Qt::SolidLine);

  if(!elltextV[wP]->isClicked()){
      elltextV[wP]->setPen(pen);
      elltextV[wP]->Label()->setDefaultTextColor(color);
  }
  if(!elltextV[wK]->isClicked()){
      elltextV[wK]->setPen(pen);
      elltextV[wK]->Label()->setDefaultTextColor(color);
  }
  this->QGraphicsLineItem::setPen(pen);
  label->setDefaultTextColor(color);
  label->setVisible(true);
}
