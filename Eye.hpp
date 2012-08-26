#ifndef _EYE_H_
    #define _EYE_H_
        
#include <iostream>
#include <SDL/SDL_opengl.h>

using namespace std;

class Eye {
public:

    int range;
    GLuint* tex;
    
    Eye(int r, GLuint *t);
    
    ~Eye();
};

#endif
