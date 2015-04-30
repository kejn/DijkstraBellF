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
#ifndef MWAG_HH
#define MWAG_HH

#include <cstddef>
#include "Vertex.hh"

/* klasa MWag (macierz wag)
 *
 * składa się z:
 * int *** tab - docelowo dwuwymiarowa tablica wskaźników;
 *               wskaźniki zaalokowane wraz z wartościami
 *               pokazują wagę połączenia wierzchołków:
 *               wiersz-kolumna; jeśli NULL to brak połączenia.
 * int size    - rozmiar macierzy (liczba wierszy / kolumn /
 *                                        wierzchołków grafu)
*/
class MWag {
  int *** tab;
  int     size;
public:
  MWag() : tab(NULL) { size = 0; }
  MWag(int V);
  void Wpisz(int,int,int);
  //void Wyswietl();
  int * operator()(Vertex,Vertex);
  int  Size() { return size; }
  ~MWag();
};

#endif // MWAG_HH
