#include "Attack.hpp"

//CONSTRUCTOR
Attack::Attack(int x, int y, double dx, double dy, int tp, bool p, GLuint* t) {
    xPos = x;
    yPos = y;
    destX = dx;
    destY = dy;
    type = tp;
    tex = t;
    dead = false;
    player = p;
    aliveTime = 120;

    //set the damage
    switch (type) {
        case 0:
            damage = 10;
            width = height = 10;
            break;
        case 1:
            damage = 25;
            width = height = 16;
            break;
        case 2:
            damage = 50;
            width = height = 20;
            break;
    }
}

//DESTRUCTOR
Attack::~Attack() {}

//FUNCTIONS
/*updates the attack*/
void Attack::update() {
    //get the move speeds
    xMove = 10*(cos((fabs(destY-yPos))/(sqrt(pow(fabs(destX-xPos), 2)+pow(fabs(destY-yPos), 2))))/1.570796326);
    yMove = 10*(cos((fabs(destX-xPos))/(sqrt(pow(fabs(destX-xPos), 2)+pow(fabs(destY-yPos), 2))))/1.570796326);

    if (destX < xPos) xMove = -xMove;
    if (destY < yPos) yMove = -yMove;

    //move
    //if ((xPos >= destX-10 && xPos <= destX+10) && (yPos >= destY-10 && yPos <= destY+10)) dead = true;
    xPos += xMove;
    yPos += yMove;

    --aliveTime;
    if (aliveTime < 1) dead = true;
}

/*draws the attack*/
void Attack::draw(int offsetX, int offsetY) {
    glBindTexture(GL_TEXTURE_2D, *tex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(xPos+offsetX, yPos+offsetY, -0.001);
    glTexCoord2f(0.0, 1.0); glVertex3f(xPos+offsetX, yPos+height+offsetY, -0.001);
    glTexCoord2f(1.0, 1.0); glVertex3f(xPos+width+offsetX, yPos+height+offsetY, -0.001);
    glTexCoord2f(1.0, 0.0); glVertex3f(xPos+width+offsetX, yPos+offsetY, -0.001);
    glEnd();
}


