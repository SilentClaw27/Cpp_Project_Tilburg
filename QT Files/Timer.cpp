#include "Timer.h"

MyTimer::MyTimer(Snake *s,Fruit *f, Grid *g, QGraphicsScene *canvas,QGraphicsView *view){
    //Timer Variable Created
    timer = new QTimer(this);
    //Boolean which shows if the fruit has been eaten or not
    bool fruit = false;

    //The X and Y Coordinates of the Fruit which has been eaten
    int f_x = 0;
    int f_y = 0;

    connect(timer,&QTimer::timeout, [s,f,g,canvas,view,this,fruit,f_x,f_y]() mutable {


        canvas->setBackgroundBrush(QBrush(Qt::darkGreen));
        //Creating an object for the algorithm
        AI *Algorithm = new AI(s,f);
        //Running the A* Algorithm to find the next possible path
        Algorithm->Algorithm(s,view,timer);

        //Checking if the Snake head crashed into it's body
        g->snakeCrashsnake(s,view,timer);
        //Moving the Snake
        g->movement(view,timer,s);
        if(fruit){
            //Growing the Snake using the old x and y values of the fruit eaten
            f->grow_Snake(s,f_x,f_y,canvas);
            fruit = false;
        }
        //Checking if the snake has eaten the fruit
        if(f->checkEat(s)){
            fruit = true;
            //Setting the variables to the old x and y values of the fruit
            f_x = f->get_X();
            f_y = f->get_Y();
            //Creating a new fruit in a random location
            f->createNewFruit(s);
            //Drawing the new Fruit on the Canvas
            f->setRect(f->get_X()*20,f->get_Y()*20,20,20);
            f->setBrush(Qt::red);
        }
    });

    //Starting the timer at a pause of 0.1 seconds per movement
    timer->start(100);
}
