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
    double xPos; //the current x position of the entity
    double yPos; //the current y position of the entity
    int width; //the general width of the entity
    int height; //the general height of the entity

public:

    //VARIABLES
    bool selected; //is true when the unit is selected
    bool player; //is true when is the player's unit
    Entity* target; //the entity this unit is targeting
    int damage; //the damage the unit inflicts
    int attackType;
    bool attackFlag; //is true when the unit wants to attack
    bool dead; //is true when the entity is dead
    int health; //the units health

    //FUNCTIONS
    /*updates the entity*/
    virtual void update();

    /*draws the entity, takes the x and y offsets*/
    virtual void draw(int offsetX, int offsetY);

    /*Set the destination of the unit*/
    virtual void setDest(int x, int y);

    /*returns true if the mouse pos is on the entity*/
    virtual bool mouseOn(int mouseY, int mouseX);

    /*returns true if the mouse pos is on the entity*/
    virtual bool mouseOn(int mouseStartX, int mouseStartY, int mouseX, int mouseY);
    
    /*Returns true if the entity is colliding with the given object coords*/
    virtual bool collision(int x, int y, int w, int h);
    
    /*Stops the entity if it is a moving entity*/
    virtual void stop();
    
    /*For units, push each other away when colliding*/
    virtual void pushAway(Entity* other);

    /*deselects the entity*/
    virtual void deselect();
    
    /*getters*/
    double getX();
    
    double getY();
    
    int getW();
    
    int getH();
    
    /*setters*/
    void setX(double x);
    
    void setY(double y);

};

#endif
