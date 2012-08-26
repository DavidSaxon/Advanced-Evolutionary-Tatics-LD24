#ifndef _LEG_H_
    #define _LEG_H_
    
#include <iostream>
#include <SDL/SDL_opengl.h>

using namespace std;

class Leg {
public:

    int speed;
    GLuint* tex;
    
    Leg(int s, GLuint* t);
    
    ~Leg();
};

#endif
