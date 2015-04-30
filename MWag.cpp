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
#include "MWag.hh"

/* konstruktor parametryczny
 *
 * alokuje pamięć na macierz wag i inicjuje jej pola NULLami
*/
MWag::MWag(int V)
{
  size = V;
  tab = new int**[size];
  for(int i=0; i < size; i++){
    tab[i] = new int*[size];
    for(int j=0; j < size; j++)
      tab[i][j] = NULL;
  }
}

/* metoda Wpisz
 *
 * wpisuje wagę VALUE w pola o położeniach
 * (i,j) oraz (j,i)
*/
void MWag::Wpisz(int i, int j, int value)
{
  tab[i][j] = new int;
  *tab[i][j] = value;
  tab[j][i] = new int;
  *tab[j][i] = value;
}

/* operator()
 *
 * pozwala na dostęp do pól macierzy spoza klasy
*/
int * MWag::operator()(Vertex a,Vertex b)
{
  return tab[a][b];
}

//void MWag::Wyswietl()
//{
//  for(int i=0; i < size; i++){
//    for(int j=0; j < size; j++){
//      if(tab[i][j] != NULL)
//        std::cout << *tab[i][j] << '\t';
//      else
//        std::cout << "-\t";
//    }
//    std::cout << std::endl;
//  }

//}



/* destruktor klasy
 *
 * zwalnia zaalokowaną pamięć
*/
MWag::~MWag()
{
  if(!tab){
    for(int i=0; i < size; i++){
      for(int j=0; j < size; j++){
        if(!tab[i][j]){
          delete tab[i][j];
          tab[i][j] = NULL;
        }
      }
      delete [] tab[i];
      tab[i] = NULL;
    }
  }
}
