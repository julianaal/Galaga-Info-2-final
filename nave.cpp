#include "nave.h"
#define R 14
#define R1 R*2

Nave::Nave(int x, int y, int t)
{
    i=x;
    j=y;
    type=t;
    setPos(i,j);
}


QRectF Nave::boundingRect() const
{
    return QRectF(-14, -28, 28, 56);
}


void Nave::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (type==1){
        painter->drawPixmap(-14, -28, 28, 56,QPixmap (":/Image/N1.png"));
    }
    else if (type==2){
        painter->drawPixmap(-14, -28, 28, 56,QPixmap (":/Image/N2.png"));
    }
}

void Nave::advance(int step){
    setPos(i,j);
}

int Nave::getJ(void){
    return j;
}

int Nave::getI(void){
    return i;
}

void Nave::setI(int z){
    i=z;
}

void Nave::setJ(int z){
    j=z;
}
