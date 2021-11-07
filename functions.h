#include "fruit.h"
#include "snake.h"
#include "grid.h"

void gameOver();
#ifndef GUITEST_FUNCTIONS_H
#define GUITEST_FUNCTIONS_H

void Snake:: movement(){

    Snake *a;
    int start_x = this->getPos_X();
    int start_y = this->getPos_Y();

    int dir = this->getDir();
    switch(dir) {
        case 0: {
            if(this->getPos_Y() == 0){
                gameOver();
            }
            this->setPos_Y(this->getPos_Y()-1);
            if(this->getNextSnake() != NULL){
                a = this->getNextSnake();
                a->setDir(this->getDir());
            }
            break;
        }
        case 90: {
            if(this->getPos_X() == 19){
                gameOver();
            }
            this->setPos_X(this->getPos_X()+1);
            if(this->getNextSnake() != NULL){
                a = this->getNextSnake();
                a->setDir(this->getDir());
            }
            break;
        }
        case 180: {
            if(this->getPos_Y() == 19){
                gameOver();
            }
            this->setPos_Y(this->getPos_Y()+1);
            if(this->getNextSnake() != NULL){
                a = this->getNextSnake();
                a->setDir(this->getDir());
            }
            break;
        }
        case 270: {
            if(this->getPos_X() == 0){
                gameOver();
            }
            this->setPos_X(this->getPos_X()-1);
            if(this->getNextSnake() != NULL){
                a = this->getNextSnake();
                a->setDir(this->getDir());
            }
            break;
        }
    }
    a = this;
    int new_dir;
    int count = 0;
    int old_x,old_y;
    int new_x = start_x;
    int new_y = start_y;
    do{
        old_x = new_x;
        old_y = new_y;

        a = a->getNextSnake();
        new_x = a->getPos_X();
        new_y = a->getPos_Y();
        if(count != 0) {
            a->setDir(new_dir);
        }


        a->setPos_X(old_x);
        a->setPos_Y(old_y);
        if(a->getNextSnake() != NULL){
            new_dir = a->getDir();
        }

        if(count ==0){
            count++;
        }
    }while(a->getNextSnake() != NULL);

//    do{
//
//    }while(true);
}

void Snake:: steer(){

    char dir;

    cin >> dir;

    switch(dir){
        case 'w':{
            this->setDir(0);
            break;
        }
        case 's':{
            this->setDir(180);
            break;
        }
        case 'a':{
            this->setDir(270);
            break;
        }
        case 'd':{
            this->setDir(90);
            break;
        }
        default:{
            steer();
            break;
        }
    }
}

void gameOver(){
    cout << "Game is Over!" << endl;
    exit(2);
}

bool Snake:: checkEat(Fruit f){
    if((this->getPos_X() == f.get_X()) && (this->getPos_Y() == f.get_Y())){
        return true;
    }
    else{
        return false;
    }
}

void Snake:: grow_Snake(Fruit f){
    Snake *s = new Snake;
    s->setPos_X(this->getPos_X());
    s->setPos_Y(this->getPos_Y());
    s->setNext(this->getNextSnake());

    this->nextS = s;
    this->setPos_X(f.get_X());
    this->setPos_Y(f.get_Y());
}
#endif //GUITEST_FUNCTIONS_H
