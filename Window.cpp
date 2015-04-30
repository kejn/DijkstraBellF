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
#include <QApplication>
#include <QTextCodec>
#include <QPainter>
#include <QBrush>

#include "Window.hh"
#include "Wsp.hh"
#include "QRealMatrix3x3.hh"


#define PI 3.14159265358979323264
#define MAXSIZE 20

/* konstruktor domyślny klasy *
 * * * * * * * * * * * * * * *
 */
Window::Window() : labelKHeight(27)
{
  graf = NULL;
  labelWagi = NULL;
  lineE = NULL;
  elltextV = NULL;
  zakresAlgParam = NULL;
  labelDrogi = NULL;
  labelAlgActive = NULL;
  wyswietlMacierz = false;
  wyswietlListeK = false;
  wyswietlListeS = false;
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

  // [Layout init] -- start ////////////////////////////////////////////////////
  gridLayout = new QGridLayout;
  gridLayout->setContentsMargins(10,10,10,5);
  formLayout = new QFormLayout;
  macierzLayout = new QGridLayout;
  scrollViewport= new QWidget;
  scrollViewport2= new QWidget;
  listaKLayout = new QVBoxLayout(scrollViewport);
  listaSLayout = new QGridLayout(scrollViewport2);
  DijkstraRouteLayout = new QGridLayout;

  scrollArea= new QScrollArea;
  scrollArea->setMaximumWidth(this->width()/2);
  scrollArea->setMinimumHeight(this->height()-210);
  scrollArea->setWidget(scrollViewport);

  scrollArea2= new QScrollArea;
  scrollArea2->setMaximumWidth(this->width()/2);
  scrollArea2->setMinimumHeight(this->height()-210);
  scrollArea2->setWidget(scrollViewport2);

  scenaRysowanie = new QGraphicsScene;
  view = new QGraphicsView(scenaRysowanie);
  view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform \
                       | QPainter::HighQualityAntialiasing);
  view->setContentsMargins(0,0,0,0);
  view->setMinimumHeight(this->height()-220);
  gridLayout->addWidget(view,1,0);
  // [Layout init] -- end //////////////////////////////////////////////////////

  // [Formularz] -- start //////////////////////////////////////////////////////
  editV = new QLineEdit;
  editV->setPlaceholderText(tr("min. 2, max. ").append(QString::number(MAXSIZE)));
  editV->setMaximumHeight(labelKHeight);
  editE = new QLineEdit;
  editE->setMaximumHeight(labelKHeight);
  editE->setDisabled(true);
  gestosc = new QLineEdit(QString("100"));
  gestosc->setPlaceholderText(tr("0-100"));
  gestosc->setMaximumHeight(labelKHeight);
  randMax = new QLineEdit(QString("100"));
  randMax->setPlaceholderText(tr("min. 1, max. 1000"));
  randMax->setMaximumHeight(labelKHeight);

  formLayout->addRow(tr("Liczba wierzchołków"),editV);
  formLayout->addRow(tr("Liczba krawędzi"),editE);
  formLayout->addRow(tr("Gęstość grafu [%]"),gestosc);
  formLayout->addRow(tr("Maksymalna waga"),randMax);
  formLayout->setVerticalSpacing(5);

  zakresGestosc = new QIntValidator(0,100,this);
  zakresWierzcholki = new QIntValidator(0,MAXSIZE,this);
  zakresRandMax = new QIntValidator(0,1000,this);

  gestosc->setValidator(zakresGestosc);
  editV->setValidator(zakresWierzcholki);
  randMax->setValidator(zakresRandMax);

  connect(gestosc,SIGNAL(textChanged(QString)),this,SLOT(SprawdzPolaFormSLOT()));
  connect(editV,SIGNAL(textChanged(QString)),this,SLOT(SprawdzPolaFormSLOT()));
  connect(randMax,SIGNAL(textChanged(QString)),this,SLOT(SprawdzPolaFormSLOT()));

  buttonGenerujGraf = new QPushButton(tr("&Generuj graf"));
  formLayout->addWidget(buttonGenerujGraf);
  buttonGenerujGraf->setDisabled(true);
  buttonGenerujGraf->setMaximumHeight(labelKHeight);
  connect(buttonGenerujGraf,SIGNAL(clicked()),this,SLOT(GenerujGrafSLOT()));

  gridLayout->addLayout(formLayout,0,0,Qt::AlignTop);
  // [Formularz] -- end ////////////////////////////////////////////////////////

  // [Przyciski] -- start //////////////////////////////////////////////////////
  buttonsLayout = new QVBoxLayout;
  buttonsLayout->setSpacing(5);
  gridLayout->addLayout(buttonsLayout,0,1,Qt::AlignBottom);

  algExecSetLayout = new QHBoxLayout;
  algExecSetLayout->setSpacing(5);
  buttonsLayout->addItem(algExecSetLayout);

  buttonDijkstra = new QPushButton(tr("&Dijkstra"));
  algExecSetLayout->addWidget(buttonDijkstra);
  buttonDijkstra->setDisabled(true);
  buttonDijkstra->setMaximumHeight(labelKHeight);
  connect(buttonDijkstra,SIGNAL(clicked()),this,SLOT(DijkstraSLOT()));

  buttonBellmanFord = new QPushButton(tr("&Bellman-Ford"));
  algExecSetLayout->addWidget(buttonBellmanFord);
  buttonBellmanFord->setDisabled(true);
  buttonBellmanFord->setMaximumHeight(labelKHeight);
  connect(buttonBellmanFord,SIGNAL(clicked()),this,SLOT(BellmanFordSLOT()));

  algParamSetLayout = new QHBoxLayout;
  algParamSetLayout->setSpacing(5);
  buttonsLayout->addItem(algParamSetLayout);

  startingV = new QLineEdit;
  startingV->setPlaceholderText("wierzchołek startowy");
  startingV->setMaximumWidth(180);
  startingV->setMaximumHeight(labelKHeight);
  algParamSetLayout->addWidget(startingV);
  startingV->setDisabled(true);
  connect(startingV,SIGNAL(textChanged(QString)),this,SLOT(SprawdzPolaDijkstraSLOT()));

  targetV = new QLineEdit;
  targetV->setPlaceholderText("wierzchołek końcowy");
  targetV->setMaximumWidth(180);
  targetV->setMaximumHeight(labelKHeight);
  algParamSetLayout->addWidget(targetV);
  targetV->setDisabled(true);
  connect(targetV,SIGNAL(textChanged(QString)),this,SLOT(SprawdzPolaDijkstraSLOT()));

  checkboxMST = new QCheckBox(tr("drogi do &wszystkich wierzchołków"));
  checkboxMST->setDown(true);
  algParamSetLayout->addWidget(checkboxMST);
  connect(checkboxMST,SIGNAL(clicked()),this,SLOT(ZablokujWKSLOT()));
  connect(checkboxMST,SIGNAL(clicked()),this,SLOT(SprawdzPolaDijkstraSLOT()));

  buttonMacierzWag = new QPushButton(tr("&Macierz wag"));
  buttonsLayout->addWidget(buttonMacierzWag);
  buttonMacierzWag->setDisabled(true);
  buttonMacierzWag->setMaximumHeight(labelKHeight);
  connect(buttonMacierzWag,SIGNAL(clicked()),this,SLOT(RysujMacierzWagSLOT()));

  buttonListaKrawedzi = new QPushButton(tr("Lista &krawędzi"));
  buttonsLayout->addWidget(buttonListaKrawedzi);
  buttonListaKrawedzi->setDisabled(true);
  buttonListaKrawedzi->setMaximumHeight(labelKHeight);
  connect(buttonListaKrawedzi,SIGNAL(clicked()),this,SLOT(RysujListeKrawedziSLOT()));

  buttonListaSasiadow = new QPushButton(tr("Lista &sąsiadów"));
  buttonsLayout->addWidget(buttonListaSasiadow);
  buttonListaSasiadow->setDisabled(true);
  buttonListaSasiadow->setMaximumHeight(labelKHeight);
  connect(buttonListaSasiadow,SIGNAL(clicked()),this,SLOT(RysujListeSasiadowSLOT()));
  // [Przyciski] -- end ////////////////////////////////////////////////////////

  // [Pasek stanu] -- start
  ready = new QLabel(tr("Gotowy"));
  ready->setMaximumHeight(labelKHeight);
  gridLayout->addWidget(ready,2,0,Qt::AlignLeft);

  czasAnimacji = 500;
  sleeperLayout = new QHBoxLayout;
  labelSleeper = new QLabel(tr("Szybkość animacji [milisekundy]"));
  labelSleeper->setMaximumHeight(labelKHeight);
  buttonSleeper = new QPushButton(tr("OK"));
  buttonSleeper->setMaximumWidth(100);
  buttonSleeper->setMaximumHeight(labelKHeight);
  sleeperMs = new QLineEdit;
  sleeperMs->setPlaceholderText(tr("mniej -> szybciej (domyślnie: ").append(QString::number(czasAnimacji)).append(")"));
  sleeperMs->setMaximumWidth(300);
  sleeperMs->setMaximumHeight(labelKHeight);
  sleeperMs->setValidator(zakresRandMax);
  sleeper = new Sleeper(view->viewport());
  connect(sleeperMs,SIGNAL(returnPressed()),buttonSleeper,SIGNAL(clicked()));
  connect(buttonSleeper,SIGNAL(clicked()),this,SLOT(szybkoscAnimacjiSLOT()));
  sleeperLayout->addWidget(labelSleeper);
  sleeperLayout->addWidget(sleeperMs);
  sleeperLayout->addWidget(buttonSleeper);
  sleeperMs->setMaximumHeight(labelKHeight);
  sleeperLayout->setAlignment(labelSleeper,Qt::AlignRight);
  gridLayout->addLayout(sleeperLayout,2,1,Qt::AlignLeft);
  // [Pasek stanu] -- end

  setLayout(gridLayout);
  setMinimumSize(800,500);
  resize(1280,820);
}


