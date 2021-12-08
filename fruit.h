#include "snake.h"

#ifndef GUITEST_FRUIT_H
#define GUITEST_FRUIT_H
class Fruit: public QGraphicsRectItem{
private:
    int pos_x = 0;
    int pos_y = 0;
public:
    Fruit();
    int get_X();
    int get_Y();
    char getSymbol();

    void set_X(int x);
    void set_Y(int y);
    bool fruitOnSnake(Snake *s);
    void createNewFruit(Snake *s);
    void grow_Snake(Snake *s,int x, int y,QGraphicsScene *canvas);
    bool checkEat(Snake *s);

};

inline Fruit::Fruit(){
    this->pos_x = 0;
    this->pos_y = 0;
}

//Getting the X Position of the Fruit
inline int Fruit:: get_X(){
    return this->pos_x;
}

//Getting the Y Position of the Fruit
inline int Fruit:: get_Y(){
    return this->pos_y;
}

//Setting the new X Position of the new Fruit
inline void Fruit:: set_X(int x){
    this->pos_x = x;
}

//Setting the new Y Position of the new Fruit
inline void Fruit:: set_Y(int y){
    this->pos_y = y;
}

//Function creating a new Fruit
inline void Fruit:: createNewFruit(Snake *s){
    bool correct = true;
    int x =0;
    int y= 0;
    srand(time(NULL));
    do {
        //Setting two random x and y positions for the new fruit
        x = rand() % 20;
        y = rand() % 20;

        //Setting these values into the object
        this->pos_x = x;
        this->pos_y = y;

        //Checking if the Fruit is on the Snake
        correct = this->fruitOnSnake(s);
    //Repeating the process if the fruit is placed on the snake
    }while(!correct);

    //Drawing the position of the new Fruit
    this->setRect(pos_x*20,pos_y*20,20,20);
}

//Function checking whether the Snake has eaten the Fruit
inline bool Fruit:: checkEat(Snake *s){
    if((s->getPos_X() == this->get_X()) && (s->getPos_Y() == this->get_Y())){
        return true;
    }
    else{
        return false;
    }
}

//Function Growing the Snake after eating a piece of fruit
inline void Fruit:: grow_Snake(Snake *s, int x, int y, QGraphicsScene *canvas){
    //Incrementing the Length of the Snake
    s->setLength();
    //Setting a temporary snake object to hold the new x and y positions together with the snake body parts which follow it.
    Snake *temp = new Snake;
    temp->setPos_X(x);
    temp->setPos_Y(y);
    temp->setNext(s->getNextSnake());

    //Adding the new body part to the head
    s->setNext(temp);
    //Drawing the new Snake Body on the Canvas and adding it
    temp->setRect(temp->getPos_X()*20,temp->getPos_Y()*20,20,20);
    temp->setBrush(Qt::black);
    canvas->addItem(temp);
}

//Checking if the new Fruit being created is intersecting with the snake
inline bool Fruit::fruitOnSnake(Snake *s){
    Snake *temp = s;


    if(this->checkEat(s)){
        return false;
    }

    while(temp->getNextSnake() != NULL){
        temp = temp->getNextSnake();
        if(this->checkEat(temp)){
            return false;
        }
    }
    return true;
}
#endif //GUITEST_FRUIT_H
