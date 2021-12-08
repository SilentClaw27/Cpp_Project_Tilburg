#include "Timer.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Creating a canvas and view for the game to be seen on
    QGraphicsScene *canvas = new QGraphicsScene();
    QGraphicsView * view = new QGraphicsView();

    //Setting the Canvas Size and Background Colour
    canvas->setSceneRect(0, 0, 400, 400);
    canvas->setBackgroundBrush(QBrush(Qt::darkGreen));


    srand(time(NULL));
    //Creating a snake, grid and fruit
    Snake *s = new Snake();
    Grid g(20,20);
    Fruit *f = new Fruit();
    f->createNewFruit(s);

    //Drawing the Fruit
    f->setRect(f->get_X()*20,f->get_Y()*20,20,20);
    f->setBrush(Qt::red);

    //Drawing the Initial Snake
    s->setRect(s->getPos_X()*20,s->getPos_Y()*20,20,20);
    s->setFlag(QGraphicsItem::ItemIsFocusable);
    s->setFocus();
    s->setBrush(Qt::blue);

    //Placing the snake and fruit on the canvas
    canvas->addItem(s);
    canvas->addItem(f);
    //Placing the canvas on the view
    view->setScene(canvas);
    view->show();

    //Creating the timer
    MyTimer t(s,f,&g,canvas,view);
    return a.exec();
}