void Window::RysujGrafSLOT()
{
  scenaRysowanie->clear();
  if(intV > MAXSIZE){
    buttonMacierzWag->setDisabled(true);
    buttonListaKrawedzi->setDisabled(true);
    buttonListaSasiadow->setDisabled(true);
    startingV->setDisabled(true);
    targetV->setDisabled(true);
    buttonDijkstra->setDisabled(true);
    QGraphicsTextItem * labelV = new QGraphicsTextItem;
    labelV->setPos(-50,-50);
    QString info("Aby odblokować rysowanie większych\ngrafów \
zmień makro MAXSIZE w pliku Window.cpp\n\nNA \
WŁASNE RYZYKO !!!\n\nObecny limit na liczbę wierzchołków: ");
    info.append(QString::number(MAXSIZE));
    labelV->setPlainText(info);
    scenaRysowanie->addItem(labelV);
    return;
  }
  if(elltextV != NULL)
    delete [] elltextV;
  if(lineE != NULL)
    delete [] lineE;

  qreal r = 30.0;
  qreal R = 3*r/(2*qSin(PI/((qreal)intV)));
  qreal x = R, y=0;
  double angle = (double)360.0/(double)intV;

  elltextV = new QVertex*[intV];
  for(int i = 0; i < intV; i++){
    // rysujemy wierzcholek + etykiete
      elltextV[i] = new QVertex(i,&wyswietlMacierz,&wyswietlListeK,\
                                &wyswietlListeS,x,y);
      scenaRysowanie->addItem(elltextV[i]);
    // obliczenie wsp kolejnego wierzcholka
    QRealMatrix3x3 Rot(angle), Trans(x,y);
    Wsp w = (Rot * Trans);
    x = w.getX();
    y = w.getY();
  }

  lineE = new QEdge*[intE];
  qreal x0,x1,y0,y1;
  for(int i=0, j=0, k=1; i < intE; i++, j++){
    if(j == intV){
      j=0;
      k++;
    }
    //rysujemy krawedz
    x0 = elltextV[j]->getWsp().getX()+r/2;
    y0 = elltextV[j]->getWsp().getY()+r/2;
    x1 = elltextV[(j+k)%intV]->getWsp().getX()+r/2;
    y1 = elltextV[(j+k)%intV]->getWsp().getY()+r/2;
    lineE[i] = new QEdge(j,(j+k)%intV, &wyswietlMacierz, &wyswietlListeK,\
                         &wyswietlListeS, x0,y0,x1,y1);
    lineE[i]->setPtrs(labelWagi,labelListaK,i,labelListaS,graf,elltextV);
    elltextV[j]->setPtrs(labelWagi,labelListaK,labelListaS,graf,lineE);
    elltextV[(j+k)%intV]->setPtrs(labelWagi,labelListaK,labelListaS,graf,lineE);
    scenaRysowanie->addItem(lineE[i]);
  }
}

