#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QMessageBox>
#include <QLCDNumber>
#include <QMediaPlayer>

#include "nave.h"
#include "bala.h"
#include "alien.h"
#include "nube.h"

namespace Ui {
class MultiWidget;
}

class MultiWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit MultiWidget(QWidget *parent = 0);
    ~MultiWidget();
    bool Jugando=true;

private:
    Ui::MultiWidget *ui;
    QWidget *Game;
    QGraphicsScene *scene;
    QWidget *score,*life;
    QTimer *timer,*timer2;
    QTimer *timershot;
    QMessageBox *msg,*msg1;
    QMediaPlayer *player,*player1,*player2;




    QLCDNumber *puntaje1,*puntaje2;

    Nave *Ship1;
    Nave *Ship2;
    Alien *Spaceship[50];
    Bala *Shot1[20];
    Bala *Shot2[20];
    nube *Cloud;

    int Inicio1;
    int round1;
    bool righting1,lefting1;
    bool uping1,downing1;
    bool shotting1;
    void dibujar_alien(int,int,int);
    int puntos1;
    int puntos2;
    int nivel;
    int velNave=5;

    int Inicio2;
    int round2;
    bool righting2,lefting2;
    bool uping2,downing2;
    bool shotting2;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void mover1();
    void mover2();
    void reload();
};

#endif // WIDGET_H
