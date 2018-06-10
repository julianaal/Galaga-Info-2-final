#include "simplewidget.h"
#include "ui_simplewidget.h"

SimpleWidget::SimpleWidget(QString *user,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleWidget)
{
    ui->setupUi(this);
    username=new QString(*user); // Usuario que esta jugando

    QFile file(*username+".txt"); // Crea o lee el archivo txt donde se guardan las vidas y los puntos, este tiene el nombre del usuario
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text)){
    }
    else{
        QTextStream in(&file);
        while(!in.atEnd()){
            vidaReg=QString(in.readLine().toLatin1()).toInt(); //toma la primera linea que son las vidas
            vidaReg=vidaReg-vida;
            puntosReg=QString(in.readLine().toLatin1()).toInt(); //toma la segunda linea que son los puntos
        }
    }
    file.close();

    this->resize(810,660); // Cambia el tamaño de la pantalla del juego
    round=0; // Declara la cantidad inicial de disparos
    msg=new QMessageBox(this);
    timer=new QTimer(this); // Controla el juego
    timershot=new QTimer(this); // Controla los disparos

    Game=new QWidget(this);
    Game->move(5,55);
    Game->resize(800,650);

    scene=new QGraphicsScene (Game);
    scene->setSceneRect(0, 0, 800,600);

    score=new QWidget (this);
    score->move(5,5);
    score->resize(800,50);

    nivel = 0;

    puntaje =new QLCDNumber(score);
    puntaje->display(puntos+puntosReg);
    puntaje->resize(puntaje->size().width()*2,45);



    life=new QWidget(this);
    life->move(500,5);
    life->resize(800,50);

    vidas = new QLCDNumber(life);
    vidas->display(vida+vidaReg);
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

    Inicio=1; //Delay entre disparos
    righting=lefting=uping=downing=false;
    shotting=false;

    timershot->start(200);// Rata de balas
    connect(timer,SIGNAL(timeout()),this,SLOT(mover()));
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));//Permite que las graficas se muevan
    connect(timershot,SIGNAL(timeout()),this,SLOT(reload()));

    for(int flag=0;flag<20;flag++){
        Shot[flag]=new Bala(10000,10000);
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

SimpleWidget::~SimpleWidget()
{
    delete ui;
}

void SimpleWidget::keyPressEvent(QKeyEvent *event){

    if (event->key()==Qt::Key_Right||event->key()==Qt::Key_D){      // Activa el movimiento de la nave hacia la derecha
        righting=true;
    }
    if (event->key()==Qt::Key_Left||event->key()==Qt::Key_A){       // Activa el movimiento de la nave hacia la izquierda
        lefting=true;
    }
    if (event->key()==Qt::Key_Up||event->key()==Qt::Key_W){         // Activa el movimiento de la nave hacia la arriba
        uping=true;
    }
    if (event->key()==Qt::Key_Down||event->key()==Qt::Key_S){       // Activa el movimiento de la nave hacia la abajo
        downing=true;
    }
    if (event->key()==Qt::Key_Control){                             // Activa el disparo de nave
        shotting=true;
    }
    if (event->key()==Qt::Key_P){                             // Pausa el juego
        timer->stop();
    }
    if (event->key()==Qt::Key_Escape){ //Sale del juego

        QFile cuenta1(*username+".txt"); //Elimina el archivo de puntos existente
        cuenta1.remove();
        cuenta1.close();

        QFile cuenta2(*username+".txt");
        if(!cuenta2.open(QIODevice::ReadWrite|QIODevice::Append)){
            qDebug()<<"Error";
            return;
        }
        else{ // Crear archivo txt con puntos y vidas del usuario y sale del juego
            QTextStream out (&cuenta2);
            out << vida+vidaReg<<"\n";
            out << puntos+puntosReg<<"\n";
            cuenta2.close();
            Jugando=false;
        }
    }
    if (event->key()==Qt::Key_Space){ // Inicia el juego
        timer->start(15);
    }


}

void SimpleWidget::keyReleaseEvent(QKeyEvent *event){
    if (event->key()==Qt::Key_Right||event->key()==Qt::Key_D){      // Desactiva el movimiento de la nave hacia la derecha
        righting=false;
    }
    if (event->key()==Qt::Key_Left||event->key()==Qt::Key_A){       // Desactiva el movimiento de la nave hacia la izquierda
        lefting=false;
    }
    if (event->key()==Qt::Key_Up||event->key()==Qt::Key_W){         // Desactiva el movimiento de la nave hacia la arriba
        uping=false;
    }
    if (event->key()==Qt::Key_Down||event->key()==Qt::Key_S){       // Desactiva el movimiento de la nave hacia la abajo
        downing=false;
    }
    if (event->key()==Qt::Key_Control){                             // Desactiva el disparo de nave
        shotting=false;
    }
}

void SimpleWidget::mover(){ // Cerebro del juego

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
        player1->play();
        if(round>10){
            round=0;
        }
        Inicio=0;
    }


    for(int flag=0;flag<20;flag++){
        for(int N_A=0;N_A<(10+10*nivel);N_A++){ //Puntaje
            if(Shot[flag]->collidesWithItem(Spaceship[N_A])&&Spaceship[N_A]->isActive()==true&&Shot[flag]->isActive()==true){
                scene->removeItem(Spaceship[N_A]);
                scene->removeItem(Shot[flag]);
                puntos=puntos+10;
                puntaje->display(puntos+puntosReg);
            }
        }
    }
    for(int N_A=0;N_A<(10+10*nivel);N_A++){ // Vidas-Muerte
        if(Ship->collidesWithItem(Spaceship[N_A])&&Spaceship[N_A]->isActive()==true){
            player->play();
            scene->removeItem(Spaceship[N_A]);
            vida=vida-1;
            vidas->display(vida+vidaReg);
            Ship->setI(400);
            Ship->setJ(500);


            for(int flag=0;flag<(10+10*nivel);flag++){ // Pone nuevamente las naves en la parte superior de la pantalla
                Spaceship[flag]->setJ(0);
            }

            for(int flag=0;flag<20;flag++){ // Elimina disparos
                scene->removeItem(Shot[flag]);
            }

            if(vida+vidaReg==0){ // Muerte!!!!
                vida=vida-1;
                msg->setWindowTitle("* Perdiste *");
                msg->setText("\n Acepta tu destino");
                msg->setStandardButtons(QMessageBox::Yes);
                if(msg->exec() == QMessageBox::Yes){

                    QFile cuenta("Records.txt"); // Guarda puntaje en el archivo de records
                    if(!cuenta.open(QIODevice::ReadWrite|QIODevice::Append)){
                        qDebug()<<"Error";
                        return;
                    }
                    QTextStream out (&cuenta);
                    out << username->toLatin1()<<"\n";
                    out << puntos+puntosReg<<"\n";
                    cuenta.close();

                    QFile cuenta1(*username+".txt");
                    cuenta1.remove();
                    cuenta1.close();

                    Jugando=false;
                }
            }
            timer->stop();

            break;
        }
    }
    if (Ship->collidesWithItem(Cloud)){ // Si la nave choca con la nube su velocidad se reduce
        velNave=2;
    }
    else{
        velNave=5;
    }

    if (nivel<4){  // Cambio de nivel
        if((puntos+10*(3-vida))==(((nivel+2))*(nivel+1)*50)){
            nivel=nivel+1;
            for (int j1 = 1; j1 <= nivel+1; j1++) {
                for(int i1 = 1; i1 <= 10; i1++ ){
                    dibujar_alien(i1-1+10*(j1-1),i1*80+25,150-30*(j1-1));
                }
            }
            for(int flag=0;flag<20;flag++){ // Al cambiar el nivel pone la nave en su posicion inicial y elimina las balas que esten en la escena
                scene->removeItem(Shot[flag]);
            }
            Ship->setI(400);
            Ship->setJ(500);
            timer->stop();
        }
    }
    else{ // Elimina todo para evitar un bucle
        int clearscene=0;
        for(int flag=0;flag<50;flag++){
            if(Spaceship[flag]->isActive()==false){
                clearscene++;
            }
        }
        if(clearscene==50){ // Cuanto todas las naves tas eliminadas se crean las del siguiente nivel
            for (int j1 = 1; j1 <= 4; j1++) {
                for(int i1 = 1; i1 <= 10; i1++ ){
                    dibujar_alien(i1-1+10*(j1-1),i1*80+25,150-30*(j1-1));
                }
            }
            for(int flag=0;flag<20;flag++){
                scene->removeItem(Shot[flag]);
            }
            Ship->setI(400);
            Ship->setJ(500);
        }
    }

}

void SimpleWidget::reload(){
    Inicio=1;
    for(int flag=0;flag<20;flag++){// Elimina los disparos al superar el tamaño de la ventana
        if(Shot[flag]->getJ()<0){
            scene->removeItem(Shot[flag]);
        }
    }
    if((nivel>0) && nubes==false){// Genera la nube en el nivel 1
        scene->removeItem(Cloud);
        Cloud=new nube((qrand()%601+150),-50);
        scene->addItem(Cloud);
        Cloud->setZValue(-1);
        nubes=true;
    }


}

void SimpleWidget::dibujar_alien(int num,int x,int y){
    int intRand = (qrand()%2);
    Spaceship[num]=new Alien(x,y,intRand);
    scene->addItem(Spaceship[num]);
}

