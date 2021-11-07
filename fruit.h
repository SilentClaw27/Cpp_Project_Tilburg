#include "std_lib_facilities.h"
#ifndef GUITEST_FRUIT_H
#define GUITEST_FRUIT_H
class Fruit{
private:
    int pos_x = 0;
    int pos_y = 0;
    char symbol = '%';
public:
    Fruit(){
        this->pos_x = 0;
        this->pos_y = 0;
        this->symbol = '%';
    }

    int get_X();
    int get_Y();
    char getSymbol();

    void set_X(int x);
    void set_Y(int y);
    Fruit createNewFruit();

};

int Fruit:: get_X(){
    return this->pos_x;
}

int Fruit:: get_Y(){
    return this->pos_y;
}

char Fruit::getSymbol(){
    return this->symbol;
}
void Fruit:: set_X(int x){
    this->pos_x = x;
}

void Fruit:: set_Y(int y){
    this->pos_y = y;
}

Fruit Fruit::createNewFruit() {
    srand(time(NULL));
    int x = rand() % 20;
    int y = rand() % 20;

    Fruit f;

    f.set_X(x);
    f.set_Y(y);

    return f;
}
#endif //GUITEST_FRUIT_H
