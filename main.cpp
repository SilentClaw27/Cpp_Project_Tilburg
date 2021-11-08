#include <unistd.h>
#include "grid.h"

#define BOXES 20
int main() {
    srand(time(NULL));

    Snake s(20,20);

    Grid g(20,20);

    Fruit f;
    f = f.createNewFruit(&s);
    do {
        if(f.checkEat(&s)){
            f.grow_Snake(&s);
            f = f.createNewFruit(&s);
        }

        g.drawGrid(&s,&f);
        cout << endl;
        cout << endl;
        s.steer();
        s.movement();
        sleep(1);
    }while(true);
    return 0;
}

