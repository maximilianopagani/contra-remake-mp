//============================================================================
// Name        : Test.cpp
// Author      : fewfwe
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDLView.h"
#include "Character.h"

using namespace std;

int main() {

	SDL_View* vista = new SDL_View();
	Character* player = new Character(vista);

	vista->initLoader();

	for(int i=0 ; i<25 ; i++) {
		vista->clear();

		player->render();

		vista->show();
		vista->delay(50);
	}

	vista->clean();

	return 0;
}




/*std::list<std::string> imagenes;
	std::list<std::string>::iterator imagenIterator;*/