void Window::SprawdzPolaFormSLOT()
{
  buttonMacierzWag->setDisabled(true);
  buttonListaKrawedzi->setDisabled(true);
  buttonListaSasiadow->setDisabled(true);
  buttonDijkstra->setDisabled(true);
  if(editV->text() != NULL){
    if(gestosc->text() != NULL){
      if(randMax->text() != NULL){
        QString skipchars("-_!,;. \t");
        foreach(QChar ch, skipchars){
          editV->setText(editV->text().remove(ch));
          gestosc->setText(gestosc->text().remove(ch));
          randMax->setText(randMax->text().remove(ch));
        }
        intV = (*editV).text().toInt();
        intGestosc = (*gestosc).text().toInt();
        intRandMax = (*randMax).text().toInt();
        intE = intV * (intV-1) * intGestosc / 200;
        editE->setText(QString::number(intE));
        if(intE > 0){
          if(intRandMax > 0)
            buttonGenerujGraf->setDisabled(false);
        } else
          buttonGenerujGraf->setDisabled(true);
      } else {
          buttonGenerujGraf->setDisabled(true);
      }
    } else {
        buttonGenerujGraf->setDisabled(true);
    }
  } else {
    buttonGenerujGraf->setDisabled(true);
  }
}
void Window::SprawdzPolaDijkstraSLOT(){
  buttonDijkstra->setDisabled(true);
  buttonBellmanFord->setDisabled(true);
  if(startingV->text() != NULL){
    if(!checkboxMST->isChecked()){
      if(targetV->text() != NULL){
        QString skipchars("-_!,;. \t");
        foreach(QChar ch, skipchars){
          startingV->setText(startingV->text().remove(ch));
          targetV->setText(targetV->text().remove(ch));
        }
        int start = startingV->text().toInt();
        int target = targetV->text().toInt();
        if(start > 0 && start <= intV){
          if(target > 0 && target <= intV){
            buttonDijkstra->setDisabled(false);
            buttonBellmanFord->setDisabled(false);
          }
        }
      }
    } else {
      buttonDijkstra->setDisabled(false);
      buttonBellmanFord->setDisabled(false);
    }
  } else {
    buttonDijkstra->setDisabled(true);
    buttonBellmanFord->setDisabled(true);
  }
}

void Window::RysujListeSasiadowSLOT()
{
  ready->setText(tr("Rysuję listę sąsiadów..."));
  if(wyswietlListeS){
    for(int i=0; i < graf->intV(); i++){
      listaSLayout->removeWidget(labelListaS[i][0]);
      delete labelListaS[i][0];
      std::list<Edge>::iterator iter = graf->ListaSasiadow(i)->begin();
      for(int j=1; iter != graf->ListaSasiadow(i)->end(); ++iter, j++){
        listaSLayout->removeWidget(labelListaS[i][j]);
        delete labelListaS[i][j];
      }
      delete [] labelListaS[i];
    }
    delete [] labelListaS;
    labelListaS = NULL;
    gridLayout->removeWidget(scrollArea2);
    scrollArea2->setVisible(false);
    buttonListaSasiadow->setDisabled(false);
  } else {
    ukryjWynikiDijkstraSLOT();
    if(wyswietlMacierz)
      RysujMacierzWagSLOT();
    else if(wyswietlListeK)
      RysujListeKrawedziSLOT();
    gridLayout->addWidget(scrollArea2,1,1,Qt::AlignTop);
    GenerujListeSasiadowSLOT();
    int tmp=10;
    int zeros=2;
    while(intRandMax/tmp > 0){
      tmp*=100;
      zeros++;
    }
    scrollViewport2->resize(intV*zeros*labelKHeight,intV*labelKHeight);
    scrollArea2->setVisible(true);
    buttonMacierzWag->setDisabled(false);
    buttonListaKrawedzi->setDisabled(false);
    buttonListaSasiadow->setDisabled(true);
    RysujGrafSLOT();
    scrollArea2->setMinimumHeight(this->height()-210);
    scrollArea2->setMaximumWidth(this->width()/2);
    //scrollViewport2->setMinimumHeight(this->height()-210);
  }
  wyswietlListeS = !wyswietlListeS;

  ready->setText(tr("Gotowy"));
}

void Window::GenerujListeSasiadowSLOT()
{
  QPalette palette;
  QBrush brush(QColor(0,0,0,255));
  brush.setStyle(Qt::SolidPattern);

  palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
  palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);

  const int size = intV;
  int zeros, tmp;

  labelListaS = new QLabel**[size];

  for(int i=0; i < size; i++){
    std::list<Edge>::iterator iter = graf->ListaSasiadow(i)->begin();
    labelListaS[i] = new QLabel*[size+1];
    QString label("V");
    tmp=10;
    zeros=0;
    while(intV/tmp > 0){
      tmp*=10;
      zeros++;
    }
    for(int z=(i+1)/10; z < zeros; z++)
      label.append(QString::number(0));
    label.append(QString::number(i+1));
    label.append(" : ");
    labelListaS[i][0] = new QLabel(label);
    listaSLayout->addWidget(labelListaS[i][0],i,0);
    for(int j=1; iter != graf->ListaSasiadow(i)->end(); ++iter, j++){
        label.clear();
        label.append("(V");
        for(int z=intV/10; z < zeros; z++)
          label.append(QString::number(0));
        label.append(QString::number(iter->wK+1));
        label.append(",");
        label.append(QString::number(iter->waga));
        label.append(")");
        labelListaS[i][j] = new QLabel(label,scrollViewport2);
        labelListaS[i][j]->setMinimumHeight(labelKHeight);
        labelListaS[i][j]->setPalette(palette);
        listaSLayout->addWidget(labelListaS[i][j],i,j);
    }
  }
}

