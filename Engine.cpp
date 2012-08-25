#include "Engine.hpp"

//CONSTRUCTOR
Engine::Engine() {}

//DESTRUCTOR
Engine::~Engine() {}

//FUNCTIONS
/*Initialise the game*/
bool Engine::init() {
    //initialise variables
    running = true;
    gameState = LEVEL; //TODO: change to MENU in final

    //initialise sdl
    initSDL();

    //open the window
    const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo(); //get the video info
    int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_FULLSCREEN; //sets the window flags
    if(videoInfo->hw_available) flags |= SDL_HWSURFACE; //check to see if hardware surfaces are enabled
    else flags |= SDL_SWSURFACE;
    if(videoInfo->blit_hw) flags |= SDL_HWACCEL; //check to see if hardware supports blitting
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    if ((display = SDL_SetVideoMode(0, 0, 32, flags)) == NULL) return false; //sets up the video mode

    //get the width and height
    width = display->w;
    height = display->h;

    return true; //everything is initialised
}

/*Initialises SDL*/
bool Engine::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
    return true; //sdl has been initialised
}

/*Initialise openGL*/
bool Engine::initGL() {
    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, width, height); //TODO: make sure this is right
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1920, 1080, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();

    return true; //openGL has been initialised
}

/*Run the main game loop*/
bool Engine::execute() {
    SDL_Event event; //creates a new event

    //start the main game loop
    while (running) {
        while (SDL_PollEvent(&event)) onEvent(&event); //polls the events
        
        //clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //checks to see what state the game is in
        switch (gameState) {
            case MENU:
                break;
            case LEVEL: //update the level
                levelUpdate();
                break;
        }
        
        //Swap the buffers
        SDL_GL_SwapBuffers();
    }

    return true; //the game has finished running
}

/*Cleanup the game*/
bool Engine::cleanup() {
    SDL_FreeSurface(display); //Remove the display window

    return true; //cleanup has compeleted
}
