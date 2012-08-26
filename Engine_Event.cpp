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
    if (sym == SDLK_ESCAPE) running = false;
    if (gameState == MENU) {
        if(sym == SDLK_SPACE) {        
            loadLevel();
            
            Mix_HaltChannel(introChannel);
            
            sound = Mix_LoadWAV("data/music/InGame.wav");
            if(sound == NULL) {
                fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
            }

            int channel;

            channel = Mix_PlayChannel(-1, sound, -1);
            if(channel == -1) {
                fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
            }
            
            gameState = LEVEL;
        }
    }
    if (gameState == LEVEL) {
        if (sym == SDLK_u) buildUnit(true);
        if (sym == SDLK_i) {
            if (moneyWait > 0 && money >= 500) {
                --moneyWait;
                money -= 500;
            }
        }
        if (sym == SDLK_y) {
            if (money >= 750 && lowChance > 10) {
                lowChance -= 3;
                medChance -= 2;
                --highChance;
                money -= 750;
            }
        }
        if (sym == SDLK_UP) {
            if (upDown == 0) upDown = 1;
        }
        if (sym == SDLK_DOWN) {
            if (upDown == 0) upDown = 2;
        }
        if (sym == SDLK_LEFT) {
            if (leftRight == 0) leftRight = 1;
        }
        if (sym == SDLK_RIGHT) {
            if (leftRight == 0) leftRight = 2;
        }
    }
}

void Engine::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    if (gameState == LEVEL) {
        if (sym == SDLK_UP) {
            if (upDown == 1) upDown = 0;
        }
        if (sym == SDLK_DOWN) {
            if (upDown == 2) upDown = 0;
        }
        if (sym == SDLK_LEFT) {
            if (leftRight == 1) leftRight = 0;
        }
        if (sym == SDLK_RIGHT) {
            if (leftRight == 2) leftRight = 0;
        }
    }
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
