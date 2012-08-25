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
