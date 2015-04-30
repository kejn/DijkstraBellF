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
#include "Graph.hh"
#include <cstdlib>

/* konstruktor parametryczny
 *
 * przypisuje podane parametry polom klasy
 * oraz alokuje pamięć na macierz wag
 * oraz listę sąsiadów (zmienne dynamiczne)
*/
Graph::Graph(int v, int e, int ro, int rnd)
{
  V=v; E=e; gestosc=ro; maxRandom=rnd;
  macierz = new MWag(V);
  listaS = new std::list<Edge>[V];
}


/* metoda Generuj
 *
 * na podstawie pól w klasie (liczba wierzchołków,
 * liczba krawędzi, maksymalna losowana waga) generuje
 * graf o zdefiniowanej wcześniej gęstości
*/
void Graph::Generuj()
{
  for(int i=0, j=0, k=1, wp, wk, waga; i < E; i++, j++){
    if(j == V){
      j=0;
      k++;
    }
    wp = j;
    wk = (j+k)%V;
    waga = 1+rand()%maxRandom;
    macierz->Wpisz(wp,wk,waga);
    listaK.push_back(Edge(wp,wk,waga));
    listaS[wp].push_back(Edge(wp,wk,waga));
    listaS[wk].push_back(Edge(wk,wp,waga));
  }
}


/* destruktor klasy
 *
 * zwalnia dynamicznie zaalokowaną pamięć
*/
Graph::~Graph()
{
  if(macierz){
    delete macierz;
    macierz = NULL;
  }
  if(listaS){
    delete [] listaS;
    listaS=NULL;
  }
}