void Window::RysujListeKrawedziSLOT()
{
  ready->setText(tr("Rysuję listę krawędzi..."));
  if(wyswietlListeK){
    for(int i=0; i < graf->intE(); i++){
      listaKLayout->removeWidget(labelListaK[i]);
      delete labelListaK[i];
    }
    delete [] labelListaK;
    labelListaK = NULL;
    gridLayout->removeWidget(scrollArea);
    scrollArea->setVisible(false);
    buttonListaKrawedzi->setDisabled(false);
  } else {
    ukryjWynikiDijkstraSLOT();
    if(wyswietlMacierz)
      RysujMacierzWagSLOT();
    else if(wyswietlListeS)
      RysujListeSasiadowSLOT();
    gridLayout->addWidget(scrollArea,1,1,Qt::AlignTop);
    GenerujListeKrawedziSLOT();
    scrollViewport->resize(580,intE*labelKHeight);
    scrollArea->setVisible(true);
    buttonMacierzWag->setDisabled(false);
    buttonListaKrawedzi->setDisabled(true);
    buttonListaSasiadow->setDisabled(false);
    RysujGrafSLOT();
    scrollArea->setMinimumHeight(this->height()-210);
    scrollArea->setMaximumWidth(this->width()/2);
    scrollViewport->setMinimumHeight(this->height()-210);
  }
  wyswietlListeK = !wyswietlListeK;

  ready->setText(tr("Gotowy"));
}

void Window::GenerujListeKrawedziSLOT()
{
  QPalette palette;
  QBrush brush(QColor(0,0,0,255));
  brush.setStyle(Qt::SolidPattern);

  palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
  palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);

  const int size = intE;
  int zeros=0, tmp=10;

  labelListaK = new QLabel*[size];

  std::list<Edge>::iterator iter = graf->ListaKrawedzi()->begin();
  for(int k=0; iter != graf->ListaKrawedzi()->end(); ++iter, k++){// k < size
    while(intV/tmp > 0){
      tmp*=10;
      zeros++;
    }
    QString label("V");
    for(int z=(iter->wP+1)/10; z < zeros; z++)
      label.append(QString::number(0));
    label.append(QString::number(iter->wP+1));
    label.append(" - V");
    for(int z=(iter->wK+1)/10; z < zeros; z++)
      label.append(QString::number(0));
    label.append(QString::number(iter->wK+1));
    label.append("   :   ");
    label.append(QString::number(iter->waga));
    iter->labelEdge = new QLabel(label,scrollViewport);
    iter->labelEdge->setMinimumHeight(labelKHeight);
    labelListaK[k] = iter->labelEdge;
    labelListaK[k]->setPalette(palette);
    listaKLayout->addWidget(labelListaK[k]);
  }
}

void Window::RysujMacierzWagSLOT()
{
  ready->setText(tr("Rysuję macierz wag..."));
  if(wyswietlMacierz){
    for(int i=0; i < graf->intV(); i++){
      for(int j=0; j < graf->intV(); j++){
        macierzLayout->removeWidget(labelWagi[i][j]);
        delete labelWagi[i][j];
      }
      delete [] labelWagi[i];
    }
    delete [] labelWagi;
    labelWagi = NULL;
    gridLayout->removeItem(macierzLayout);
    buttonMacierzWag->setDisabled(false);
  } else {
    ukryjWynikiDijkstraSLOT();
    if(wyswietlListeK)
      RysujListeKrawedziSLOT();
    else if(wyswietlListeS)
      RysujListeSasiadowSLOT();
    GenerujMacierzWagSLOT();
    gridLayout->addLayout(macierzLayout,1,1,Qt::AlignBaseline);
    for(int i=0; i < intV; i++){
      for(int j=0; j < intV; j++){
        macierzLayout->addWidget(labelWagi[i][j],i,j,Qt::AlignCenter);
      }
    }
    buttonMacierzWag->setDisabled(true);
    buttonListaKrawedzi->setDisabled(false);
    buttonListaSasiadow->setDisabled(false);
    RysujGrafSLOT();
  }
  wyswietlMacierz = !wyswietlMacierz;

  ready->setText(tr("Gotowy"));
}

void Window::GenerujMacierzWagSLOT()
{
  QPalette palette;
  QBrush brush(QColor(0,0,0,255));
  brush.setStyle(Qt::SolidPattern);

  palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
  palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);

  const int size = intV;
  labelWagi = new QLabel**[size];

  for(int i=0; i < size; i++){
    labelWagi[i] = new QLabel*[size];
    for(int j=0; j < size; j++){
        labelWagi[i][j] = new QLabel;
        if(graf->MacierzWag(i,j) == NULL)
          labelWagi[i][j]->setText("-");
        else
          labelWagi[i][j]->setText(QString::number(*(graf->MacierzWag(i,j))));
        labelWagi[i][j]->setPalette(palette);
    }
  }
}

void Window::GenerujGrafSLOT()
{
  int opcja = 1;
  buttonGenerujGraf->setDisabled(true);
  buttonDijkstra->setDisabled(true);
  buttonBellmanFord->setDisabled(true);
  buttonMacierzWag->setDisabled(true);
  buttonListaKrawedzi->setDisabled(true);
  buttonListaSasiadow->setDisabled(true);
  ready->setText(tr("Generuję graf..."));
  QApplication::processEvents();

  if(wyswietlMacierz){
    RysujMacierzWagSLOT();
  }

  if(wyswietlListeK){
    RysujListeKrawedziSLOT();
    opcja = 2;
  }

  if(wyswietlListeS){
    RysujListeSasiadowSLOT();
    opcja = 3;
  }

  ukryjWynikiDijkstraSLOT();

  if(graf != NULL){
    delete graf;
    graf = NULL;
  }

  graf = new Graph(intV,intE,intGestosc,intRandMax);
  graf->Generuj();

  if(zakresAlgParam)
    delete zakresAlgParam;
  zakresAlgParam = new QIntValidator(1,intV);
  startingV->setValidator(zakresAlgParam);
  targetV->setValidator(zakresAlgParam);

  if(intV < MAXSIZE+1){
    if(opcja==1)
      RysujMacierzWagSLOT();
    if(opcja==2)
      RysujListeKrawedziSLOT();
    if(opcja==3)
      RysujListeSasiadowSLOT();
    startingV->setDisabled(false);
    targetV->setDisabled(false);
  } else
    RysujGrafSLOT();
  ready->setText(tr("Gotowy"));
  buttonGenerujGraf->setDisabled(false);
  buttonDijkstra->setDisabled(true);
  startingV->setText(tr(""));
  targetV->setText(tr(""));
  if(intE < intV){
    startingV->setDisabled(true);
    targetV->setDisabled(true);
  } else if(checkboxMST->isChecked())
    targetV->setDisabled(true);
}

