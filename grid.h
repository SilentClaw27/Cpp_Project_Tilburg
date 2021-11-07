#include "std_lib_facilities.h"
#include <list>

#ifndef GUITEST_GRID_H
#define GUITEST_GRID_H

class Grid {
private:
    int boxes;
    list<int>* closeBoxes_x;
    list<int>* closeBoxes_y;
    bool *visited;

public:
    Grid(int boxes);
    void addConnection(int start_x, int start_y, int end_x, int end_y);
    void Algorithm(int start_x, int start_y);
    bool Location_X_Y(Snake* s, int x,int y);
    bool checkFruit(Fruit *f, int x, int y);
};

Grid::Grid(int boxes){
    this->boxes = boxes;
    this->closeBoxes_x = new list<int>[boxes];
    this->closeBoxes_y = new list<int>[boxes];
}

void Grid::addConnection(int start_x, int start_y, int end_x, int end_y){
    this->closeBoxes_x[start_x].push_back(end_x);
    this->closeBoxes_y[start_y].push_back(end_y);
}

void Grid:: Algorithm(int start_x,int start_y){
    bool visited[boxes][boxes];

    for(int i=0;i<boxes;i++){
        for(int j =0;j<boxes;j++){
            visited[i][j] = false;
        }
    }

    list<int> queue_x;
    list<int> queue_y;

    visited[start_x][start_y] = true;
    queue_x.push_back(start_x);
    queue_y.push_back(start_y);

    list<int>::iterator i;
    list<int>::iterator j;

    while ((!queue_x.empty()) && (!queue_y.empty())) {
        int curr_x_pos = queue_x.front();
        int curr_y_pos = queue_y.front();
        cout << "Visited " << curr_x_pos << " and " << curr_y_pos;
        queue_x.pop_front();
        queue_y.pop_front();

        for (i = closeBoxes_x[curr_x_pos].begin(), j = closeBoxes_y[curr_y_pos].begin(); i != closeBoxes_x[curr_x_pos].end() && j != closeBoxes_y[curr_y_pos].end(); ++i,++j) {
            int adjVertex_x = *i;
            int adjVertex_y = *j;
            if (!visited[adjVertex_x][adjVertex_y]) {
                visited[adjVertex_x][adjVertex_y] = true;
                queue_x.push_back(adjVertex_x);
                queue_y.push_back(adjVertex_y);
            }
        }
    }
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
#endif //GUITEST_GRID_H
