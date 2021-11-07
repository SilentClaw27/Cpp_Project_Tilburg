#include <unistd.h>
#include "functions.h"

#define BOXES 20
int main() {
    srand(time(NULL));

    Snake s(20,20);

    int temp_x;

    if(s.getPos_X() != 0){
        temp_x = s.getPos_X() - 1;
    }
    else{
        temp_x = s.getPos_X() + 1;
    }

    Grid g(10);
    s.setSnake(temp_x,s.getPos_Y(),s.getDir());
    Snake *temp = s.getNextSnake();

//    cout << "X Position: " << temp->getPos_X() << endl;
//    cout << "Y Position: " << temp->getPos_Y() << endl;
//    cout << "Direction: " << temp->getDir() << endl;
    int po = 0;
    Fruit f;
    f= f.createNewFruit();
    do {
        if(s.checkEat(f)){
            s.grow_Snake(f);
            f = f.createNewFruit();
        }
        cout << "X Position: " << s.getPos_X() << endl;
        cout << "Y Position: " << s.getPos_Y() << endl;
        cout << "Direction: " << s.getDir() << endl;
        bool x = false;
        bool y = false;
        for (int i = 0; i < BOXES; i++) {
            for (int j = 0; j < BOXES; j++) {
                x = g.Location_X_Y(&s, j, i);
                y = g.checkFruit(&f, j, i);
                if ((x)) {
                    cout << s.getSym();
                } else if (y) {
                    cout << f.getSymbol();
                } else {
                    cout << "#";
                }
            }

            cout << endl;
        }
        po++;
        cout << endl;
        cout << endl;
        s.steer();
        s.movement();
        sleep(1);
    }while(po != 100);
    return 0;
}

