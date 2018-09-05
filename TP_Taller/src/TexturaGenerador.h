/*
 * TexturaGenerador.h
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */

#ifndef TEXTURAGENERADOR_H_
#define TEXTURAGENERADOR_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TexturaGenerador {


public:

	//TexturaGenerador();
	//virtual ~TexturaGenerador();
	static SDL_Texture* cargarTextura(const char* nombre, SDL_Renderer* ren );


};

#endif /* TEXTURAGENERADOR_H_ */
