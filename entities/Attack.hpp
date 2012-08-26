/*************************************************************\
| This is an attack, has a destination, team, and player type |
\*************************************************************/
#ifndef _ATTACK_H_
    #define _ATTACK_H_

#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "../Entity.hpp"
using namespace std;

class Attack : public Entity {
private:

    //VARIABLES
    double destX; //the x destination
    double destY; //the y destination
    double xMove; //the move speed in the x direction
    double yMove; //the move speed in the y direction
    int type; //the type of attack
    GLuint* tex; //the texture
    int aliveTime; //the time the bullet is alive for

public:

    //CONSTRUCTOR
    Attack(int x, int y, double dx, double dy, int tp, bool p, GLuint* t);

    //DESTRUCTOR
    ~Attack();

    //FUNCTIONS
    /*updates the attack*/
    void update();

    /*draws the attack*/
    void draw(int offsetX, int offserY);

};

#endif
