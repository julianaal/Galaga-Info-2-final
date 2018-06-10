#ifndef NUBE_H
#define NUBE_H

#include <QGraphicsItem>

class nube : public QGraphicsItem
{
public:
    nube(int, int);
    int getJ(void);
    int getI(void);
    void setJ(int);
    void setI(int);

private:
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *win);
     int i,j;
     qreal q,w;

private slots:
    void advance (int step);

};

#endif // NUBE_H
