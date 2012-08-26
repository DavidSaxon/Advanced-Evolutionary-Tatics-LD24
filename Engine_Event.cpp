#include "Engine.hpp"

/*Handles events*/
void Engine::onEvent(SDL_Event* event) {
    Event::onEvent(event); //gets and stores the current event
}

/*When the exit button is pressed*/
void Engine::onExit() {
    running = false; //exit the game
}

/*When a key is pressed down*/
void Engine::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    if (sym == SDLK_F7) running = false; //TODO: Remove me
}

/*When the mouse is moved*/
void Engine::onMouseMove(int mX, int mY, int relX, int relY, bool left,bool right,bool middle) {
    mouseX = mX*scaleX;
    mouseY = mY*scaleY;
}

/*When the left mouse button is pressed*/
void Engine::onLButtonDown(int mX, int mY) {
    leftMouseDown = true;
    leftPressed = true;
    mouseStartX = mX*scaleX;
    mouseStartY = mY*scaleY;
}

/*When the left mouse button is released*/
void Engine::onLButtonUp(int mX, int mY) {
    leftMouseDown = false;
    leftReleased = true;
}

/*When the right mouse button is pressed*/
void Engine::onRButtonDown(int mX, int mY) {
    rightPressed = true;
}

/*When the right button is released*/
void Engine::onRButtonUp(int mX, int mY) {
    rightReleased = true;
}
