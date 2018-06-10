#ifndef ALIEN_H
#define ALIEN_H

#include <QGraphicsItem>
#include <QPainter>


class Alien : public QGraphicsItem
{
public:
    Alien(int, int, int);
    int getJ(void);
    int getI(void);
    void setJ(int);
    void setI(int);

private:
    QRectF boundingRect() const;
    //QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *win);
    int i,j,type;
    int velX;
    int velY;
    qreal q,w;

private slots:
    void advance (int step);

};

#endif // ALIEN_H
