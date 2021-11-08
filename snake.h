#include "std_lib_facilities.h"

#ifndef GUITEST_SNAKE_H
#define GUITEST_SNAKE_H

class Snake{
private:
    int length = 1;
    int direction = 0;
    //0 - Up, 90 - Right, 180 - Down, 270 - Left

    int location_x_pos = 0;
    int location_y_pos = 0;
    Snake *nextS;
    char symbol = '*';

public:
    //Basic Constructors Creating the Starting position of the snake
    Snake(int l,int h){
        this->location_x_pos = rand() % l;
        this->location_y_pos = rand() % h;
        this->direction =0;
        this->setFirstDir();
        this->nextS = NULL;
    }

    Snake(int pos_x,int pos_y,int dir,char sym){
        this->location_x_pos = pos_x;
        this->location_y_pos = pos_y;
        this->direction = dir;
        this->nextS = NULL;
        this->symbol = sym;
    }

    Snake(int pos_x,int pos_y,int dir,Snake *s,char sym){
        this->location_x_pos = pos_x;
        this->location_y_pos = pos_y;
        this->direction = dir;
        this->symbol = sym;
        this->nextS = s;
    }
    Snake(){
        this->location_x_pos = 0;
        this->location_y_pos = 0;
        this->direction = 0;
        this->nextS = NULL;
        this->symbol = '*';
    }
    //Getters and Setters of Attributes
    int getPos_X();
    int getPos_Y();
    int getDir();
    Snake* getNextSnake();
    char getSym();

    void setPos_X(int pos_x);
    void setPos_Y(int pos_y);
    void setDir(int dir);
    void setFirstDir();
    void setNext(Snake *s);
    void setSnake(int x,int y,int dir);
    void movement();
    void steer();
};

int Snake::getPos_X() {
    return this->location_x_pos;
}

int Snake::getPos_Y() {
    return this->location_y_pos;
}

int Snake:: getDir() {
    return this->direction;
}

Snake* Snake:: getNextSnake(){
    return this->nextS;
}

char Snake::getSym(){
    return this->symbol;
}

void Snake::setPos_X(int pos_x) {
    this->location_x_pos = pos_x;
}

void Snake::setPos_Y(int pos_y) {
    this->location_y_pos = pos_y;
}

void Snake:: setDir(int dir) {
    this->direction = dir;
}

void Snake:: setNext(Snake* s){
    this->nextS = s;
}
void Snake::setFirstDir() {
    int dir = rand() % 4;;

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

void Snake::setSnake(int x,int y, int dir){
    this->nextS = new Snake(x,y,dir,this->symbol);
}

#endif //GUITEST_SNAKE_H
