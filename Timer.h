#include "AI.h"

#ifndef TIMER_H
#define TIMER_H


class MyTimer:QObject
{
    Q_OBJECT

public:
    //Constructor of the Timer which starts the game
    MyTimer(Snake *s,Fruit *f, Grid *g, QGraphicsScene *canvas,QGraphicsView *view);
    QTimer *timer;
};




#endif
