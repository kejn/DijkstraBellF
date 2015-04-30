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
#ifndef WSP_HH
#define WSP_HH

class Wsp {
  qreal x;
  qreal y;
public:
  Wsp() {}
  Wsp(const Wsp &w)
  {
   x = w.getX();
   y = w.getY();
  }
  Wsp(qreal xVal, qreal yVal)
  {
    x = xVal;
    y = yVal;
  }
  void put(qreal xVal, qreal yVal)
  {
    x = xVal;
    y = yVal;
  }
  void put(Wsp a)
  {
    x = a.getX();
    y = a.getY();
  }
  qreal getX() const { return x; }
  qreal getY() const { return y; }
};

#endif // WSP_HH
