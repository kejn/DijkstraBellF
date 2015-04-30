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
#ifndef EDGE_HH
#define EDGE_HH

#include <QLabel>
#include "Vertex.hh"

/* Krawędź
  Składa się z wierzchołków:
  - początkowego (wP),
  - końcowego (wK),
  wagi (waga) oraz etykiety (labelEdge)
*/
class Edge {
public:
  Vertex wP;
  Vertex wK;
  int    waga;
  QLabel * labelEdge;
  Edge() { labelEdge = NULL; }
  Edge(int b, int e, int w) { wP=b; wK=e; waga=w; labelEdge = NULL; }
  Edge(const Edge & e) { wP=e.wP; wK=e.wK; waga=e.waga; labelEdge = NULL; }
};

#endif // EDGE_HH
