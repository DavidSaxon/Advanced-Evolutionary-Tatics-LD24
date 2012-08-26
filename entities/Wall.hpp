/******************************************************\
| An enviroment obstacle, units cannot pass through it |
\******************************************************/
#ifndef _WALL_H_
    #define _WALL_H_
    
#include <iostream>

#include "../Entity.hpp"
using namespace std;

class Wall : public Entity {
private:

    

public:

    //CONSTRUCTOR
    Wall(int x, int y);
    
    //DESTRUCTOR
    ~Wall();
    
    //FUNCTIONS
    /*update the wall*/
    void update();

    /*draw the wall*/
    void draw(int offsetX, int offsetY);

};

#endif
