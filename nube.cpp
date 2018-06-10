#include "nube.h"
#include <QPainter>

nube::nube(int x,int y)
{
    i=x;
    j=y;
    setPos(i,j);
}
QRectF nube::boundingRect() const
{
    return QRectF(-100, -78, 200, 156);
}

void nube::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-100, -78, 200, 156,QPixmap (":/Image/nube.png"));
}

int nube::getJ()
{
    return j;
}

int nube::getI()
{
    return i;
}

void nube::setJ(int z)
{
    j=z;
}

void nube::setI(int z)
{
    i=z;
}

void nube::advance(int step)
{
    j=j+1;
    if(j>700){
        j=-50;
        i=(qrand()%601+150);
    }
    setPos(i,j);
}
