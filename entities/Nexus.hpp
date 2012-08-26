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
    GLuint* bodyTex; //the main texture of the nexus
    GLuint* colourTex; //the nexus colour texture

public:

    //CONSTRUCTOR
    Nexus(int x, int y, bool p, GLuint* tb, GLuint* tc);

    //DESTRUCTOR
    ~Nexus();

    //FUNCTIONS
    /*update the nexus*/
    void update();

    /*draw the nexus*/
    void draw(int offsetX, int offsetY);

};

#endif
