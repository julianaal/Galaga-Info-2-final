#include "records.h"
#include "ui_records.h"
#include <QFile>
#include <QTextStream>
#include <qdebug.h>

#define TAM 300 //numero de registros

Records::Records(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Records)
{
    ui->setupUi(this);
    for(int i=0;i<TAM;i++){ //declaracion numero de registros
        for(int j=0;j<2;j++){
            record[i][j]=new QString(" ");
        }
    }

    QFile file("Records.txt"); //Lee o crea el archivo txt para guardar usuarios y puntaje
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text)){
    }
    else{
        QTextStream in(&file);//toma la info del archivo
        int i=0;
        int j=0;
        while(!in.atEnd()&&i<TAM){ // lee linea por linea
            //record[i][j]->close();
            record[i][j]=new QString(in.readLine().toLatin1());  // j=0 nombre y j=1 puntaje
            j++;
            if  (j==2){
                j=0;
                i++;
            }
        }
    }
    file.close();
    for (int i=1; i<TAM; i++){ // Metodo burbuja para ordenar los puntajes de mayor a menor
        for (int j=0 ; j<TAM - 1; j++){
            if (record[j][1]->toInt() < record[j+1][1]->toInt()){
                QString *temp[2];
                for(int i=0;i<2;i++){
                    temp[i]=new QString(*record[j][i]);
                    record[j][i]=new QString(*record[j+1][i]);
                    record[j+1][i]=new QString(*temp[i]);
                }
            }
        }
    }

    ui->one->setText(record[0][0]+QString(" -- ")+record[0][1]); // Muesta nombre y puntaje de los 5 mejores
    ui->two->setText(record[1][0]+QString(" -- ")+record[1][1]);
    ui->tres->setText(record[2][0]+QString(" -- ")+record[2][1]);
    ui->four->setText(record[3][0]+QString(" -- ")+record[3][1]);
    ui->five->setText(record[4][0]+QString(" -- ")+record[4][1]);
}

Records::~Records()
{
    delete ui;
}

void Records::on_Salir_clicked()
{
    open=false;
}
