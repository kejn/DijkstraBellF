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
#ifndef QREALMATRIX3X3_HH
#define QREALMATRIX3X3_HH

#include <QtCore/QtMath>
#include <QtCore/qmath.h>
#include "Wsp.hh"


/* klasa macierzy 3x3
 *
 * zdefiniowana do obliczania współrzędnych w jakich
 * mają zostać wyrysowane kolejne wierzchołki grafu.
*/
class QRealMatrix3x3 {
  qreal M[3][3];
public:
  QRealMatrix3x3()
  {
    for(int i=0; i < 3; i++){
        for(int j=0; j < 3; j++)
          M[i][j] = 0.0;
      }
  }
  QRealMatrix3x3(double angle) // macierz Rotacji
  {
    qreal a = (qreal) qDegreesToRadians(angle);
    M[0][0] = qCos(a); M[0][1] = -qSin(a); M[0][2] = 0.0;
    M[1][0] = qSin(a); M[1][1] =  qCos(a); M[1][2] = 0.0;
    M[2][0] =     0.0; M[2][1] =      0.0; M[2][2] = 1.0;
  }
  QRealMatrix3x3(qreal x, qreal y) // macierz Translacji
  {
    M[0][0] = 1.0; M[0][1] = 0.0; M[0][2] = x;
    M[1][0] = 0.0; M[1][1] = 1.0; M[1][2] = y;
    M[2][0] = 0.0; M[2][1] = 0.0; M[2][2] = 1.0;
  }
  Wsp getWsp() { return Wsp(M[0][2],M[1][2]); }
  qreal & operator()(const int & i, const int & j)
  {
    return M[i][j];
  }
  qreal operator()(const int & i, const int & j) const
  {
    return M[i][j];
  }
  Wsp operator*(const QRealMatrix3x3 & matrix) const
  {
    QRealMatrix3x3 result;
    for(int i=0; i < 3; i++){
      for(int j=0; j < 3; j++){
        for(int k=0; k < 3; k++)
          result(i,j) += M[i][k] * matrix(k,j);
      }
    }
    return result.getWsp();
  }
};

#endif // QREALMATRIX3X3_HH
