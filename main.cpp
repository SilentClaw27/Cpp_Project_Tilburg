#include <iostream>
#include "snake.h"
#include "grid.h"

#define BOXES 10
//Grid 20x20
//Snake Position is inside the Grid
//Head
//0 - Grid
//2 - Snake
//3 - Snake Head
//1 - Fruit

//Methods:

//Steering
//Creating the Grid
//Main
//Fruit
//
int main() {
    srand(time(NULL));
    int start_dir =0;
//    while(start_dir != 5) {
//        start_dir = (rand() % 4) + 1;
//    }
    Snake s(10,10,start_dir);
    cout << "X Position: " << s.getPos_X() << endl;
    cout << "Y Position: " << s.getPos_Y() << endl;
    cout << "Direction: " << s.getDir() << endl;
    int temp_x;

    if(s.getPos_X() != 0){
        temp_x = s.getPos_X() - 1;
    }
    else{
        temp_x = s.getPos_X() + 1;
    }

    Grid g(10);
    s.setSnake(temp_x,s.getPos_Y(),start_dir);
    Snake *temp = s.getNextSnake();

    cout << "X Position: " << temp->getPos_X() << endl;
    cout << "Y Position: " << temp->getPos_Y() << endl;
    cout << "Direction: " << temp->getDir() << endl;
    bool x = false;
    bool y = false;
      for(int i =0;i<BOXES;i++){
          for(int j=0;j<BOXES;j++) {
              x = g.Location_X_Y(&s,j,i);
            if((x)){
                cout << s.getSym();

            }
            else{
                cout << "#";
            }
          }
          cout << endl;
      }
    return 0;
}

