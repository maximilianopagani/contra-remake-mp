/*
 * Personaje.cpp
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */

#include "Personaje.h"
#include "TexturaGenerador.h"

Personaje::Personaje(const char* nombre,SDL_Renderer* ren) {

	renderer = ren ;
	personajeTextura = TexturaGenerador::cargarTextura(nombre,renderer);

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x= 0;
	srcRect.y = 0;

	desRect.h = 64;
	desRect.w = 64 ;
	desRect.x = 40 ;
	desRect.y = 40 ;
}

Personaje::~Personaje() {

}

void Personaje::eventos(SDL_Event evento){

	 switch(evento.key.keysym.sym){

	        case SDLK_UP:
	            desRect.y = desRect.y - 4 ;
	            break;
	        case SDLK_LEFT:
	            desRect.x = desRect.x-4;
	            personajeTextura = TexturaGenerador::cargarTextura("personajeleft.png",renderer);

	            break;
	        case SDLK_RIGHT:
	             desRect.x = desRect.x+4;
		         personajeTextura = TexturaGenerador::cargarTextura("personaje.png",renderer);

	            break;
	        case SDLK_DOWN:
	            desRect.y = desRect.y + 4;
	            break;
	        default:
	            break;
	    }
}

void Personaje:: actualizar(){

}

void Personaje::renderizar(){
	SDL_RenderCopy(renderer,personajeTextura,NULL,&desRect);
}
