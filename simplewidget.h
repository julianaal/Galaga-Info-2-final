#ifndef SIMPLEWIDGET_H
#define SIMPLEWIDGET_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QWidget>
#include <QTimer>
#include <QMessageBox>
#include <QLCDNumber>
#include <QString>
#include <QGraphicsView>
#include <QKeyEvent>
#include <qdebug.h>
#include <QLabel>
#include <QMediaPlayer>

#include "nave.h"
#include "bala.h"
#include "alien.h"
#include "nube.h"
namespace Ui {
class SimpleWidget;
}

class SimpleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SimpleWidget(QString *user,QWidget *parent = 0);
    ~SimpleWidget();
    bool Jugando=true;
    QString *username;

private:
    Ui::SimpleWidget *ui;
    QWidget *Game;
    QGraphicsScene *scene;
    QWidget *score,*life;
    QTimer *timer;
    QTimer *timershot;
    QMessageBox *msg,*msg1;
    QMediaPlayer *player,*player1,*player2;
    QLCDNumber *puntaje,*vidas;

    Nave *Ship;
    Alien *Spaceship[50];
    Bala *Shot[20];
    nube *Cloud;

    int Inicio;
    int round;
    bool righting,lefting;
    bool uping,downing;
    bool shotting;
    bool nubes=false;
    void dibujar_alien(int,int,int);
    int vida=3;
    int puntos=0;
    int vidaReg=0;
    int puntosReg=0;
    int nivel;
    int velNave=2;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void mover();
    void reload();
};

#endif // SIMPLEWIDGET_H
