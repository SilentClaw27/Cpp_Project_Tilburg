#include "grid.h"
#include <utility>
#include <float.h>
#include <list>
#include <iostream>

#ifndef AI_H
#define AI_H

#define DIMENSION 20


class AI{
private:

    typedef struct gridBlock{
        //boolean variable to check whether the block is an obstructing one
        bool obstruct = false;
        //boolean variable to check whether the block has been checked
        bool checked = false;
        //Vector to hold all of the nearby blocks which will be checked from this block
        std::vector<gridBlock*> nearbyBlocks;
        //The parent of the respective block
        gridBlock *block_Parent;

        //Scores which will be used to compare the best path
        float block_f_score;
        float f_score;
        float h_score;

        //X and Y Coordinates of Specific Block
        int x_pos;
        int y_pos;
    }block;

    //Block pointer to hold the data of the entire grid
    block *grid = nullptr;
    //Block pointer to hold the data of the starting point
    block *start = nullptr;
    //Block pointer to hold the data of the destination point
    block *dest = nullptr;

public:

    AI(Snake *s,Fruit *f);
    double find_Score(int block_x,int block_y, int fruit_x,int fruit_y);
    bool obstacle(Snake *s,int x,int y);
    void Algorithm(Snake *s, QGraphicsView *view, QTimer *timer);
    void nextMove(Snake *s, int destination_x,int destination_y);
    bool compare_Score(const block *a, const block *b);
    void gameOver(Snake *s, QGraphicsView *view, QTimer *timer);
};

inline AI::AI(Snake *s,Fruit *f){
    grid = new block[DIMENSION*DIMENSION];

    for(int x=0;x < DIMENSION;x++){
        for(int y=0;y<DIMENSION;y++){
            //Setting the checked variable to false
            grid[y*DIMENSION+x].checked = false;

            //Setting the X and Y positions of the blocks
            grid[y*DIMENSION+x].x_pos = x;
            grid[y*DIMENSION+x].y_pos = y;

            //Setting the Boolean to whether the block is occupied by a part of the snake's body
            grid[y*DIMENSION+x].obstruct = obstacle(s,x,y);

            //Setting the F Score and Block Score to MAX
            grid[y*DIMENSION+x].f_score = FLT_MAX;
            grid[y*DIMENSION+x].h_score = FLT_MAX;
            grid[y*DIMENSION+x].block_f_score = FLT_MAX;

            //Setting the Neighbouring Blocks

            //Block is on the Left Border
            if(x > 0){
                 grid[y*DIMENSION+x].nearbyBlocks.push_back(&grid[y*DIMENSION+(x-1)]);
            }
            //Block is on the Right Border
            if(x < DIMENSION - 1){
                 grid[y*DIMENSION+x].nearbyBlocks.push_back(&grid[y*DIMENSION+(x+1)]);
            }
            //Block is on the Upper Border
            if(y > 0){
                 grid[y*DIMENSION+x].nearbyBlocks.push_back(&grid[(y-1)*DIMENSION+x]);
            }
            //Block is on the Lower Border
            if(y < DIMENSION - 1){
                 grid[y*DIMENSION+x].nearbyBlocks.push_back(&grid[(y+1)*DIMENSION+x]);
            }

            //Setting the Start and Destination Blocks

            if(x == s->getPos_X() && y == s->getPos_Y()){
                start = &grid[y*DIMENSION+x];
            }
            else if(x == f->get_X() && y == f->get_Y()){
                dest = &grid[y*DIMENSION+x];
            }
            else{
                continue;
            }
        }        
    }
}


inline double AI::find_Score(int block_x,int block_y, int fruit_x,int fruit_y){
    //Returns the Euclidean Distance by working out Pythagoras Theorem betwen the source and the destination blocks
    return sqrt(((block_x-fruit_x)*(block_x-fruit_x))+((block_y-fruit_y)*(block_y-fruit_y)));
}

inline bool AI::obstacle(Snake *s,int x,int y){
    Snake *tempS = s;

    //If the block being checked is a part of the snake's body, then it is an obstacle
    if(tempS->getNextSnake() != NULL){
        do{
            tempS = tempS->getNextSnake();

            if((tempS->getPos_X() == x) && (tempS->getPos_Y() == y)){
                return true;
            }
        }while(tempS->getNextSnake() != NULL);
    }
    return false;
}

