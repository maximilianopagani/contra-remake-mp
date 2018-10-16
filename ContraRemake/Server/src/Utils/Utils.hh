//============================================================================
// Name        : Utils.hh
// Author      : pola17
//============================================================================

#ifndef UTILS_HH_
#define UTILS_HH_

#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

using namespace std;

class Utils
{
public:
    static const string getTimestamp();
    static const string getDate();
    static const string toUppercase(string aString);

    static bool initTimer() { return (SDL_Init(SDL_INIT_TIMER) == 0); }
	static Uint32 getTicks() { return SDL_GetTicks(); }
	static void setDelay(int milisecs) { SDL_Delay(milisecs); }
};

#endif /* UTILS_HH_ */
