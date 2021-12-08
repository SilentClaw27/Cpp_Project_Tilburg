#include <stdlib.h>
#include <time.h>
#include <winsock2.h>
#include <QtCore>
#include <QDebug>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include <vector>

#ifndef GUITEST_SNAKE_H
#define GUITEST_SNAKE_H

class Snake: public QGraphicsRectItem{
private:
    int length = 1;
    int direction = 0;
    //0 - Up, 90 - Right, 180 - Down, 270 - Left

    int location_x_pos = 0;
    int location_y_pos = 0;
    Snake *nextS;

public:
    //Basic Constructors Creating the Starting position of the snake
    Snake();
    Snake(int pos_x,int pos_y,int dir);
    Snake(int pos_x,int pos_y,int dir,Snake *s);

    //Getters and Setters of Attributes
    int getPos_X();
    int getPos_Y();
    int getDir();
    Snake* getNextSnake();
    int getLength();

    void setLength();
    void setPos_X(int pos_x);
    void setPos_Y(int pos_y);
    void setDir(int dir);
    void setFirstDir();
    void setNext(Snake *s);
    void setSnake(int x,int y,int dir);

    //Functions
    void keyPressEvent(QKeyEvent *event);
};

//Constructor used when the Program is started i.e. used when the snake head is created
inline Snake::Snake(){
    this->location_x_pos = (rand() % 20);
    this->location_y_pos = (rand() % 20);
    this->direction = 0;
    this->setFirstDir();
    this->nextS = NULL;
}

//Constructor to create a new body for the snake after eating the fruit
inline Snake::Snake(int pos_x,int pos_y,int dir){
    this->location_x_pos = pos_x;
    this->location_y_pos = pos_y;
    this->direction = dir;
    this->nextS = NULL;
}

//Constructor to add the new body to the snake
inline Snake::Snake(int pos_x,int pos_y,int dir,Snake *s){
    this->location_x_pos = pos_x;
    this->location_y_pos = pos_y;
    this->direction = dir;
    this->nextS = s;
}

//Getting the X Position of the Snake Body which is used
inline int Snake::getPos_X() {
    return this->location_x_pos;
}

//Getting the Y Position of the Snake Body which is used
inline int Snake::getPos_Y() {
    return this->location_y_pos;
}

//Getting the Direction of the Snake Body
inline int Snake:: getDir() {
    return this->direction;
}

//Getting the next piece of the snake
inline Snake* Snake:: getNextSnake(){
    return this->nextS;
}

//Getting the Length of the snake
inline int Snake::getLength(){
    return this->length;
}

//Setting the new X Position of the Snake Body being used
inline void Snake::setPos_X(int pos_x) {
    this->location_x_pos = pos_x;
}

//Setting the new Y Position of the Snake Body being used
inline void Snake::setPos_Y(int pos_y) {
    this->location_y_pos = pos_y;
}

//Setting the new Direction of the snake
inline void Snake:: setDir(int dir) {
    this->direction = dir;
}

//Setting the next piece of the snake
inline void Snake:: setNext(Snake* s){
    this->nextS = s;
}

//Setting the first direction of the snake when it is created
inline void Snake::setFirstDir() {
    int dir = rand() % 4;;

    //0 - North (0 degress)
    //1 - East (90 degrees)
    //2 - South (180 degrees)
    //3 - West (270 degrees)
    switch(dir){
        case 0:{
            this->setDir(0);
            break;
        }
        case 1:{
            this->setDir(90);
            break;
        }
        case 2:{
            this->setDir(180);
            break;
        }
        case 3:{
            this->setDir(270);
            break;
        }
    }
}

//Incrementing the length of the snake when a piece of fruit is eaten
inline void Snake::setLength(){
    this->length = this->length + 1;
}

//Creating a new piece of snake body
inline void Snake::setSnake(int x,int y, int dir){
    this->nextS = new Snake(x,y,dir);
}

//Taking in the event of the user using the arrow keys to change the snake's direction
inline void Snake:: keyPressEvent(QKeyEvent *event){
    int dir = this->getDir();

    //Depending on the Direction, the user can only go left and right of said direction
       if(dir == 0){
           if(event->key() == Qt::Key_Left) {
               this->setDir(270);
           }
           else if(event->key() == Qt::Key_Right) {
               this->setDir(90);
           }
           else{
               return;
           }
       }
       else if(dir == 90){
           if(event->key() == Qt::Key_Up) {
               this->setDir(0);
           }
           else if(event->key() == Qt::Key_Down) {
               this->setDir(180);
           }
           else{
               return;
           }
       }
       else if(dir == 180){
           if(event->key() == Qt::Key_Left) {
               this->setDir(270);
           }
           else if(event->key() == Qt::Key_Right) {
               this->setDir(90);
           }
           else{
               return;
           }
       }
       else if(dir == 270){
           if(event->key() == Qt::Key_Up) {
               this->setDir(0);
           }
           else if(event->key() == Qt::Key_Down) {
               this->setDir(180);
           }
           else{
               return;
           }
       }
}
#endif //GUITEST_SNAKE_H
