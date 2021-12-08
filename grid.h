#include "fruit.h"

#ifndef GUITEST_GRID_H
#define GUITEST_GRID_H

class Grid {
private:
    int left_border_x = 0;
    int right_border_x;
    int up_border_y = 0;
    int down_border_y;

public:

    Grid(int length,int height);
    void snakeCrashborder(Snake* s,QGraphicsView *view,QTimer *timer);
    void snakeCrashsnake(Snake *s,QGraphicsView *view, QTimer *timer);
    void movement(QGraphicsView *view, QTimer *timer, Snake *s);
    void gameOver(Snake *s, QGraphicsView *view, QTimer *timer);

};
//Constructor which Creates the grid and its four maximum points
inline Grid::Grid(int length,int height){
    this->left_border_x = 0;
    this->right_border_x = length-1;
    this->down_border_y = height-1;
    this->up_border_y = 0;
}

//Function which moves the snake
inline void Grid:: movement(QGraphicsView *view, QTimer *timer,Snake *s){

    Snake *a;
    //Takes the snake's first position
    int start_x = s->getPos_X();
    int start_y = s->getPos_Y();

    int dir = s->getDir();
    //Depending on the direction, the snake's head is moved by one in that direction
    switch(dir) {
        case 0: {
            snakeCrashborder(s,view,timer);
            s->setPos_Y(s->getPos_Y()-1);
            s->setRect(s->getPos_X()*20,s->getPos_Y()*20,20,20);
            //If the snake has a length larger than 1, we set the temporary snake object as the next part of the body
            if(s->getNextSnake() != NULL){
                a = s->getNextSnake();
                a->setDir(s->getDir());
            }
            break;
        }
        case 90: {
            snakeCrashborder(s,view,timer);
            s->setPos_X(s->getPos_X()+1);
            s->setRect(s->getPos_X()*20,s->getPos_Y()*20,20,20);
            if(s->getNextSnake() != NULL){
                a = s->getNextSnake();
                a->setDir(s->getDir());
            }
            break;
        }
        case 180: {

            snakeCrashborder(s,view,timer);
            s->setPos_Y(s->getPos_Y()+1);
            s->setRect(s->getPos_X()*20,s->getPos_Y()*20,20,20);
            if(s->getNextSnake() != NULL){
                a = s->getNextSnake();
                a->setDir(s->getDir());
            }
            break;
        }
        case 270: {

            snakeCrashborder(s,view,timer);
            s->setPos_X(s->getPos_X()-1);
            s->setRect(s->getPos_X()*20,s->getPos_Y()*20,20,20);
            if(s->getNextSnake() != NULL){
                a = s->getNextSnake();
                a->setDir(s->getDir());
            }
            break;
        }
    }
    if(s->getNextSnake() != NULL) {
        a = s;
        int new_dir;
        int count = 0;
        int old_x, old_y;
        int new_x = start_x;
        int new_y = start_y;
        do {
            //Setting the old coordinates so that the next part of the body can go in its place
            old_x = new_x;
            old_y = new_y;

            a = a->getNextSnake();
            //Taking the values of the new position
            new_x = a->getPos_X();
            new_y = a->getPos_Y();
            //Taking into consideration, a change in direction, the snake's direction is saved
            if (count != 0) {
                a->setDir(new_dir);
            }


            //Setting the new position of the snake's body part
            a->setPos_X(old_x);
            a->setPos_Y(old_y);

            //As mentioned in line 101, the direction is saved here in the case of a different direction later.
            if (a->getNextSnake() != NULL) {
                new_dir = a->getDir();
            }

            //Incrementing of the count variable in order to control of unnecessary statements
            if (count == 0) {
                count++;
            }

            //Drawing the Snake's Body in its new position
            a->setRect(a->getPos_X()*20,a->getPos_Y()*20,20,20);
        } while (a->getNextSnake() != NULL);
    }

    qDebug() << s->getPos_X() << " " << s->getPos_Y();

}

//Function checking whether the snake has crashed into one of the four borders.
inline void Grid::snakeCrashborder(Snake *s,QGraphicsView *view, QTimer *timer) {
        if(((s->getPos_Y() == 0) && (s->getDir() == 0)) || ((s->getPos_X() == 19) && (s->getDir() == 90)) || ((s->getPos_Y() == 19) && (s->getDir() == 180)) || ((s->getPos_X() == 0) && (s->getDir() == 270))){
            this->gameOver(s,view,timer);
        }
}

//Checking whether the snake has crashed into itself
inline void Grid::snakeCrashsnake(Snake *s,QGraphicsView *view, QTimer *timer) {
    Snake* curr = s;

    if(curr->getNextSnake() != NULL){
        do{
            curr = curr->getNextSnake();

            if((curr->getPos_X() == s->getPos_X()) && (curr->getPos_Y() == s->getPos_Y())){
                gameOver(s,view,timer);
            }
        }while(curr->getNextSnake() != NULL);
    }
}

//Function displaying the GameOver screen
inline void Grid::gameOver(Snake *s, QGraphicsView *view, QTimer *timer){
    //Creating the Scene and Setting the Background colour and size
    QGraphicsScene *final = new QGraphicsScene();
    final->setSceneRect(0,0,400,400);
    final->setBackgroundBrush(Qt::darkGray);

    //Setting the text which will be outputted on gameover screen
    std::string scoreText = "Score: ";
    scoreText += std::to_string(s->getLength());
    QGraphicsTextItem *sentence = final->addText("Snake is dead :(");
    QString QScore = QString::fromStdString(scoreText);
    QGraphicsTextItem *score = final->addText(QScore);


    //Formatting the text into a specific colour, scale and position
    sentence->setDefaultTextColor(Qt::black);
    score->setDefaultTextColor(Qt::black);
    sentence->setScale(3);
    score->setScale(2);
    sentence->setPos(75,100);
    score->setPos(100,140);

    //Placing the scene on the view and stopping the timer
    view->setScene(final);
    timer->stop();
}
#endif //GUITEST_GRID_H
