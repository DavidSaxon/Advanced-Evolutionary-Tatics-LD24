/***********************************************************************\
| This is a grunt unit, every unit starts as a grunt and can be evovled |
\***********************************************************************/
#ifndef _GRUNT_H_
    #define _GRUNT_H_

#include <iostream>
    
#include "../Entity.hpp"
using namespace std;

class Grunt : public Entity {
private:
    
    //VARIABLES
    bool player; //is true when is the player's unit
    
public:

    //CONSTRUCTOR
    Grunt(int x, int y, bool p);
    
    //DESTRUCTOR
    ~Grunt();
    
    //FUNCTIONS
    /*updates the grunt*/
    void update();
    
    /*draws the grunt*/
    void draw(int offsetX, int offsetY);
    
};

#endif