void Window::ukryjWynikiDijkstraSLOT()
{
  if(labelDrogi != NULL){
    gridLayout->removeItem(DijkstraRouteLayout);
    DijkstraRouteLayout->removeWidget(labelAlgActive);
    if(labelAlgActive != NULL){
      delete labelAlgActive;
      labelAlgActive = NULL;
    }
    for(int i=0; i < graf->intV(); i++){
      DijkstraRouteLayout->removeWidget(labelDrogi[i][0]);
      delete labelDrogi[i][0];
      DijkstraRouteLayout->removeWidget(labelDrogi[i][1]);
      delete labelDrogi[i][1];
      delete [] labelDrogi[i];
    }
    delete [] labelDrogi;
    labelDrogi = NULL;
  }
}

void Window::szybkoscAnimacjiSLOT()
{
  Sleeper layoutThread(&czasAnimacji,sleeperMs);
  layoutThread.updateAnimation();
}

/* Animacja algorytmu DIJKSTRY *
 * * * * * * * * * * * * * * * *
*/
void Window::DijkstraSLOT()
{
  // blokujemy pola edycji i przyciski, które mogłyby wysypać program
  editV->setDisabled(true);
  gestosc->setDisabled(true);
  randMax->setDisabled(true);
  startingV->setDisabled(true);
  targetV->setDisabled(true);
  buttonDijkstra->setDisabled(true);
  buttonBellmanFord->setDisabled(true);
  buttonGenerujGraf->setDisabled(true);
  checkboxMST->setDisabled(true);

  // rysujemy graf od nowa i robimy miejsce na oszacowania dróg
  RysujListeSasiadowSLOT();
  if(wyswietlMacierz)
    RysujMacierzWagSLOT();
  if(wyswietlListeK)
    RysujListeKrawedziSLOT();
  if(wyswietlListeS)
    RysujListeSasiadowSLOT();
  // wyłączamy jeszcze te przyciski, żeby nic nie popsuć
  buttonMacierzWag->setDisabled(true);
  buttonListaKrawedzi->setDisabled(true);
  buttonListaSasiadow->setDisabled(true);

  int start = startingV->text().toInt()-1;
  int cel = (checkboxMST->isChecked())?-1:(targetV->text().toInt()-1);
  int size;
  int aktywny;
  int INF = 100000;
  const int labelDrogiSize = intV;

  // [kolorowanki] -- start
  QPalette black, blue;
  QBrush blackB(Qt::black), blueB(Qt::blue);
  blackB.setStyle(Qt::SolidPattern);
  blueB.setStyle(Qt::SolidPattern);
  black.setBrush(QPalette::Active, QPalette::WindowText, blackB);
  black.setBrush(QPalette::Inactive, QPalette::WindowText, blackB);
  blue.setBrush(QPalette::Active, QPalette::WindowText, blueB);
  blue.setBrush(QPalette::Inactive, QPalette::WindowText, blueB);
  view->setBackgroundBrush(QBrush(QColor(255,0,0,10)));
  // [kolorowanki] -- end

  if(labelDrogi != NULL){
    gridLayout->removeItem(DijkstraRouteLayout);
    DijkstraRouteLayout->removeWidget(labelAlgActive);
    delete labelAlgActive;
    for(int i=0; i < graf->intV(); i++){
      DijkstraRouteLayout->removeWidget(labelDrogi[i][0]);
      delete labelDrogi[i][0];
      DijkstraRouteLayout->removeWidget(labelDrogi[i][1]);
      delete labelDrogi[i][1];
      delete [] labelDrogi[i];
    }
    delete [] labelDrogi;
  }

  labelDrogi = new QLabel**[labelDrogiSize];

  for(int i=0; i < intV; i++){
    elltextV[i]->setDroga(INF);
    elltextV[i]->setPrev(-1); // niezdefiniowany poprzednik
    elltextV[i]->setAcceptHoverEvents(false);
    labelDrogi[i] = new QLabel*[2];
    labelDrogi[i][0] = new QLabel(QString(tr("V").append(QString::number(i+1))));
    labelDrogi[i][0]->setPalette(black);
    labelDrogi[i][1] = new QLabel(tr(" : nie oszacowano"));
    labelDrogi[i][1]->setPalette(black);
    DijkstraRouteLayout->addWidget(labelDrogi[i][0],i,0,Qt::AlignLeft);
    DijkstraRouteLayout->addWidget(labelDrogi[i][1],i,1,Qt::AlignLeft);
  }
  gridLayout->addLayout(DijkstraRouteLayout,1,1,Qt::AlignTop | Qt::AlignLeft);
  labelAlgActive = new QLabel(tr(" <--- aktywny wierzchołek"));

  elltextV[start]->setDroga(0);    // odleglosc start-start jest rowna zero
  elltextV[start]->setPrev(start);  // poprzednika juz nie ma
  labelDrogi[start][1]->setText(tr(" : 0"));
  aktywny = start;        // aktywujemy wierzcholek startowy
  size=1;

  // dopóki nie przejżeliśmy wszystkich wierzchołków... :
  while(size < intV){
    DijkstraRouteLayout->addWidget(labelAlgActive,aktywny,2,Qt::AlignLeft);
    // aktywacja wierzchołka !
    elltextV[aktywny]->Click();
    ready->setText(tr("Szukam najkrótszej drogi... Aktywny wierzchołek: ").append(QString::number(aktywny+1)));
    // podświetlamy wszystkich wcześniej nieaktywnych sąsiadów
    elltextV[aktywny]->highlightAllNeighbours(255,0,0,255);
    sleeper->msleep(czasAnimacji);
    // podświetlamy wszystkie wierzchołki incydentne z aktywnym
    // o ile nie były wcześniej aktywowane
    if(!graf->ListaSasiadow(aktywny)->empty()){
      std::list<Edge>::iterator iter = graf->ListaSasiadow(aktywny)->begin();
      for( ; iter != graf->ListaSasiadow(aktywny)->end(); ++iter){
        // czy istnieje krawędź (aktywny,iter->wK) ?
        if(graf->MacierzWag()->operator ()(aktywny,iter->wK)){
          // czy był już aktywowany ?
          if(elltextV[iter->wK]->isClicked())
            continue;
          // czy bieżące oszacowanie jest większe od nowego ?
          if(elltextV[iter->wK]->Droga() > elltextV[aktywny]->Droga() + iter->waga){
            elltextV[iter->wK]->setDroga(elltextV[aktywny]->Droga() + iter->waga);
            elltextV[iter->wK]->setPrev(aktywny);
            elltextV[iter->wK]->incidentEdge(aktywny)->highlight(0,0,255,255);
            labelDrogi[iter->wK][1]->setText(tr(" : ").append(QString::number(elltextV[iter->wK]->Droga())));
            labelDrogi[iter->wK][0]->setPalette(blue);
            labelDrogi[iter->wK][1]->setPalette(blue);
            sleeper->msleep(czasAnimacji);
            elltextV[iter->wK]->incidentEdge(aktywny)->lightsoffDij();
            labelDrogi[iter->wK][0]->setPalette(black);
            labelDrogi[iter->wK][1]->setPalette(black);
          }
        }
      }
      elltextV[aktywny]->lightsoffAllNeighboursDij();
      sleeper->msleep(czasAnimacji);
    }
    sleeper->msleep(czasAnimacji);
    aktywny = QVertex::minV(elltextV,intV);
    DijkstraRouteLayout->removeWidget(labelAlgActive);
    size++;
  }
  elltextV[aktywny]->highlight(0,255,0,255);

  if(cel > 0) {
    aktywny = cel;
    // pokazuje najkrótszą ścieżkę od wierzchołka startowego do końcowego
    elltextV[aktywny]->highlight(0,0,255,255);
    sleeper->msleep(czasAnimacji);
    do {
      for(int a=0; a < intE; a++){
        if(lineE[a]->WK() == aktywny){
          if(lineE[a]->WP() == elltextV[aktywny]->Prev()){
            lineE[a]->highlight(0,0,255,255);
            aktywny = lineE[a]->WP();
            sleeper->msleep(czasAnimacji);
            break;
          }
        } else if(lineE[a]->WP() == aktywny){
          if(lineE[a]->WK() == elltextV[aktywny]->Prev()){
            lineE[a]->highlight(0,0,255,255);
            aktywny = lineE[a]->WK();
            sleeper->msleep(czasAnimacji);
            break;
          }
        }
      }
    } while(elltextV[aktywny]->Prev() != aktywny);
    ready->setText("Gotowy. Najkrótsza droga: " + QString::number(elltextV[cel]->Droga()));
    labelAlgActive->setText(tr(" <--- najkrótsza droga z ").append(labelDrogi[start][0]->text()));
    DijkstraRouteLayout->addWidget(labelAlgActive,cel,2,Qt::AlignLeft);
    labelDrogi[cel][0]->setPalette(blue);
    labelDrogi[cel][1]->setPalette(blue);
    labelAlgActive->setPalette(blue);
    labelDrogi[start][0]->setText(tr("start"));
    labelDrogi[cel][0]->setText(tr("cel"));
    elltextV[start]->Label()->setHtml(tr("<div style='background-color: white; color: blue;'>start</div>"));
    elltextV[start]->Label()->setPos(elltextV[start]->getWsp().getX()-5, \
                                     elltextV[start]->getWsp().getY()+2);
    elltextV[cel]->Label()->setHtml(tr("<div style='background-color: white; color: blue;'>cel</div>"));
    elltextV[cel]->Label()->setPos(elltextV[cel]->getWsp().getX()+1, \
                                     elltextV[cel]->getWsp().getY()+2);
  } else {
    labelAlgActive->setText(tr(""));
    for(int i=0; i < intV; i++){
      aktywny = i;
      bool goOn = true;
      // pokazuje najkrótszą ścieżkę od wierzchołka startowego do końcowego
      elltextV[aktywny]->highlight(0,0,255,255);
      sleeper->msleep(czasAnimacji);
      do {
        for(int a=0; a < intE; a++){
          if(lineE[a]->WK() == aktywny){
            if(lineE[a]->WP() == elltextV[aktywny]->Prev()){
              if(lineE[a]->isBlue){
                goOn=false;
                break;
              }
              lineE[a]->highlight(0,0,255,255);
              lineE[a]->isBlue = true;
              aktywny = lineE[a]->WP();
              sleeper->msleep(czasAnimacji);
              break;
            }
          } else if(lineE[a]->WP() == aktywny){
            if(lineE[a]->WK() == elltextV[aktywny]->Prev()){
              if(lineE[a]->isBlue){
                goOn=false;
                break;
              }
              lineE[a]->highlight(0,0,255,255);
              lineE[a]->isBlue = true;
              aktywny = lineE[a]->WK();
              sleeper->msleep(czasAnimacji);
              break;
            }
          }
        }
      } while(elltextV[aktywny]->Prev() != aktywny && goOn);
      labelDrogi[i][0]->setPalette(blue);
      labelDrogi[i][1]->setPalette(blue);
    }
    labelDrogi[start][0]->setText(tr("start"));
    elltextV[start]->Label()->setHtml(tr("<div style='background-color: white; color: blue;'>start</div>"));
    elltextV[start]->Label()->setPos(elltextV[start]->getWsp().getX()-5, \
                                     elltextV[start]->getWsp().getY()+2);
    ready->setText("Gotowy.");
  }

  view->setBackgroundBrush(QBrush(QColor(255,255,255,255)));
  // odblokowujemy interfejs
  buttonDijkstra->setDisabled(false);
  buttonBellmanFord->setDisabled(false);
  buttonGenerujGraf->setDisabled(false);
  buttonMacierzWag->setDisabled(false);
  buttonListaKrawedzi->setDisabled(false);
  buttonListaSasiadow->setDisabled(false);
  startingV->setDisabled(false);
  if(!checkboxMST->isChecked())
    targetV->setDisabled(false);
  editV->setDisabled(false);
  gestosc->setDisabled(false);
  randMax->setDisabled(false);
  checkboxMST->setDisabled(false);
}

