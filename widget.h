#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QMessageBox>
#include <QLCDNumber>
#include <QString>
#include "nave.h"
#include "bala.h"
#include "alien.h"
#include "nube.h"

namespace Ui {
class Widget;
}

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Widget(QString *user=0,QWidget *parent = 0);
    ~Widget();
    bool Jugando=true;
    QString *username;

private:
    Ui::Widget *ui;
    QWidget *Game;
    QGraphicsScene *scene;
    QWidget *score,*life;
    QTimer *timer;
    QTimer *timershot;
    QMessageBox *msg,*msg1;


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
    int vida;
    int puntos;
    int nivel;
    int velNave=2;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void mover();
    void reload();
};

#endif // WIDGET_H
