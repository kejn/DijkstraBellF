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
#ifndef SLEEPER_HH
#define SLEEPER_HH

#include <QThread>
#include <QWidget>
#include <QLineEdit>
#include <QCoreApplication>

// na potrzeby animacji, utworzona by skorzystać z przeciążonych metod *sleep()
class Sleeper : public QThread
{
  QWidget * p;
  unsigned long * value1;
  QLineEdit * value2;
public:
  Sleeper() : QThread() {}
  Sleeper(unsigned long * animationTimeout, QLineEdit *animationLineEdit) : QThread()
  {
    value1=animationTimeout;
    value2=animationLineEdit;
  }

  Sleeper(QWidget * parent=0) : QThread()
  {
   p=parent;
  }
  void usleep(unsigned long usecs)
  {
    QThread::usleep(usecs);
    p->repaint();
    QCoreApplication::processEvents();
  }
  void msleep(unsigned long msecs)
  {
    QThread::msleep(msecs);
    p->repaint();
    QCoreApplication::processEvents();
  }
  void sleep(unsigned long secs){
    QThread::sleep(secs);
    p->repaint();
    QCoreApplication::processEvents();
  }
  void updateAnimation()
  {
    if(value2 != NULL){
      QString skipchars("-_!,;. \t");
      foreach(QChar ch, skipchars)
        value2->setText(value2->text().remove(ch));
      int czasMs = value2->text().toInt();
      if(czasMs > 0)
        *value1 = czasMs;
    }
  }
};

#endif // SLEEPER_HH
