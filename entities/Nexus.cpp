#include "Nexus.hpp"

//CONSTRUCTOR
Nexus::Nexus(int x, int y, bool p, GLuint* tb, GLuint* tc) {
    xPos = x;
    yPos = y;
    player = p;
    width = height = 200;
    bodyTex = tb;
    colourTex = tc;
}

//DESTRUCTOR
Nexus::~Nexus() {}

//FUNCTIONS
/*update the nexus*/
void Nexus::update() {
    
}

/*draw the nexus*/
void Nexus::draw(int offsetX, int offsetY) {
    //draw the body
    glBindTexture(GL_TEXTURE_2D, *bodyTex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(xPos, yPos, -0.0025);
    glTexCoord2f(0.0, 1.0); glVertex3f(xPos, yPos+height, -0.0025);
    glTexCoord2f(1.0, 1.0); glVertex3f(xPos+width, yPos+height, -0.0025);
    glTexCoord2f(1.0, 0.0); glVertex3f(xPos+width, yPos, -0.0025);
    glEnd();
    
    //draw the team colour
    glBindTexture(GL_TEXTURE_2D, *colourTex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(xPos, yPos, -0.002);
    glTexCoord2f(0.0, 1.0); glVertex3f(xPos, yPos+height, -0.002);
    glTexCoord2f(1.0, 1.0); glVertex3f(xPos+width, yPos+height, -0.002);
    glTexCoord2f(1.0, 0.0); glVertex3f(xPos+width, yPos, -0.002);
    glEnd();
}


