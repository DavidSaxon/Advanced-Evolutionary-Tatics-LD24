/**************************************************************\
| This is a basic unit that can evolve into more complex units |
\**************************************************************/
#ifndef _UNIT_H_
    #define _UNIT_H_

#include <iostream>
#include <math.h>
#include <stdlib.h>
    
#include "../Entity.hpp"
using namespace std;

class Unit : public Entity {
private:
    
    //VARIABLES
    bool player; //is true when is the player's unit
    int moveSpeed; //the move speed of the unit
    int destX; //the x position of the units destination
    int destY; //the y position of the unit's destination
    double xMove; //move speed in x direction
    double yMove; //move speed in y direction
    bool move; //is true when the unit should move
    
public:

    //CONSTRUCTOR
    Unit(int x, int y, bool p);
    
    //DESTRUCTOR
    ~Unit();
    
    //FUNCTIONS
    /*updates the Unit*/
    void update();
    
    /*draws the Unit*/
    void draw(int offsetX, int offsetY);
    
    /*Set the destination of the unit*/
    void setDest(int x, int y);
    
    /*only used for enemy units where they find a new direction*/
    void newDirection();
    
    /*Selects the unit if the mouse is on*/
    bool mouseOn(int mouseStartX, int mouseStartY, int mouseX, int mouseY);
    
    /*Returns true if the unit is colliding with the given object coords*/
    bool collision(int x, int y, int w, int h);
    
    /*Stops the entity if it is a moving entity*/
    void stop();
    
    /*Push the other unit away and move away*/
    void pushAway(Entity* other);
    
    /*Deselects the unit*/
    void deselect();
    
};

#endif
