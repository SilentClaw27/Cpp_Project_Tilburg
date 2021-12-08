#include "Timer.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene *canvas = new QGraphicsScene();
    canvas->setSceneRect(0, 0, 400, 400);
    canvas->setBackgroundBrush(QBrush(Qt::darkGreen));
    QGraphicsView * view = new QGraphicsView();

    srand(time(NULL));
    Snake *s = new Snake();
    Grid g(20,20);
    Fruit *f = new Fruit();
    f->createNewFruit(s);

    f->setRect(f->get_X()*20,f->get_Y()*20,20,20);
    f->setBrush(Qt::red);

    s->setRect(s->getPos_X()*20,s->getPos_Y()*20,20,20);
    s->setFlag(QGraphicsItem::ItemIsFocusable);
    s->setFocus();
    s->setBrush(Qt::blue);

    canvas->addItem(s);
    canvas->addItem(f);
    view->setScene(canvas);
    view->show();


    MyTimer t(s,f,&g,canvas,view);
    return a.exec();
}


