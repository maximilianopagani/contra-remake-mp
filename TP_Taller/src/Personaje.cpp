/*
 * Personaje.cpp
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */

#include "Personaje.h"

extern Game* synergy;

#define GRAVITY_SPEED 0.4 // Pixels per iteration

Personaje::Personaje()
{
	//Texturas de disparos
	crouchTexture = Grapher::loadTexture("imagenes/disparoagachado.png");
	aimDownTexture = Grapher::loadTexture("imagenes/disparobajo.png");
	aimUpTexture = Grapher::loadTexture("imagenes/disparoalto.png");
	aimFrontTexture = Grapher::loadTexture("imagenes/disparofrontal.png");
	//Texturas de personaje quieto
	idleTexture[0] = Grapher::loadTexture("imagenes/espera1.png");
	idleTexture[1] = Grapher::loadTexture("imagenes/espera2.png");
	idleTexture[2] = Grapher::loadTexture("imagenes/espera3.png");
	idleTexture[3] = idleTexture[1]; // Repite "imagenes/espera2.png"

	//Texturas de personaje caminando
	walkingTexture[0] = Grapher::loadTexture("imagenes/caminando1.png");
	walkingTexture[1] = walkingTexture[0];
	walkingTexture[2] = walkingTexture[0];
	walkingTexture[3] = Grapher::loadTexture("imagenes/caminando2.png");
	walkingTexture[4] = walkingTexture[3];
	walkingTexture[5] = walkingTexture[3];
	walkingTexture[6] = Grapher::loadTexture("imagenes/caminando3.png");
	walkingTexture[7] = walkingTexture[6];
	walkingTexture[8] = walkingTexture[6];
	walkingTexture[9] = Grapher::loadTexture("imagenes/caminando4.png");
	walkingTexture[10] = walkingTexture[9];
	walkingTexture[11] = walkingTexture[9];


	//Texturas de personaje saltando
	jumpingTexture[0] = Grapher::loadTexture("imagenes/salto1.png");
	jumpingTexture[1] = Grapher::loadTexture("imagenes/salto2.png");
	//Textura Principal esta es la que se carga en el renderer
	renderTexture = idleTexture[0];
	//indices utiles
	pos = 0;
	posCaminando = 0;
	//Direccion por defecto de disparo
	aimingAt = AIM_FRONT;
	//Estado inicial
	state = STATE_STANDING;
	//Posicion inicial del personaje
	pos_x = gameLevel->getPlayerSpawnX();
	pos_y = gameLevel->getPlayerSpawnY();
	//Velocidad inicial del personaje
	speed_x = 0;
	speed_y = 0;
	//Configuracion del tamaño del personaje
	renderRect.x = pos_x;
	renderRect.y = pos_y;
	renderRect.h = 92;
	renderRect.w = 123;
	//Disparo
	lastShotTime = 0;
	/* En milisegundos. Esto podria modelarse dentro de una arma,
	como una caracteristica de la misma, si pidiesen distintas armas.*/
	shotCooldown = 200;
}

Personaje::~Personaje() {}

void Personaje::handleEvent(SDL_Event evento)
{
	 switch(evento.key.keysym.sym)
	 {
	 	 case SDLK_SPACE:
	 		 this->jump(-10);
	 		 break;

	 	 case SDLK_LEFT:
	 		 this->moveX(-7);
	 		 break;

	 	 case SDLK_RIGHT:
	 		 this->moveX(7);
	 		 break;

	 	 case SDLK_z:
	 		 this->shoot(300);
	 		 break;

	 	 case SDLK_DOWN:
	 		 renderTexture = aimDownTexture;
	 		 aimingAt = AIM_DOWN;
	 		 break;

	 	 case SDLK_UP:
	 		 renderTexture = aimUpTexture;
	 		 aimingAt = AIM_UP;
	 		 break;

		 case SDLK_LCTRL:
			 if(state != STATE_JUMPING && state != STATE_FALLING)
			 {
				 renderTexture = crouchTexture;
				 state = STATE_CROUCHING;
				 aimingAt = AIM_CROUCHING;
			 }
			 break;

		 default:
			break;
	 }
}

