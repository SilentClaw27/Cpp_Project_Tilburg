#include "Timer.h"

MyTimer::MyTimer(Snake *s,Fruit *f, Grid *g, QGraphicsScene *canvas,QGraphicsView *view){
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout, [s,f,g,canvas,view,this]() mutable {

        g->snakeCrash(s,false,view,timer);

        if(f->checkEat(s)){
            f->grow_Snake(s,canvas);
            f->createNewFruit(s);
            f->setRect(f->get_X()*20,f->get_Y()*20,20,20);
            f->setBrush(Qt::red);
        }

        g->movement(view,timer,s);
    });

    timer->start(100);
}
