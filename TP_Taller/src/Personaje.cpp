/*
 * Personaje.cpp
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */

#include "Personaje.h"

extern Game* synergy;

Personaje::Personaje(std::string texturePath)
{
	personajeTextura = Grapher::loadTexture(texturePath.c_str());

	pos = 0;
	posCaminando = 0;
	rebote = true;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	desRect.h = 64;
	desRect.w = 64 ;
	desRect.x = 200 ;
	desRect.y = 225 ;

	spriteNames[0] = "imagenes/espera1.png";
	spriteNames[1] = "imagenes/espera2.png";
	spriteNames[2] = "imagenes/espera3.png";
	spriteNames[3] = "imagenes/espera2.png";

	spriteCaminando[0] = "imagenes/caminando1.png";
	spriteCaminando[1] = "imagenes/caminando2.png";
	spriteCaminando[2] = "imagenes/caminando3.png";
	spriteCaminando[3] = "imagenes/caminando4.png";

	lastShotTime = 0;
	shotCooldown = 200; // EN milisegundos. ESto podria modelarse dentro de una arma, como una caracteristica de la misma, si pidiesen distintas armas.
}

Personaje::~Personaje() {}

void Personaje::handleEvent(SDL_Event evento)
{
	 switch(evento.key.keysym.sym)
	 {
	 	 case SDLK_SPACE:
			if(rebote)
			{
				this->jumping();
				rebote = false;
				break;
			}

			rebote = true ;
			break;

		case SDLK_LEFT:
			if(rebote)
			{
				desRect.x = desRect.x-3;
				this->walking();
				rebote = false;
				break;
			}

			rebote = true ;
			break;

		case SDLK_RIGHT:
			if(rebote)
			{
				desRect.x = desRect.x+3;
				this->walking();
				rebote = false;
				break;
			}

			rebote = true ;
			break;

		case SDLK_z:
			this->shoot(); // Ver porque se esta ejecutando cada case 2 veces, hay algo que no esta bien. Las texturas tambien, se cargan 2 veces. Salvo flecha izq y derecha, el resto duplica todos
			// EL problema es que faltaba un --else if(evento.type == SDL_KEYDOWN)-- en el PollEvent, ya que llamaba a personaje.eventhandler aún para otros eventos no de teclado
			break;

		case SDLK_x:
			this->shoot(250);
			break;

		case SDLK_DOWN:
			personajeTextura = Grapher::loadTexture("imagenes/disparobajo.png"); // MUY LENTO, CONTINUAMENTE ESTA ACCEDIENDO A DISCO Y CARGANDO TEXTURAS, MEJOR CARGAR TODAS Y SELECCIONAR LUEGO SEGUN EVENTO
			break;

		case SDLK_UP:
			personajeTextura = Grapher::loadTexture("imagenes/disparoalto.png");
			break;

		case SDLK_LCTRL:
			 personajeTextura = Grapher::loadTexture("imagenes/disparoagachado.png");
			 break;

		case SDLK_KP_0:
			 personajeTextura = Grapher::loadTexture("imagenes/disparofrontal.png");
			 break;

		default:
			break;
	 }
}

void Personaje::shoot(int distanceToTravel)
{
	Uint32 currentShotTime = SDL_GetTicks();

	if((SDL_GetTicks() - lastShotTime) > shotCooldown)
	{
		synergy->catchFiredBullet(new Bullet(desRect.x, desRect.y, 15, 0, distanceToTravel));
		lastShotTime = currentShotTime;
	}
}

void Personaje::update()
{
	personajeTextura = Grapher::loadTexture(spriteNames[pos]);
	pos++;

	if(pos == 4)
		pos = 0;
}

void Personaje::render()
{
	SDL_RenderCopy(Grapher::gameRenderer, personajeTextura, NULL, &desRect);
}

void Personaje::clean()
{
	SDL_DestroyTexture(personajeTextura);
	personajeTextura = NULL;
}

void Personaje::jumping()
{
	for(int i=0 ; i < 15 ; i++)
	{
		desRect.y = desRect.y -5 ;
		SDL_RenderClear(Grapher::gameRenderer);
		personajeTextura = Grapher::loadTexture("imagenes/salto1.png");
		this->render();
		SDL_RenderPresent(Grapher::gameRenderer);
		SDL_Delay(15);
	}

	for(int i=0 ; i < 14 ; i++)
	{
		 desRect.y = desRect.y +5 ;
		 SDL_RenderClear(Grapher::gameRenderer);
		 personajeTextura = Grapher::loadTexture("imagenes/salto2.png");
		 this->render();
	     SDL_RenderPresent(Grapher::gameRenderer);
		 SDL_Delay(15);
	}

	desRect.y = desRect.y +5 ;
	SDL_RenderClear(Grapher::gameRenderer);
	personajeTextura = Grapher::loadTexture("imagenes/espera1.png");
	this->render();
	SDL_RenderPresent(Grapher::gameRenderer);
	SDL_Delay(30);
}

void Personaje::walking()
{
	personajeTextura = Grapher::loadTexture(spriteCaminando[posCaminando]);
	posCaminando++;

	if(posCaminando == 4)
		posCaminando = 0;
}
