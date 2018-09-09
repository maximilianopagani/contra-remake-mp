#ifndef HEADERS_H
#define HEADERS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <list>

#include "Game.h"
#include "Grapher.h"
#include "Level.h"

using namespace std;

#endif /* SRC_HEADERS_H_ */

/*
 *
 * Codigo que me puede servir luego
 *
 class KeyboardHandler {
    handleKeyboardEvent(SDL Event) {
        keyState[event.code] = event.state;
    }

    bool isPressed(keyCode) {
        return (keyState[keyCode] == PRESSED);
    }

    bool isReleased(keyCode) {
        return (keyState[keyCode] == RELEASED);
    }

    keyState[];
}

...

while(SDL Pull events)
{
    switch(event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
                keyHandler.handleKeyboardEvent(event);
            break;
        case SDL_ANOTHER_EVENT:
                ...
            break;
    }
}

// When you need to use it:
if(keyHandler.isPressed(SOME_KEY) && keyHandler.isPressed(SOME_OTHER_KEY))
    doStuff(TM);
 */
