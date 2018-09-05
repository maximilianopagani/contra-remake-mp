/*
 * TexturaGenerador.cpp
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */

#include "TexturaGenerador.h"

/*TexturaGenerador::TexturaGenerador() {
	// TODO Auto-generated constructor stub

}

TexturaGenerador::~TexturaGenerador() {
	// TODO Auto-generated destructor stub
}*/

SDL_Texture* TexturaGenerador::cargarTextura(const char* nombre, SDL_Renderer* ren ){
	SDL_Surface* superficieTemp=IMG_Load(nombre);
	SDL_Texture* textura = SDL_CreateTextureFromSurface(ren,superficieTemp);
	SDL_FreeSurface(superficieTemp);

	return textura;
}
