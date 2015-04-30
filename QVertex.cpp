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

/* metoda highlight
 *
 * podświetla wierzchołek (koloruje) wg: r,g,b,alpha
*/
void QVertex::highlight(int r, int g, int b, int alpha)
{
  QColor color(r,g,b,alpha);
  QPen pen(color);
  pen.setStyle(Qt::SolidLine);
  QGraphicsEllipseItem::setPen(pen);
  label->setDefaultTextColor(color);
}

/* metoda highlightAllNeighbours
 *
 * podświetla wierzchołek (koloruje) wg: r,g,b,alpha
 * oraz wszystkie jego incydentne krawędzie i wierzchołki
*/
void QVertex::highlightAllNeighbours(int r, int g, int b, int alpha)
{
  QColor color(r,g,b,alpha);
  QPen pen(color);
  pen.setStyle(Qt::SolidLine);
  QGraphicsEllipseItem::setPen(pen);
  label->setDefaultTextColor(color);
  setZValue(10);

  for(int a=0; a < graf->intE(); a++){
    if(lineE[a]->WP() == id || lineE[a]->WK() == id){
      if((*linkM == true) || (*linkLk == true) || (*linkLs == true))
        lineE[a]->highlight(r,g,b,alpha);
      else
        lineE[a]->highlightDij(r,g,b,alpha);
     }
  }
}

/* metoda lightsoff
 *
 * koloruje wierzchołek na czarno
*/
void QVertex::lightsoff()
{
  highlight(0,0,0,255);
}

/* metoda lightsoff
 *
 * koloruje wierzchołek na szaro
*/
void QVertex::lightsoffDij()
{
  highlight(180,180,180,255);
}

/* metoda lightsoffAllNeighbours
 *
 * koloruje wierzchołek oraz wszystkie jego
 * incydentne krawędzie i wierzchołki na
 * czarno
*/
void QVertex::lightsoffAllNeighbours()
{
  highlightAllNeighbours(0,0,0,255);
  for(int a=0; a < graf->intE(); a++){
    if(lineE[a]->WP() == id || lineE[a]->WK() == id)
      lineE[a]->lightsoff();
  }
}

void QVertex::lightsoffAllNeighboursDij()
{
  highlight(0,255,0,255);
  for(int a=0; a < graf->intE(); a++){
    if(lineE[a]->WP() == id || lineE[a]->WK() == id)
      lineE[a]->lightsoffDij();
  }
}

/* znajduje wierzchołek o najmniejszym oszacowaniu drogi */
int QVertex::minV(QVertex **tab, int size)
{
  int min = -1;
  int id = -1;
  for(int i=0; i < size; i++){
    if(!tab[i]->isClicked()){
      if(min == -1){
        min = tab[i]->Droga();
        id = i;
      }
      else if(tab[i]->Droga() < min){
        min = tab[i]->Droga();
        id = i;
      }
    }
  }
  return id;
}


/* zwraca krawędź incydentną z danym wierzchołkiem
 * prowadzącą do wierzchołka Vx
*/
QEdge * QVertex::incidentEdge(int Vx)
{
  for(int i=0; i < graf->intE(); i++){
    if(lineE[i]->WP() == id){
      if(lineE[i]->WK() == Vx)
        return lineE[i];
    } else if(lineE[i]->WK() == id){
      if(lineE[i]->WP() == Vx)
        return lineE[i];
    }
  }
  return NULL;
}
