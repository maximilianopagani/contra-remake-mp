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

	pos =0;
	posCaminando=0;
	rebote = true;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x= 0;
	srcRect.y = 0;

	desRect.h = 64;
	desRect.w = 64 ;
	desRect.x = 200 ;
	desRect.y = 200 ;

	spriteNames[0]= "imagenes/espera1.png";
	spriteNames[1]= "imagenes/espera2.png";
	spriteNames[2]= "imagenes/espera3.png";
	spriteNames[3]= "imagenes/espera2.png";

	spriteCaminando[0]= "imagenes/caminando1.png";
	spriteCaminando[1]= "imagenes/caminando2.png";
	spriteCaminando[2]= "imagenes/caminando3.png";
	spriteCaminando[3]= "imagenes/caminando4.png";


}

Personaje::~Personaje() {

}

void Personaje::eventos(SDL_Event evento){


	 switch(evento.key.keysym.sym){


	        case SDLK_SPACE:
					if(rebote){
						saltando();
						rebote = false;
						break;
					}

					rebote = true ;
					break;

	        case SDLK_LEFT:

	        	if(rebote){
	        			desRect.x = desRect.x -3  ;
	        			caminando();
	        			rebote = false;
	        				break;
	        		}

	        		rebote = true ;
	        		break;

	        case SDLK_RIGHT:
	        	if(rebote){
	        			desRect.x = desRect.x +3  ;
	        			caminando();
	        			rebote = false;
	        				break;
	        		}

	        		rebote = true ;
	        		break;

	        case SDLK_DOWN:
	        	personajeTextura = TexturaGenerador::cargarTextura("imagenes/disparobajo.png",renderer);
	            break;
	        case SDLK_UP:
	        	personajeTextura = TexturaGenerador::cargarTextura("imagenes/disparoalto.png",renderer);
	        	break;

	        case SDLK_LCTRL:
	        	 personajeTextura = TexturaGenerador::cargarTextura("imagenes/disparoagachado.png",renderer);
	        	 break;

	        case SDLK_KP_0:
	        	 personajeTextura = TexturaGenerador::cargarTextura("imagenes/disparofrontal.png",renderer);
	        	 break;

	        default:
	            break;
	    }
}

void Personaje:: actualizar(){
	personajeTextura = TexturaGenerador::cargarTextura(spriteNames[pos],renderer);
	pos++;
	if(pos == 4) pos =0 ;
}

void Personaje::renderizar(){
	SDL_RenderCopy(renderer,personajeTextura,NULL,&desRect);
}

void Personaje::limpiar(){

	spriteNames[0] = NULL;
	spriteNames[1] = NULL;
	spriteNames[2] = NULL;
	spriteNames[3] = NULL;
	SDL_DestroyTexture(personajeTextura);

}

void Personaje::saltando(){
	for(int i=0 ; i < 15 ; i++){
		desRect.y = desRect.y -5 ;
		SDL_RenderClear(renderer);
		personajeTextura = TexturaGenerador::cargarTextura("imagenes/salto1.png",renderer);
		renderizar();
		SDL_RenderPresent(renderer);
		SDL_Delay(15);
	}
	for(int i=0 ; i < 14 ; i++){
		 desRect.y = desRect.y +5 ;
		 SDL_RenderClear(renderer);
		 personajeTextura = TexturaGenerador::cargarTextura("imagenes/salto2.png",renderer);
		 renderizar();
	     SDL_RenderPresent(renderer);
		 SDL_Delay(15);
	}
	desRect.y = desRect.y +5 ;
	SDL_RenderClear(renderer);
	personajeTextura = TexturaGenerador::cargarTextura("imagenes/espera1.png",renderer);
	renderizar();
	SDL_RenderPresent(renderer);
	SDL_Delay(30);
}

void Personaje::caminando(){

	personajeTextura = TexturaGenerador::cargarTextura(spriteCaminando[posCaminando],renderer);
	posCaminando++;
	if(posCaminando == 4) posCaminando = 0;

}
