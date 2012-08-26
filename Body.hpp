/***********************\
| This is a unit's body |
\***********************/
#ifndef _BODY_H_
    #define _BODY_H_
    
#include <iostream>
#include <SDL/SDL_opengl.h>

using namespace std;

class Body {
public: //running out of time everything from now on is public

    int width; //the width of the body
    int health; //the health of the body
    GLuint* tex;
    
    //ok no more comments, not enough time
    Body(int w, int h, GLuint* t);
    
    ~Body();
       
};

#endif
