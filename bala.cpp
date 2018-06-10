#include "bala.h"

Bala::Bala(int x,int y,int t)
{
    i=x;
    j=y;
    setPos(i,j);
    velJ=4;
    type=t;
}

QRectF Bala::boundingRect() const
{
    return QRectF(-3, -7, 6, 14);
}

void Bala::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(type==1){
        painter->drawPixmap(-3, -7, 6, 14,QPixmap (":/Image/S1.png"));
    }
    else if(type==2){
        painter->drawPixmap(-3, -7, 6, 14,QPixmap (":/Image/S2.png"));
    }
}

void Bala::advance(int step){
    j=j-velJ;
    setPos(i,j);
}

int Bala::getJ(void){
    return j;
}

int Bala::getI(void){
    return i;
}

void Bala::setI(int z){
    i=z;
}

void Bala::setJ(int z){
    j=z;
}

void Bala::setvelJ(int z){
    velJ=z;
}
