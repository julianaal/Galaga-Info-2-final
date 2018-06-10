#include "widget.h"
#include "ui_widget.h"

#include <QGraphicsView>
#include <QKeyEvent>
#include <qdebug.h>
#include <QLabel>


Widget::Widget(QString *user,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    username=new QString(*user);
    qDebug()<<username->toLatin1();
    this->resize(810,660);
    round=0;
    msg=new QMessageBox(this);
    //msg1=new QMessageBox(this);
    timer=new QTimer(this);
    timershot=new QTimer(this);

    Game=new QWidget(this);
    Game->move(5,55);
    Game->resize(800,650);

    scene=new QGraphicsScene (Game);
    scene->setSceneRect(0, 0, 800,600);

    score=new QWidget (this);
    score->move(5,5);
    score->resize(800,50);

    nivel = 0;

    puntos=0;
    puntaje =new QLCDNumber(score);
    puntaje->display(puntos);
    puntaje->resize(puntaje->size().width()*2,45);



    life=new QWidget(this);
    life->move(500,5);
    life->resize(800,50);

    vida=3;
    vidas = new QLCDNumber(life);
    vidas->display(vida);
    vidas->resize(vidas->size().width()*2,45);

    Ship=new Nave(400,500);
    scene->addItem(Ship);

    Cloud=new nube(10,10);
    scene->addItem(Cloud);
    scene->removeItem(Cloud);


    QGraphicsView *view=new QGraphicsView(scene,Game);
    view->setBackgroundBrush(QPixmap(":/Image/giphy.gif"));
    view->setFrameShape(QFrame::NoFrame);
    view->resize(802, 602);
    view->setEnabled(true);

    Inicio=1;
    righting=lefting=uping=downing=false;
    shotting=false;

    //timer->start(15);
    timershot->start(200);
    connect(timer,SIGNAL(timeout()),this,SLOT(mover()));
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(timershot,SIGNAL(timeout()),this,SLOT(reload()));

    for(int flag=0;flag<20;flag++){
        Shot[flag]=new Bala(10000,10000);
    }


    for(int flag=0;flag<(10+10*nivel);flag++){
        dibujar_alien(flag,flag*50+25,150);
    }





}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event){

    if (event->key()==Qt::Key_Right||event->key()==Qt::Key_D){      // activa el movimiento de la nave hacia la derecha
        righting=true;
    }
    if (event->key()==Qt::Key_Left||event->key()==Qt::Key_A){       // activa el movimiento de la nave hacia la izquierda
        lefting=true;
    }
    if (event->key()==Qt::Key_Up||event->key()==Qt::Key_W){         // activa el movimiento de la nave hacia la arriba
        uping=true;
    }
    if (event->key()==Qt::Key_Down||event->key()==Qt::Key_S){       // activa el movimiento de la nave hacia la abajo
        downing=true;
    }
    if (event->key()==Qt::Key_Control){                             // activa el disparo de nave
        shotting=true;
    }
    if (event->key()==Qt::Key_Escape){
        QFile cuenta("Records.txt");
        if(!cuenta.open(QIODevice::ReadWrite|QIODevice::Append)){
            qDebug()<<"Error";
            return;
        }
        QTextStream out (&cuenta);
        out << *username<<"\n";
        out << puntos<<"\n";
        cuenta.close();
        Jugando=false;
    }
    if (event->key()==Qt::Key_Space){
        timer->start(15);
    }


}

void Widget::keyReleaseEvent(QKeyEvent *event){
    if (event->key()==Qt::Key_Right||event->key()==Qt::Key_D){      // desactiva el movimiento de la nave hacia la derecha
        righting=false;
    }
    if (event->key()==Qt::Key_Left||event->key()==Qt::Key_A){       // desactiva el movimiento de la nave hacia la izquierda
        lefting=false;
    }
    if (event->key()==Qt::Key_Up||event->key()==Qt::Key_W){         // desactiva el movimiento de la nave hacia la arriba
        uping=false;
    }
    if (event->key()==Qt::Key_Down||event->key()==Qt::Key_S){       // desactiva el movimiento de la nave hacia la abajo
        downing=false;
    }
    if (event->key()==Qt::Key_Control){                             // desactiva el disparo de nave
        shotting=false;
    }
}