void Personaje::shoot(int distanceToTravel)
{
	//Control del cooldown del disparo

	Uint32 currentShotTime = SDL_GetTicks();

	if((SDL_GetTicks() - lastShotTime) > shotCooldown)
	{
		//Tipos de disparon dependiendo el AIM
		switch(aimingAt)
		{
			case AIM_FRONT:
				synergy->catchFiredBullet(new Bullet(pos_x + 30, pos_y - 10, 10, 0, distanceToTravel));
				break;

			case AIM_UP:
				synergy->catchFiredBullet(new Bullet(pos_x + 30, pos_y - 10, 7, -7, distanceToTravel));
				break;

			case AIM_DOWN:
				synergy->catchFiredBullet(new Bullet(pos_x + 30, pos_y - 10, 7, 7, distanceToTravel));
				break;

			case AIM_CROUCHING:
				synergy->catchFiredBullet(new Bullet(pos_x + 30, pos_y - 25, 10, 0, distanceToTravel));
				break;
		}

		lastShotTime = currentShotTime;
	}
}

void Personaje::update()
{
	// Permito la modificacion de la coordenada X, a menos que el jugador quiera ir hacia la izquierda en el tope izquierdo o quiera ir a la derecha en el tope de la derecha.
	pos_x += speed_x;
	if(pos_x < gameLevel->getCameraPosX() || pos_x > (gameLevel->getMapWidth() - 50))
	{
		pos_x -= speed_x;
	}

	if(this->onPlatform()) // Está sobre una plataforma, puede saltar o detener una caida.
	{
		if(speed_y < 0) // está por saltar
		{
			renderTexture = jumpingTexture[0]; // Aplicamos textura de salto

			pos_y += speed_y;
			speed_y += GRAVITY_SPEED;
		}
		else if(speed_y > 0)
		{
			speed_y = 0; // Entonces frenamos la caida, si hubiese

			if(state == STATE_FALLING) // Seteamos el estado parado
			{
				state = STATE_STANDING;
				aimingAt = AIM_FRONT;
				renderTexture = aimFrontTexture;
			}
		}
	}
	// Ya está ascendiendo en un salto o apretó JUMP en este frame y va a comenzar a ascender
	else if(speed_y < 0)
	{
		renderTexture = jumpingTexture[0]; // Aplicamos textura de salto

		pos_y += speed_y;
		speed_y += GRAVITY_SPEED;
	}
	// Caida libre, sin apoyo en ninguna plataforma
	else if(speed_y > 0)
	{
		state = STATE_FALLING;
		renderTexture = jumpingTexture[1]; // Aplicamos textura de caida

		pos_y += speed_y;
		speed_y += GRAVITY_SPEED;
	}
	// Aplicamos velocidad de gravedad
	else
	{
		state = STATE_FALLING;
		speed_y = GRAVITY_SPEED;
	}

	// SI el jugador llego al techo del mapa
	if(pos_y < 10)
	{
		pos_y += 10; // POr ahora, una forma villera de pararlo
	}
	// Si el jugador llego al piso del mapa, es decir, se cayó
	else if(pos_y >= gameLevel->getCameraPosY() + Grapher::windowHeight)
	{
		//Te caiste, moris
		speed_y = -22; // Rebotin temporario
	}

	speed_x = 0;

}

void Personaje::render()
{
	renderRect.x = pos_x - gameLevel->getCameraPosX(); // Ajuste de offset. Muevo la posicion absoluta global del personaje en el mapa a la relativa a la ventana
	renderRect.y = pos_y - gameLevel->getCameraPosY();

	SDL_RenderCopy(Grapher::gameRenderer, renderTexture, NULL, &renderRect);
}

void Personaje::clean()
{
	SDL_DestroyTexture(renderTexture);
	SDL_DestroyTexture(crouchTexture);
	SDL_DestroyTexture(aimDownTexture);
	SDL_DestroyTexture(aimUpTexture);
	SDL_DestroyTexture(aimFrontTexture);
	SDL_DestroyTexture(jumpingTexture[0]);
	SDL_DestroyTexture(jumpingTexture[1]);

	renderTexture = NULL;
	crouchTexture = NULL;
	aimDownTexture = NULL;
	aimUpTexture = NULL;
	aimFrontTexture = NULL;
	jumpingTexture[0] = NULL;
	jumpingTexture[1] = NULL;

	for(int i=0 ; i < 5 ; i++)
	{
		SDL_DestroyTexture(idleTexture[i]);
		SDL_DestroyTexture(walkingTexture[i]);

		idleTexture[i] = NULL;
		walkingTexture[i] = NULL;
	}
}

void Personaje::jump(int _speed_y)
{
	if(state != STATE_JUMPING && state != STATE_FALLING)
	{
		speed_y += _speed_y;
		state = STATE_JUMPING;
	}
}

void Personaje::moveX(int _speed_x)
{
	speed_x = _speed_x;

	renderTexture = walkingTexture[posCaminando];
	posCaminando++;

	if(posCaminando == 12)
		posCaminando = 0;
}
