#include "Unit.hpp"

//CONSTRUCTOR
Unit::Unit(int x, int y, bool p) {
    xPos = x;
    yPos = y;
    player = p;

    //initialise variables
    width = 25;
    height = 25;
    selected = false;
    moveSpeed = 2;
    destX = xPos;
    destY = yPos;
    move = false;
    xMove = 0;
    yMove = 0;

    if (!player) newDirection();
}

//DESTRUCTOR
Unit::~Unit() {}

//FUNCTIONS
/*updates the Unit*/
void Unit::update() {
    if (player) { //if is a player unit
        if (move) { //move the unit towards it's destination
            if ((xPos >= destX-moveSpeed && xPos <= destX+moveSpeed) && (yPos >= destY-moveSpeed && yPos <= destY+moveSpeed)) move = false; //stop moving
            else {
                if (destX > xPos) xPos += xMove;
                else xPos -= xMove;
                if (destY > yPos) yPos += yMove;
                else yPos -= yMove;
            }
        }
    }
    else { //if an enemy unit move in a random path
        int change = rand()%200;
        if (change < 2) { //change the unit's direction
            newDirection();
        }
        else if (change > 197) { //stop the unit
            move = false;
        }
        else if (move) { //move the unit
            xPos += xMove;
            yPos += yMove;
        }
    }
}

/*draws the Unit*/
void Unit::draw(int offsetX, int offsetY) {
    double x1 = floor(xPos+0.5);
    double x2 = floor(xPos+width+0.5);
    double y1 = floor(yPos+0.5);
    double y2 = floor(yPos+height+0.5);
    glColor4d(0.0, 1.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();

    if (selected) { //if the unit is selected draw the slected box
        glColor4d(1.0, 1.0, 0.0, 0.7);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x1-3, y1-3);
        glVertex2f(x2+4, y1-3);
        glVertex2f(x2+4, y2+4);
        glVertex2f(x1-3, y2+4);
        glEnd();
    }
}

/*Set the destination of the unit*/
void Unit::setDest(int x, int y) {
    destX = x;
    destY = y;
    xMove = moveSpeed*(cos((fabs(destY-yPos))/(sqrt(pow(fabs(destX-xPos), 2)+pow(fabs(destY-yPos), 2))))/1.570796326);
    yMove = moveSpeed*(cos((fabs(destX-xPos))/(sqrt(pow(fabs(destX-xPos), 2)+pow(fabs(destY-yPos), 2))))/1.570796326);
    move = true;
}

/*only used for enemy units where they find a new direction*/
void Unit::newDirection() {
    xMove = (rand()%(2*moveSpeed))-moveSpeed;
    int ne = rand()%2; //whether the y move should be negative or positive
    if (ne) yMove = -(moveSpeed-fabs(xMove));
    else yMove = moveSpeed-fabs(xMove);
    move = true;
}

/*Selects the unit if the mouse is on*/
bool Unit::mouseOn(int mouseStartX, int mouseStartY, int mouseX, int mouseY) {
    //set up the drag box coords
    int dbx1, dbx2, dby1, dby2 = 0;
    if (mouseStartX <= mouseX) {
        dbx1 = mouseStartX;
        dbx2 = mouseX;
    }
    else {
        dbx1 = mouseX;
        dbx2 = mouseStartX;
    }
    if (mouseStartY <= mouseY) {
        dby1 = mouseStartY;
        dby2 = mouseY;
    }
    else {
        dby1 = mouseY;
        dby2 = mouseStartY;
    }

    if (((xPos > dbx1 && xPos) && (xPos+width > dbx1 && xPos+width < dbx2)) &&
        ((yPos > dby1 && yPos < dby2) && (yPos+height > dby1 && yPos+height < dby2))
        && player) selected = true;

    return selected;
}

/*Returns true if the unit is colliding with the given object coords*/
bool Unit::collision(int x, int y, int w, int h) {
    bool c = (((xPos >= x && xPos <= x+w) || (xPos+width  >= x && xPos+width  <= x+w)) &&
              ((yPos >= y && yPos <= y+h) || (yPos+height >= y && yPos+height <= y+h)));
    //if there is a collision bounce back a bit
    if (c) {
        if (xPos < x) xPos -= 1;
        else xPos += 1;
        if (yPos < y) yPos -= 1;
        else yPos += 1;
    }

    return c;
}

/*Stops the entity if it is a moving entity*/
void Unit::stop() {
    move = false;
}

/*Push the other unit away and move away*/
void Unit::pushAway(Entity* other) {
    if (xPos <= other->getX()) {
        xPos -= 1;
        other->setX(other->getX()+1);
    }
    else {
        xPos += 1;
        other->setX(other->getX()-1);
    }
    if (yPos < other->getY()) {
        yPos -= 1;
        other->setY(other->getY()+1);
    }
    else {
        yPos += 1;
        other->setY(other->getY()-1);
    }
}

/*Deselects the unit*/
void Unit::deselect() {
    selected = false;
}
