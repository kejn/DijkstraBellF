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
#ifndef WINDOW_HH
#define WINDOW_HH

#include <QWidget>
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QValidator>
#include <QCheckBox>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>

#include "Graph.hh"
#include "QEdge.hh"
#include "QVertex.hh"
#include "Sleeper.hh"

class Window : public QWidget
{
  Q_OBJECT

private:
  QGridLayout * gridLayout;    // layout okna / widget'u (siatka)
  QGridLayout * macierzLayout; // layout dla macierzy wag (siatka)
  QVBoxLayout * listaKLayout;  // layout dla listy krawedzi (pionowy)
  QGridLayout * listaSLayout;  // layout dla listy sasiadow (siatka)
  QHBoxLayout * algParamSetLayout; // layout dla przycisku i pól DIJ. (poziomy)
  QHBoxLayout * algExecSetLayout; // layout dla przycisku i pól BELL.FO. (poziomy)
  QHBoxLayout * sleeperLayout; // layout dla przełącznika szybkości animacji
  QGridLayout * DijkstraRouteLayout; // layout dla oszacowań drogi w alg DIJ.
  QScrollArea * scrollArea;    // obszar z możliwością przewijania (lista K)
  QScrollArea * scrollArea2;   // obszar z możliwością przewijania (lista S)
  QWidget     * scrollViewport; // kanał wyświetlania dla listy krawędzi
  QWidget     * scrollViewport2;// kanał wyświetlania dla listy sąsiadów

  QFormLayout * formLayout;    // formularz inicjacji grafu
  QVBoxLayout * buttonsLayout; // layout dla przycisków
  QLabel      * ready;         // etykieta paska stanu

  QPushButton * buttonGenerujGraf; // przycisk do generowania grafów
  QPushButton * buttonDijkstra;    // przycisk uruchamiania alg. DIJKSTRY
  QPushButton * buttonBellmanFord; // przycisk uruchamiania alg. BELLMANA-FORDA

  QPushButton * buttonMacierzWag; // przycisk wyświetlania macierzy wag
  QPushButton * buttonListaKrawedzi; // przycisk wyświetlania listy krawędzi
  QPushButton * buttonListaSasiadow; // przycisk wyświetlania listy sąsiadów

  QGraphicsScene * scenaRysowanie; // scena do rysowania grafu
  QGraphicsView  * view;           // widok dla sceny (^^^)

  unsigned long czasAnimacji;      // przechowuje czaas opóźnienia animacji [ms]
  Sleeper * sleeper;               // wątek uruchamiany do opóźnienia animacji
  QLabel * labelSleeper;           // etykieta dla pola edycji opóźnienia (^^^)
  QLineEdit * sleeperMs;           // pole edycji opóźnienia animacji
  QPushButton * buttonSleeper;     // przycisk zatwierdzający zmianę (^^^)

  QVertex ** elltextV;    // tablica dla wierzchołków (na scenie)
  QEdge   ** lineE;       // tablica dla krawędzi (na scenie)
  QLabel *** labelWagi;   // tablica (2D) dla etykiet macierzy wag
  QLabel **  labelListaK; // tablica dla etykiet listy krawędzi
  QLabel *** labelListaS; // tablica (2D) dla etykiet listy sąsiadów

  bool wyswietlMacierz; // czy wyświetlić macierz wag ?
  bool wyswietlListeK;  // czy wyświetlić listę krawędzi ?
  bool wyswietlListeS;  // czy wyświetlić listę sąsiadów ?

  Graph * graf; // wskaźnik na graf

  QValidator * zakresGestosc;     // kontroluje poprawność pola gęstość
  QValidator * zakresWierzcholki; // kontroluje poprawność pola editV
  QValidator * zakresRandMax;     // kontroluje poprawność pola randMax
  QLineEdit * editV;   // pole edycji liczby wierzchołków
  QLineEdit * editE;   // pole edycji liczby krawędzi (zablokowane, samo się liczy)
  QLineEdit * gestosc; // pole edycji gęstości grafu
  QLineEdit * randMax; // pole edycji maksymalnej losowanej wagi w grafie
  int         intV;       // wartość INT pola editV
  int         intE;       // wartość INT pola editE
  int         intGestosc; // wartość INT pola gestosc
  int         intRandMax; // wartość INT pola randMax

  const int   labelKHeight; // stała wartość wysokości dla etykiet

  QValidator * zakresAlgParam;
  QLineEdit * startingV;  // pole edycji wierzchołka startowego
  QLineEdit * targetV;    // pole edycji wierzchołka docelowego
  QLabel *** labelDrogi;  // tablica dla oszacowań najkrótszych dróg
  QLabel * labelAlgActive; // etykieta wskazująca aktywny wierzchołek
  QCheckBox * checkboxMST; // pozwala zdecydować, czy narysować MST czy nie

public:
  Window(); // deklaracja konstruktora

private slots:
  void SprawdzPolaFormSLOT();
  void SprawdzPolaDijkstraSLOT();

  void GenerujGrafSLOT();
  void RysujGrafSLOT();

  void GenerujMacierzWagSLOT();
  void RysujMacierzWagSLOT();

  void GenerujListeKrawedziSLOT();
  void RysujListeKrawedziSLOT();

  void GenerujListeSasiadowSLOT();
  void RysujListeSasiadowSLOT();

  void DijkstraSLOT();
  void BellmanFordSLOT();
  void ZablokujWKSLOT();

  void ukryjWynikiDijkstraSLOT();
  void szybkoscAnimacjiSLOT();
};

#endif // WINDOW_HH
