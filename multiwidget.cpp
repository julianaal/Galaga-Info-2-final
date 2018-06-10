#include "multiwidget.h"
#include "ui_multiwidget.h"

#include <QGraphicsView>
#include <QKeyEvent>
#include <qdebug.h>
#include <QLabel>


MultiWidget::MultiWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MultiWidget)
{

    ui->setupUi(this);
    this->resize(810,660);
    round1=0;
    msg=new QMessageBox(this);
    msg1=new QMessageBox(this);
    timer=new QTimer(this);
    timer2=new QTimer(this);
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

    puntos1=0;
    puntaje1 =new QLCDNumber(score);
    puntaje1->display(puntos1);
    puntaje1->resize(puntaje1->size().width()*2,45);
    puntaje1->move(0,0);

    puntos2=0;
    puntaje2 =new QLCDNumber(score);
    puntaje2->display(puntos2);
    puntaje2->resize(puntaje2->size().width()*2,45);
    puntaje2->move(500,0);

    Ship1=new Nave(300,500,1);//Genera la nave del primer jugador
    scene->addItem(Ship1);

    Ship2=new Nave(500,500,2);//Genera la nave del segundo jugador
    scene->addItem(Ship2);

    Cloud=new nube(10,10);
    scene->addItem(Cloud);
    scene->removeItem(Cloud);


    QGraphicsView *view=new QGraphicsView(scene,Game);
    view->setBackgroundBrush(QPixmap(":/Image/giphy.gif"));
    view->setFrameShape(QFrame::NoFrame);
    view->resize(802, 602);
    view->setEnabled(true);

    Inicio1=1;
    righting1=lefting1=uping1=downing1=false;
    shotting1=false;

    Inicio2=1;
    righting2=lefting2=uping2=downing2=false;
    shotting2=false;

    timershot->start(200);
    connect(timer,SIGNAL(timeout()),this,SLOT(mover1()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(mover2()));
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(timershot,SIGNAL(timeout()),this,SLOT(reload()));

    for(int flag=0;flag<20;flag++){
        Shot1[flag]=new Bala(10000,10000,1);
    }

    for(int flag=0;flag<20;flag++){
        Shot2[flag]=new Bala(10000,10000,2);
    }


    for(int flag=0;flag<(10+10*nivel);flag++){
        dibujar_alien(flag,flag*50+25,150);
    }


    player = new QMediaPlayer; //Reproductor de sonidos
    player->setMedia(QUrl("qrc:/Image/000215225_prev.mp3"));// choque
    player->setVolume(50);

    player1 = new QMediaPlayer; //Reproductor de sonidos
    player1->setMedia(QUrl("qrc:/Image/001094906_prev.mp3"));// laser
    player1->setVolume(50);

    player2 = new QMediaPlayer; //Reproductor de sonidos
    player2->setMedia(QUrl("qrc:/Image/11 Name Entry.mp3"));// musica
    player2->setVolume(50);
    player2->play();



}

MultiWidget::~MultiWidget()
{
    delete ui;
}

void MultiWidget::keyPressEvent(QKeyEvent *event){

    if (event->key()==Qt::Key_Right||event->key()==Qt::Key_D){      // Activa el movimiento de la nave hacia la derecha
        righting1=true;
    }
    if (event->key()==Qt::Key_Left||event->key()==Qt::Key_A){       // Activa el movimiento de la nave hacia la izquierda
        lefting1=true;
    }
    if (event->key()==Qt::Key_Up||event->key()==Qt::Key_W){         // Activa el movimiento de la nave hacia la arriba
        uping1=true;
    }
    if (event->key()==Qt::Key_Down||event->key()==Qt::Key_S){       // Activa el movimiento de la nave hacia la abajo
        downing1=true;
    }
    if (event->key()==Qt::Key_Control){                             // Activa el disparo de nave
        shotting1=true;
    }
    if (event->key()==Qt::Key_Right||event->key()==Qt::Key_L){      // Activa el movimiento de la nave hacia la derecha
        righting2=true;
    }
    if (event->key()==Qt::Key_Left||event->key()==Qt::Key_J){       // Activa el movimiento de la nave hacia la izquierda
        lefting2=true;
    }
    if (event->key()==Qt::Key_Up||event->key()==Qt::Key_I){         // Activa el movimiento de la nave hacia la arriba
        uping2=true;
    }
    if (event->key()==Qt::Key_Down||event->key()==Qt::Key_K){       // Activa el movimiento de la nave hacia la abajo
        downing2=true;
    }
    if (event->key()==Qt::Key_M){                             // Activa el disparo de nave
        shotting2=true;
    }


    if (event->key()==Qt::Key_Space){// Inicia el juego
        timer->start(15);
        timer2->start(15);
    }


}

void MultiWidget::keyReleaseEvent(QKeyEvent *event){
    if (event->key()==Qt::Key_Right||event->key()==Qt::Key_D){      // Desactiva el movimiento de la nave hacia la derecha
        righting1=false;
    }
    if (event->key()==Qt::Key_Left||event->key()==Qt::Key_A){       // Desactiva el movimiento de la nave hacia la izquierda
        lefting1=false;
    }
    if (event->key()==Qt::Key_Up||event->key()==Qt::Key_W){         // Desactiva el movimiento de la nave hacia la arriba
        uping1=false;
    }
    if (event->key()==Qt::Key_Down||event->key()==Qt::Key_S){       // Desactiva el movimiento de la nave hacia la abajo
        downing1=false;
    }
    if (event->key()==Qt::Key_Control){                             // Desactiva el disparo de nave
        shotting1=false;
    }
    if (event->key()==Qt::Key_Right||event->key()==Qt::Key_L){      // Desactiva el movimiento de la nave hacia la derecha
        righting2=false;
    }
    if (event->key()==Qt::Key_Left||event->key()==Qt::Key_J){       // Desactiva el movimiento de la nave hacia la izquierda
        lefting2=false;
    }
    if (event->key()==Qt::Key_Up||event->key()==Qt::Key_I){         // Desactiva el movimiento de la nave hacia la arriba
        uping2=false;
    }
    if (event->key()==Qt::Key_Down||event->key()==Qt::Key_K){       // Desactiva el movimiento de la nave hacia la abajo
        downing2=false;
    }
    if (event->key()==Qt::Key_M){                             // Desactiva el disparo de nave
        shotting2=false;
    }
}

void MultiWidget::mover1(){

    if (righting1==true && Ship1->getI()<800){
        Ship1->setI(Ship1->getI()+velNave);
    }
    if (lefting1==true && Ship1->getI()>0){
        Ship1->setI(Ship1->getI()-velNave);
    }
    if (uping1==true && Ship1->getJ()>0){
        Ship1->setJ(Ship1->getJ()-velNave);
    }
    if (downing1==true && Ship1->getJ()<600){
        Ship1->setJ(Ship1->getJ()+velNave);
    }

    if (shotting1==true && Inicio1==1){
        Shot1[round1]=new Bala(Ship1->getI(),Ship1->getJ()-28,1);
        scene->addItem(Shot1[round1]);
        round1++;
        player1->play();
        Inicio1=0;
    }
    if(round1>10){
        round1=0;
    }
    for(int flag=0;flag<20;flag++){
        for(int N_A=0;N_A<(10+10*nivel);N_A++){ //Puntaje nave 1
            if(Shot1[flag]->collidesWithItem(Spaceship[N_A])&&Spaceship[N_A]->isActive()==true&&Shot1[flag]->isActive()==true){
                scene->removeItem(Spaceship[N_A]);
                scene->removeItem(Shot1[flag]);
                puntos1=puntos1+10;
                puntaje1->display(puntos1);
            }
        }
    }

    for(int N_A=0;N_A<(10+10*nivel);N_A++){ // Vidas-Muerte nave 1
        if(Ship1->collidesWithItem(Spaceship[N_A])&&Spaceship[N_A]->isActive()==true){
            Ship1->setI(300);
            Ship1->setJ(500);
            player->play();

            for(int flag=0;flag<20;flag++){
                scene->removeItem(Shot1[flag]);
            }
            break;
        }
    }

    if(nivel<4){ //Dibuja los aliens de acuerdo al "nivel" en que se encuentran los jugadores
        if(((puntos1+puntos2)==(((nivel+2))*(nivel+1)*50))){
            nivel=nivel+1;
            for (int j1 = 1; j1 <= nivel+1; j1++) {
                for(int i1 = 1; i1 <= 10; i1++ ){
                    dibujar_alien(i1-1+10*(j1-1),i1*80+25,150-30*(j1-1));
                }
            }
            for(int flag=0;flag<20;flag++){// Al cambiar el nivel pone la nave 1 en su posicion inicial y elimina las balas que esten en la escena
                scene->removeItem(Shot1[flag]);
            }
            for(int flag=0;flag<20;flag++){// Al cambiar el nivel pone la nave 2 en su posicion inicial y elimina las balas que esten en la escena
                scene->removeItem(Shot2[flag]);
            }
        }
    }
    if(nivel==4){// Muestra cual es el jugador ganador
        msg->setWindowTitle("* GANADOR *");
        if (puntos1>puntos2){
            msg->setText("\n Ganador Jugador 1");
        }
        else{
            msg->setText("\n Ganador Jugador 2");
        }
        msg->setStandardButtons(QMessageBox::Yes);
        if(msg->exec() == QMessageBox::Yes){
            Jugando=false;
            timer->stop();
            timer2->stop();
        }
    }
}


void MultiWidget::mover2(){
    if (righting2==true && Ship2->getI()<800){
        Ship2->setI(Ship2->getI()+velNave);
    }
    if (lefting2==true && Ship2->getI()>0){
        Ship2->setI(Ship2->getI()-velNave);
    }
    if (uping2==true && Ship2->getJ()>0){
        Ship2->setJ(Ship2->getJ()-velNave);
    }
    if (downing2==true && Ship2->getJ()<600){
        Ship2->setJ(Ship2->getJ()+velNave);
    }
    if (shotting2==true && Inicio2==1){
        Shot2[round2]=new Bala(Ship2->getI(),Ship2->getJ()-28,2);
        scene->addItem(Shot2[round2]);
        round2++;
        player1->play();
        Inicio2=0;
    }
    if(round2>10){
        round2=0;
    }

    for(int flag=0;flag<20;flag++){
        for(int N_A=0;N_A<(10+10*nivel);N_A++){ //Puntaje nave 2
            if(Shot2[flag]->collidesWithItem(Spaceship[N_A])&&Spaceship[N_A]->isActive()==true&&Shot2[flag]->isActive()==true){
                scene->removeItem(Spaceship[N_A]);
                scene->removeItem(Shot2[flag]);
                puntos2=puntos2+10;
                puntaje2->display(puntos2);
            }
        }
    }

    for(int N_A=0;N_A<(10+10*nivel);N_A++){ // Vidas-Muerte nave 2
        if(Ship2->collidesWithItem(Spaceship[N_A])&&Spaceship[N_A]->isActive()==true){
            Ship2->setI(500);
            Ship2->setJ(500);
            player->play();

            for(int flag=0;flag<20;flag++){
                scene->removeItem(Shot2[flag]);
            }
            break;
        }
    }

}

void MultiWidget::reload(){
    Inicio1=1;
    for(int flag=0;flag<20;flag++){// Elimina los disparos al superar el tamaño de la ventana
        if(Shot1[flag]->getJ()<0){
            scene->removeItem(Shot1[flag]);
        }
    }
    Inicio2=1;
    for(int flag=0;flag<20;flag++){// Elimina los disparos al superar el tamaño de la ventana
        if(Shot2[flag]->getJ()<0){
            scene->removeItem(Shot2[flag]);
        }
    }
}

void MultiWidget::dibujar_alien(int num,int x,int y){
    int intRand = (qrand()%2);
    Spaceship[num]=new Alien(x,y,intRand);
    scene->addItem(Spaceship[num]);
}

