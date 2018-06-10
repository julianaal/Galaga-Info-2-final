#ifndef NAVE_H
#define NAVE_H

#include <QGraphicsItem>
#include <QPainter>

class Nave : public QGraphicsItem
{
public:
    Nave(int x,int y, int t=1);
    int getJ(void);
    int getI(void);
    void setJ(int);
    void setI(int);

private:
    QRectF boundingRect() const;
    //QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *win);
    int i,j;
    int type;
    qreal q,w;

private slots:
    void advance (int step);


};

#endif // NAVE_H
