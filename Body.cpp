#include "Body.hpp"

Body::Body(int w, int h, GLuint* t) {
    width = w;
    health = h;
    tex = t;
}

Body::~Body() {}
