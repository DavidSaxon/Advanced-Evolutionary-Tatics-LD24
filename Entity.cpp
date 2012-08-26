#include "Entity.hpp"

//FUNCTIONS
/*updates the entity*/
void Entity::update() {}

/*draws the entity, takes the x and y offsets*/
void Entity::draw(int offsetX, int offsetY) {}

/*Set the destination of the unit*/
void Entity::setDest(int x, int y) {}

/*returns true if the mouse pos is on the entity*/
bool Entity::mouseOn(int mouseStartX, int mouseStartY, int mouseX, int mouseY) {}

/*returns true if the mouse pos is on the entity*/
bool Entity::mouseOn(int mouseY, int mouseX) {};

/*Returns true if the entity is colliding with the given object coords*/
bool Entity::collision(int x, int y, int w, int h) {}

/*Stops the entity if it is a moving entity*/
void Entity::stop() {}

/*For units, push each other away when colliding*/
void Entity::pushAway(Entity* other) {}

/*deselects the entity*/
void Entity::deselect() {}

/*getters*/
double Entity::getX() {
    return xPos;
}

double Entity::getY() {
    return yPos;
}

int Entity::getW() {
    return width;
}

int Entity::getH() {
    return height;
}

/*setters*/
void Entity::setX(double x) {
    xPos = x;
}

void Entity::setY(double y) {
    yPos = y;
}