void Widget::mover(){

    if (righting==true && Ship->getI()<800){
        Ship->setI(Ship->getI()+velNave);
    }
    if (lefting==true && Ship->getI()>0){
        Ship->setI(Ship->getI()-velNave);
    }
    if (uping==true && Ship->getJ()>0){
        Ship->setJ(Ship->getJ()-velNave);
    }
    if (downing==true && Ship->getJ()<600){
        Ship->setJ(Ship->getJ()+velNave);
    }
    if (shotting==true && Inicio==1){
        Shot[round]=new Bala(Ship->getI(),Ship->getJ()-28);
        scene->addItem(Shot[round]);
        round++;
        Inicio=0;
    }

    if(round>20){
        round=0;
    }
    for(int flag=0;flag<20;flag++){
        for(int N_A=0;N_A<(10+10*nivel);N_A++){ //Puntaje
            if(Shot[flag]->collidesWithItem(Spaceship[N_A])&&Spaceship[N_A]->isActive()==true&&Shot[flag]->isActive()==true){
                scene->removeItem(Spaceship[N_A]);
                scene->removeItem(Shot[flag]);
                puntos=puntos+10;
                puntaje->display(puntos);
            }
        }
    }
    for(int N_A=0;N_A<(10+10*nivel);N_A++){ // Vidas-Muerte
        if(Ship->collidesWithItem(Spaceship[N_A])&&Spaceship[N_A]->isActive()==true){
            scene->removeItem(Spaceship[N_A]);
            vida=vida-1;
            vidas->display(vida);
            Ship->setI(400);
            Ship->setJ(500);

            for(int flag=0;flag<(10+10*nivel);flag++){
                Spaceship[flag]->setJ(0);
            }

            for(int flag=0;flag<20;flag++){
                scene->removeItem(Shot[flag]);
            }

            if(vida==0){
                msg->setWindowTitle("*Purgarotio*");
                msg->setText("\nPerdio el turno");
                msg->show();
                QFile cuenta("Records.txt");
                if(!cuenta.open(QIODevice::ReadWrite|QIODevice::Append)){
                    qDebug()<<"Error";
                    return;
                }
                QTextStream out (&cuenta);
                out << username<<"\n";
                out << puntos<<"\n";
                cuenta.close();
                Jugando=false;
            }
            timer->stop();

            break;
        }
    }


    if((puntos+10*(3-vida))==(((nivel+2))*(nivel+1)*50)){
        nivel=nivel+1;
        for (int j1 = 1; j1 <= nivel+1; j1++) {
            for(int i1 = 1; i1 <= 10; i1++ ){
                dibujar_alien(i1-1+10*(j1-1),i1*80+25,150-30*(j1-1));
            }
        }
        for(int flag=0;flag<20;flag++){
            scene->removeItem(Shot[flag]);
        }
        Ship->setI(400);
        Ship->setJ(500);
        timer->stop();
    }


   /*
    if(puntos==200*nivel){
        msg1->setWindowTitle("*Ganó!!!*");
        msg1->setText("\nPasa al siguiente nivel");
        msg1->show();
    }
    */
}

void Widget::reload(){
    Inicio=1;
    for(int flag=0;flag<20;flag++){
        if(Shot[flag]->getJ()<0){
            scene->removeItem(Shot[flag]);
        }
    }
    if((nivel>0) && nubes==false){
        Cloud=new nube((qrand()%601+150),-50);
        scene->addItem(Cloud);
        //Cloud->setZValue(-1);
        nubes=true;
    }
    if (Ship->collidesWithItem(Cloud)){
        velNave=2;
    }
    else{
        velNave=5;
    }

}

void Widget::dibujar_alien(int num,int x,int y){
    int intRand = (qrand()%2);
    Spaceship[num]=new Alien(x,y,intRand);
    scene->addItem(Spaceship[num]);
}

