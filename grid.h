#include "std_lib_facilities.h"
#include "functions.h"

#ifndef GUITEST_GRID_H
#define GUITEST_GRID_H

class Grid {
private:
    int length;
    int height;

public:
    Grid(int length,int height);
    bool Location_X_Y(Snake* s, int x,int y);
    bool checkFruit(Fruit *f, int x, int y);
    void drawGrid(Snake *s, Fruit *f);
};

Grid::Grid(int length,int height){
    this->length = length;
    this->height = height;
}

bool Grid::Location_X_Y(Snake* s, int x,int y) {
    Snake* curr = new Snake;
    curr = s;
    bool head = true;
    do{
        if(head){
            head = false;
            if((x == curr->getPos_X()) && (y == curr->getPos_Y())){
                return true;
            }
        }
        else{
            curr = curr->getNextSnake();
            if((x == curr->getPos_X()) && (y == curr->getPos_Y())){
                return true;
            }
        }


    }while(curr->getNextSnake() != NULL);

    return false;
}

bool Grid::checkFruit(Fruit* f, int x,int y) {
    Fruit *curr = new Fruit;
    curr = f;
    if ((x == curr->get_X()) && (y == curr->get_Y())) {
        return true;
    }
    return false;
}

void Grid::drawGrid(Snake *s, Fruit *f){
    bool x = false;
    bool y = false;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            x = this->Location_X_Y(s, j, i);
            y = this->checkFruit(f, j, i);
            if ((x)) {
                cout << s->getSym();
            } else if (y) {
                cout << f->getSymbol();
            } else {
                cout << "#";
            }
        }

        cout << endl;
    }
}
#endif //GUITEST_GRID_H
