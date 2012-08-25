/*********************************************************************\
| The main class for the game, runs the engine and reports any errors |
|                                                                     |
| Author: David Saxon                                                 |
\*********************************************************************/
#include <iostream>

#include "Engine.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    Engine engine; //creates the engine

    if (!engine.init()) cout << "Initialisation error!" << endl; //initialise the game

    if (!engine.execute()) cout << "Execution Error!" << endl; //execute the game

    if (!engine.cleanup()) cout << "Cleanupn Error!" << endl; //cleanup the game

    return 0;
}
