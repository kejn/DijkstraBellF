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
#ifndef GRAPH_HH
#define GRAPH_HH

#include "MWag.hh"
#include "LKrawedzi.hh"

/* Graf
  Opis:
  int    V         - liczba wierzchołków
  int    E         - liczba krawędzi
  int    maxRandom - możliwie maksymalna losowana waga
  int    gestosc   - gęstość grafu [0 - 100%]
  MWag * macierz   - macierz wag grafu
  std::list<Edge>   listaK - lista krawędzi grafu
  std::list<Edge> * listaS - lista sąsiadów grafu
*/
class Graph {
  int    V;
  int    E;
  int    maxRandom;
  int    gestosc;
  MWag * macierz;
  std::list<Edge>   listaK;
  std::list<Edge> * listaS;
public:
  Graph() { macierz=NULL; listaS=NULL;}
  Graph(int,int,int,int);
  void Generuj();
  MWag* MacierzWag() { return macierz; }
  std::list<Edge> * ListaKrawedzi() { return &listaK; }
  std::list<Edge> * ListaSasiadow(int i) { return &(listaS[i]); }
  int* MacierzWag(Vertex a, Vertex b) { return (*macierz)(a,b); }
  int  intV() { return V; }
  int  intE() { return E; }
  ~Graph();
};

#endif // GRAPH_HH
