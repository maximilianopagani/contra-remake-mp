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
#include <SDL2/SDL_timer.h>

using namespace std;

class Utils
{
public:
    static const string getTimestamp();
    static const string getDate();
    static const string toUppercase(string aString);
	static Uint32 getTicks() { return SDL_GetTicks(); }
};

#endif /* UTILS_HH_ */