void Window::ZablokujWKSLOT()
{
  if(checkboxMST->isChecked()){
    targetV->setDisabled(true);
    targetV->clear();
  } else if(graf != NULL)
    targetV->setDisabled(false);
}

/* Animacja algorytmu BELLMANA-FORDA *
 * * * * * * * * * * * * * * * * * * *
*/
void Window::BellmanFordSLOT()
{
  // blokujemy pola edycji i przyciski, które mogłyby wysypać program
  editV->setDisabled(true);
  gestosc->setDisabled(true);
  randMax->setDisabled(true);
  startingV->setDisabled(true);
  targetV->setDisabled(true);
  buttonDijkstra->setDisabled(true);
  buttonBellmanFord->setDisabled(true);
  buttonGenerujGraf->setDisabled(true);
  checkboxMST->setDisabled(true);

  // rysujemy graf od nowa i robimy miejsce na oszacowania dróg
  RysujListeSasiadowSLOT();
  if(wyswietlMacierz)
    RysujMacierzWagSLOT();
  if(wyswietlListeK)
    RysujListeKrawedziSLOT();
  if(wyswietlListeS)
    RysujListeSasiadowSLOT();
  // wyłączamy jeszcze te przyciski, żeby nic nie popsuć
  buttonMacierzWag->setDisabled(true);
  buttonListaKrawedzi->setDisabled(true);
  buttonListaSasiadow->setDisabled(true);

  int start = startingV->text().toInt()-1;
  int cel = (checkboxMST->isChecked())?-1:(targetV->text().toInt()-1);
  int aktywny;
  int INF = 100000;
  bool zrelaksowano=true;
  bool ucykl=false;
  const int labelDrogiSize = intV;

  // [kolorowanki] -- start
  QPalette black, blue;
  QBrush blackB(Qt::black), blueB(Qt::blue);
  blackB.setStyle(Qt::SolidPattern);
  blueB.setStyle(Qt::SolidPattern);
  black.setBrush(QPalette::Active, QPalette::WindowText, blackB);
  black.setBrush(QPalette::Inactive, QPalette::WindowText, blackB);
  blue.setBrush(QPalette::Active, QPalette::WindowText, blueB);
  blue.setBrush(QPalette::Inactive, QPalette::WindowText, blueB);
  view->setBackgroundBrush(QBrush(QColor(255,0,0,10)));
  // [kolorowanki] -- end

  if(labelDrogi != NULL){
    gridLayout->removeItem(DijkstraRouteLayout);
    DijkstraRouteLayout->removeWidget(labelAlgActive);
    delete labelAlgActive;
    for(int i=0; i < graf->intV(); i++){
      DijkstraRouteLayout->removeWidget(labelDrogi[i][0]);
      delete labelDrogi[i][0];
      DijkstraRouteLayout->removeWidget(labelDrogi[i][1]);
      delete labelDrogi[i][1];
      delete [] labelDrogi[i];
    }
    delete [] labelDrogi;
  }

  labelDrogi = new QLabel**[labelDrogiSize];

  for(int i=0; i < intV; i++){
    elltextV[i]->setDroga(INF);
    elltextV[i]->setPrev(-1); // niezdefiniowany poprzednik
    elltextV[i]->setAcceptHoverEvents(false);
    labelDrogi[i] = new QLabel*[2];
    labelDrogi[i][0] = new QLabel(QString(tr("V").append(QString::number(i+1))));
    labelDrogi[i][0]->setPalette(black);
    labelDrogi[i][1] = new QLabel(tr(" : nie oszacowano"));
    labelDrogi[i][1]->setPalette(black);
    DijkstraRouteLayout->addWidget(labelDrogi[i][0],i,0,Qt::AlignLeft);
    DijkstraRouteLayout->addWidget(labelDrogi[i][1],i,1,Qt::AlignLeft);
  }
  gridLayout->addLayout(DijkstraRouteLayout,1,1,Qt::AlignTop | Qt::AlignLeft);

  sleeper->msleep(czasAnimacji);

  elltextV[start]->setDroga(0);    // odleglosc start-start jest rowna zero
  elltextV[start]->setPrev(start);  // poprzednika juz nie ma
  labelDrogi[start][1]->setText(tr(" : 0"));

  sleeper->msleep(czasAnimacji);

  // tyle razy ile jest wierzchołków (o ile doszło do relaksacji)
  for(int i=0; i < intV-1; i++){
    // na początku zakładamy że nie doszło do relaksacji
    zrelaksowano=false;
    // dla każdej krawędzi
    for(int j=0; j < intE; j++){
      int wp = lineE[j]->WP();
      int wk = lineE[j]->WK();
      // jeżeli nowe oszacowanie jest lepsze
      if(elltextV[wp]->Droga() > elltextV[wk]->Droga() + lineE[j]->Droga()){
        // to poprawiamy
        elltextV[wp]->setDroga(elltextV[wk]->Droga() + lineE[j]->Droga());
        elltextV[wp]->setPrev(wk);
        lineE[j]->highlight(0,0,255,255);
        labelDrogi[wp][1]->setText(tr(" : ").append(QString::number(elltextV[wp]->Droga())));
        labelDrogi[wp][0]->setPalette(blue);
        labelDrogi[wp][1]->setPalette(blue);
        sleeper->msleep(czasAnimacji);
        lineE[j]->lightsoffDij();
        labelDrogi[wp][0]->setPalette(black);
        labelDrogi[wp][1]->setPalette(black);
        zrelaksowano=true;
      } else
      if(elltextV[wk]->Droga() > elltextV[wp]->Droga() + lineE[j]->Droga()){
        // to poprawiamy
        elltextV[wk]->setDroga(elltextV[wp]->Droga() + lineE[j]->Droga());
        elltextV[wk]->setPrev(wp);
        lineE[j]->highlight(0,0,255,255);
        labelDrogi[wk][1]->setText(tr(" : ").append(QString::number(elltextV[wk]->Droga())));
        labelDrogi[wk][0]->setPalette(blue);
        labelDrogi[wk][1]->setPalette(blue);
        sleeper->msleep(czasAnimacji);
        lineE[j]->lightsoffDij();
        labelDrogi[wk][0]->setPalette(black);
        labelDrogi[wk][1]->setPalette(black);
        zrelaksowano=true;
      }
      else
        lineE[j]->lightsoffDij();
    }
    if(!zrelaksowano) break;
  }
  // sprawdzamy czy graf zawiera ujemne cykle
  for(int j=0; j < intE; j++){
    int wp = lineE[j]->WP();
    int wk = lineE[j]->WK();
    if(elltextV[wp]->Droga() > elltextV[wk]->Droga() + lineE[j]->Droga()){
      ready->setText("Stop ! Graf zawiera ujemny cykl.");
      ucykl = true;
      break;
    } else
    if(elltextV[wk]->Droga() > elltextV[wp]->Droga() + lineE[j]->Droga()){
      ready->setText("Stop ! Graf zawiera ujemny cykl.");
      ucykl = true;
      break;
    }
  }
  if(ucykl);
  else {
    if(cel > 0) {
      aktywny = cel;
      // pokazuje najkrótszą ścieżkę od wierzchołka startowego do końcowego
      elltextV[aktywny]->highlight(0,0,255,255);
      sleeper->msleep(czasAnimacji);
      do {
        for(int a=0; a < intE; a++){
          if(lineE[a]->WK() == aktywny){
            if(lineE[a]->WP() == elltextV[aktywny]->Prev()){
              lineE[a]->highlight(0,0,255,255);
              aktywny = lineE[a]->WP();
              sleeper->msleep(czasAnimacji);
              break;
            }
          } else if(lineE[a]->WP() == aktywny){
            if(lineE[a]->WK() == elltextV[aktywny]->Prev()){
              lineE[a]->highlight(0,0,255,255);
              aktywny = lineE[a]->WK();
              sleeper->msleep(czasAnimacji);
              break;
            }
          }
        }
      } while(elltextV[aktywny]->Prev() != aktywny);
      ready->setText("Gotowy. Najkrótsza droga: " + QString::number(elltextV[cel]->Droga()));
      labelAlgActive = new QLabel(tr(" <--- najkrótsza droga z ").append(labelDrogi[start][0]->text()));
      DijkstraRouteLayout->addWidget(labelAlgActive,cel,2,Qt::AlignLeft);
      labelDrogi[cel][0]->setPalette(blue);
      labelDrogi[cel][1]->setPalette(blue);
      labelAlgActive->setPalette(blue);
      labelDrogi[start][0]->setText(tr("start"));
      labelDrogi[cel][0]->setText(tr("cel"));
      elltextV[start]->Label()->setHtml(tr("<div style='background-color: white; color: blue;'>start</div>"));
      elltextV[start]->Label()->setPos(elltextV[start]->getWsp().getX()-5, \
                                       elltextV[start]->getWsp().getY()+2);
      elltextV[cel]->Label()->setHtml(tr("<div style='background-color: white; color: blue;'>cel</div>"));
      elltextV[cel]->Label()->setPos(elltextV[cel]->getWsp().getX()-2, \
                                     elltextV[cel]->getWsp().getY()+2);
    } else {
      for(int i=0; i < intV; i++){
        aktywny = i;
        bool goOn = true;
        // pokazuje najkrótszą ścieżkę od wierzchołka startowego do końcowego
        elltextV[aktywny]->highlight(0,0,255,255);
        sleeper->msleep(czasAnimacji);
        do {
          for(int a=0; a < intE; a++){
            if(lineE[a]->WK() == aktywny){
              if(lineE[a]->WP() == elltextV[aktywny]->Prev()){
                if(lineE[a]->isBlue){
                  goOn=false;
                  break;
                }
                lineE[a]->highlight(0,0,255,255);
                lineE[a]->isBlue = true;
                aktywny = lineE[a]->WP();
                sleeper->msleep(czasAnimacji);
                break;
              }
            } else if(lineE[a]->WP() == aktywny){
              if(lineE[a]->WK() == elltextV[aktywny]->Prev()){
                if(lineE[a]->isBlue){
                  goOn=false;
                  break;
                }
                lineE[a]->highlight(0,0,255,255);
                lineE[a]->isBlue = true;
                aktywny = lineE[a]->WK();
                sleeper->msleep(czasAnimacji);
                break;
              }
            }
          }
        } while(elltextV[aktywny]->Prev() != aktywny && goOn);
        labelDrogi[i][0]->setPalette(blue);
        labelDrogi[i][1]->setPalette(blue);
      }
      labelDrogi[start][0]->setText(tr("start"));
      elltextV[start]->Label()->setHtml(tr("<div style='background-color: white; color: blue;'>start</div>"));
      elltextV[start]->Label()->setPos(elltextV[start]->getWsp().getX()-5, \
                                       elltextV[start]->getWsp().getY()+2);
      ready->setText("Gotowy.");
    }
  }

  view->setBackgroundBrush(QBrush(QColor(255,255,255,255)));
  // odblokowujemy interfejs
  buttonDijkstra->setDisabled(false);
  buttonBellmanFord->setDisabled(false);
  buttonGenerujGraf->setDisabled(false);
  buttonMacierzWag->setDisabled(false);
  buttonListaKrawedzi->setDisabled(false);
  buttonListaSasiadow->setDisabled(false);
  startingV->setDisabled(false);
  if(!checkboxMST->isChecked())
    targetV->setDisabled(false);
  editV->setDisabled(false);
  gestosc->setDisabled(false);
  randMax->setDisabled(false);
  checkboxMST->setDisabled(false);
}

/* DO ZROBIENIA :
 * * uruchamianie algorytmów z klasy Graph i zwrócenie samego wyniku,
 *   jeśli intV > MAXSIZE
 * * dynamiczna klasa Graph
 * * * addVertex(int);
 * * * removeVertex(int);
 * * * addEdge(int,int);
 * * * removeEdge(int,int);
 */
