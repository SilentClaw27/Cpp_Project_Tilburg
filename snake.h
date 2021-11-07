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
    //Basic Constructor Creating the Starting position of the snake
    Snake(int l,int h,int dir){
        this->location_x_pos = rand() % l;
        this->location_y_pos = rand() % h;
        this->direction = dir;
        this->nextS = NULL;
    }

    Snake(int pos_x,int pos_y,int dir,char sym){
        this->location_x_pos = pos_x;
        this->location_y_pos = pos_y;
        this->direction = dir;
        this->nextS = NULL;
        this->symbol = sym;
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
    //void setFirstDir();
    void setSnake(int x,int y,int dir);




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

void Snake::setSnake(int x,int y, int dir){
    this->nextS = new Snake(x,y,dir,this->symbol);
}

#endif //GUITEST_SNAKE_H
