/*****************************************************************\
| Entity is an abstract class that all entites in the game extend |
\*****************************************************************/
#ifndef _ENTITY_H_
    #define _ENTITY_H_

#include <iostream>
#include <SDL/SDL_opengl.h>

using namespace std;

class Entity {
protected:

    //VARIABLES
    int xPos; //the current x position of the entity
    int yPos; //the current y position of the entity
    int width; //the general width of the entity
    int height; //the general height of the entity

public:

    //FUNCTIONS
    /*updates the entity*/
    virtual void update();

    /*draws the entity, takes the x and y offsets*/
    virtual void draw(int offsetX, int offsetY);

    /*returns true if the mouse pos is on the entity*/
    virtual bool mouseOn(int mouseStartX, int mouseStartY, int mouseX, int mouseY);

    /*deselects the entity*/
    virtual void deselect();

};

#endif