inline void AI::Algorithm(Snake *s, QGraphicsView *view, QTimer *timer){

    //Setting all the variables of the blocks inside the 20x20 grid to their default value
    for(int x =0;x<DIMENSION;x++){
        for(int y =0;y<DIMENSION;y++){
            grid[y*DIMENSION+x].f_score = INFINITY;
            grid[y*DIMENSION+x].h_score = INFINITY;
            grid[y*DIMENSION+x].block_f_score = INFINITY;
            grid[y*DIMENSION+x].block_Parent = nullptr;
            grid[y*DIMENSION+x].checked = false;
        }
    }

    //Block to be used in the while loop
    block *test_block = start;

    //Setting the Open List which will be used to store the blocks which have not been checked
    std::list<block*> openList;

    //Adding the source block i.e. the location of the snake's head to the Open List
    openList.push_back(start);


    //Loop that will find the path required for the snake
    while(!openList.empty()){
        //Sorting the Open List by the blocks' respective F Score
        openList.sort([](const block* lhs, const block* rhs){
            return lhs->block_f_score < rhs->block_f_score;
        });

        //If the open List is not empty and the block at the very front has already been checked, it is removed from the list
        while(!openList.empty() && openList.front()->checked){
            openList.pop_front();
        }

        //If the Open List becomes empty after the pop, the algorithm is done
        if(openList.empty()){
            break;
        }

        //Setting the Parent Block to be tested and its h score to a default of 0.0
        start->h_score = 0.0f;
        test_block = openList.front();
        test_block->checked = true;




        //Loop that will check all of the parent block's neighbours
        for(block *current_Block : test_block->nearbyBlocks){
            if(!current_Block->checked && !current_Block->obstruct){
                openList.push_back(current_Block);
            }
            //The Score which will compare which block to go to from the parent
            float F_Score = find_Score(test_block->x_pos,test_block->y_pos,current_Block->x_pos,current_Block->y_pos) + test_block->h_score;

            if(F_Score < current_Block->h_score){
                current_Block->block_Parent = test_block;
                current_Block->h_score = F_Score;
                current_Block->block_f_score = current_Block->h_score + find_Score(current_Block->x_pos,current_Block->y_pos,dest->x_pos,dest->y_pos);
            }


        }
    }


    //test_block is now used as a temporary block to trace the path from the destination i.e. the fruit to the source i.e. the snake's head
    test_block = dest;
    //loop_block is our temporary storing object for the while loop in line 206
    block *loop_block = NULL;
    //These are the varibales which will store inside of the the x and y coordinates of loop_block
    int loop_x = 0;
    int loop_y = 0;

    //Tracing the path of the snake to the fruit
    if(dest->block_Parent != NULL){
        //Looping until test_block no longer has a parent which means the snake's head was found
        while(test_block->block_Parent != NULL){
            //Setting the loop_block test_block
            loop_block=test_block;
            //Setting test_block to it's parent
            test_block=test_block->block_Parent;
        }
     //These two variables are the x and y coordinates which will point towards the next block for the snake to move towards
     loop_x = loop_block->x_pos;
     loop_y = loop_block->y_pos;
    }
    else{
        //If the snake does not have anywhere to go, the custom gameover screen is shown
        gameOver(s,view,timer);
    }

    //Setting the New Direction of the snake
    nextMove(s,loop_x,loop_y);

}

inline void AI::nextMove(Snake *s, int destination_x,int destination_y){

    //Setting the new direction depending on the next x and y position which was given by the algorithm
    if((s->getPos_X()-destination_x) < 0 ){
        s->setDir(90);
        return;
    }
    else if((s->getPos_X()-destination_x) > 0 ){
        s->setDir(270);
        return;
    }
    else if((s->getPos_Y()-destination_y) < 0 ){
        s->setDir(180);
        return;
    }
    else if((s->getPos_Y()-destination_y) > 0 ){
        s->setDir(0);
        return;
    }

}


//Special GameOver Screen for when the Algorithm cannot find a new path from the snake to the fruit
inline void AI::gameOver(Snake *s, QGraphicsView *view, QTimer *timer){
    QGraphicsScene *final = new QGraphicsScene();
    final->setSceneRect(0,0,400,400);
    final->setBackgroundBrush(Qt::darkGray);

    std::string scoreText = "Score: ";
    scoreText += std::to_string(s->getLength());
    QGraphicsTextItem *sentence = final->addText("Snake has nowhere to go :(");
    QString QScore = QString::fromStdString(scoreText);
    QGraphicsTextItem *score = final->addText(QScore);

    sentence->setDefaultTextColor(Qt::black);
    score->setDefaultTextColor(Qt::black);
    sentence->setScale(2);
    score->setScale(2);
    sentence->setPos(75,100);
    score->setPos(100,140);

    view->setScene(final);
    timer->stop();
}


#endif // AI_H
