#ifndef _FANG_H_
    #define _FANG_H_
    
#include <iostream>
#include <SDL/SDL_opengl.h>

using namespace std;

class Fang {
public:

    int type;
    GLuint* tex;

    Fang(int tp, GLuint* t);
    
    ~Fang();
};

#endif
