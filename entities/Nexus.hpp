/*********************************************************\
| The nexus is where the units for each team are produced |
\*********************************************************/
#ifndef _NEXUS_H_
    #define _NEXUS_H_

#include <iostream>
#include <math.h>

#include "../Entity.hpp"
using namespace std;

class Nexus : public Entity {
private:

    //VARIABLES
    bool player; //is true when is the player's unit

public:

    //CONSTRUCTOR
    Nexus(int x, int y, bool p);

    //DESTRUCTOR
    ~Nexus();

    //FUNCTIONS
    /*update the nexus*/
    void update();

    /*draw the nexus*/
    void draw(int offsetX, int offsetY);

};

#endif
