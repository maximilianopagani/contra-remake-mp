/*
 * Personaje.cpp
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */

#include "Personaje.h"

extern Game* synergy;

#define GRAVITY_SPEED 0.3 // Pixels per iteration

Personaje::Personaje()
{
	crouchTexture = Grapher::loadTexture("imagenes/disparoagachado.png");
	aimDownTexture = Grapher::loadTexture("imagenes/disparobajo.png");
	aimUpTexture = Grapher::loadTexture("imagenes/disparoalto.png");
	aimFrontTexture = Grapher::loadTexture("imagenes/disparofrontal.png");

	idleTexture[0] = Grapher::loadTexture("imagenes/espera1.png");
	idleTexture[1] = Grapher::loadTexture("imagenes/espera2.png");
	idleTexture[2] = Grapher::loadTexture("imagenes/espera3.png");
	idleTexture[3] = idleTexture[1]; // Repite "imagenes/espera2.png"

	walkingTexture[0] = Grapher::loadTexture("imagenes/caminando1.png");
	walkingTexture[1] = Grapher::loadTexture("imagenes/caminando2.png");
	walkingTexture[2] = Grapher::loadTexture("imagenes/caminando3.png");
	walkingTexture[3] = Grapher::loadTexture("imagenes/caminando4.png");

	jumpingTexture[0] = Grapher::loadTexture("imagenes/salto1.png");
	jumpingTexture[1] = Grapher::loadTexture("imagenes/salto2.png");

	renderTexture = idleTexture[0];

	pos = 0;
	posCaminando = 0;

	speed_x = 0;
	speed_y = 0;

	aimingAt = AIM_FRONT;
	state = STATE_STANDING;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	pos_x = 200 ;
	pos_y = 225 ;

	renderRect.x = pos_x;
	renderRect.y = pos_y;
	renderRect.h = 64;
	renderRect.w = 64 ;

	lastShotTime = 0;
	shotCooldown = 200; // En milisegundos. Esto podria modelarse dentro de una arma, como una caracteristica de la misma, si pidiesen distintas armas.
}

Personaje::~Personaje() {}

void Personaje::handleEvent(SDL_Event evento)
{
	 switch(evento.key.keysym.sym)
	 {
	 	 case SDLK_SPACE:
			this->jump();
			break;

		case SDLK_LEFT:
			this->walk(-7);
			break;

		case SDLK_RIGHT:
			this->walk(7);
			break;

		case SDLK_z:
			this->shoot(); // Ver porque se esta ejecutando cada case 2 veces, hay algo que no esta bien. Las texturas tambien, se cargan 2 veces. Salvo flecha izq y derecha, el resto duplica todos
			break; // EL problema es que faltaba un --else if(evento.type == SDL_KEYDOWN)-- en el PollEvent, ya que llamaba a personaje.eventhandler aún para otros eventos no de teclado

		case SDLK_x:
			this->shoot(250);
			break;

		case SDLK_DOWN:
			if(aimingAt == AIM_FRONT)
			{
				renderTexture = aimDownTexture;
				aimingAt = AIM_DOWN;
			}
			else if(aimingAt == AIM_UP)
			{
				renderTexture = aimFrontTexture;
				aimingAt = AIM_FRONT;
			}
			break;

		case SDLK_UP:
			if(aimingAt == AIM_FRONT)
			{
				renderTexture = aimUpTexture;
				aimingAt = AIM_UP;
			}
			else if(aimingAt == AIM_DOWN)
			{
				renderTexture = aimFrontTexture;
				aimingAt = AIM_FRONT;
			}
			break;

		case SDLK_LCTRL:
			 renderTexture = crouchTexture;
			 break;

		case SDLK_KP_0:
			 renderTexture = aimFrontTexture;
			 aimingAt = AIM_FRONT;
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
		switch(aimingAt)
		{
			case AIM_UP:
				synergy->catchFiredBullet(new Bullet(renderRect.x, renderRect.y, 7, -7, distanceToTravel));
				break;
			case AIM_DOWN:
				synergy->catchFiredBullet(new Bullet(renderRect.x, renderRect.y, 7, 7, distanceToTravel));
				break;
			case AIM_FRONT:
				synergy->catchFiredBullet(new Bullet(renderRect.x, renderRect.y, 10, 0, distanceToTravel));
				break;
		}

		lastShotTime = currentShotTime;
	}
}

void Personaje::update()
{
	/*
	renderTexture = idleTexture[pos];
	pos++;

	if(pos == 4)
		pos = 0;
	*/

	renderRect.x = pos_x - level1->getCameraPos();
	renderRect.y = pos_y;

	pos_x += speed_x;

	// para scroll vertical, si se va debajo del cero muere
	if(pos_x < level1->getCameraPos() || pos_x > level1->getMapWidth() - 10) // Si quiere irse de los limites absolutos del mapa. NO aceptamos desertores =P
		pos_x -= speed_x;

	speed_x = 0;


	if(this->onPlatform()) // Está sobre una plataforma, puede saltar o parar caida
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

			if(state == STATE_JUMPING) // Seteamos el estado parado
			{
				state = STATE_STANDING;
				renderTexture = idleTexture[0];
			}
		}
	}
	else if(speed_y < 0) // esta ascendiendo en un salto o a punto de saltar
	{
		renderTexture = jumpingTexture[0]; // Aplicamos textura de salto

		pos_y += speed_y;
		speed_y += GRAVITY_SPEED;
	}
	else if(speed_y > 0) // Esta cayendo
	{
		renderTexture = jumpingTexture[1]; // Aplicamos textura de caida

		pos_y += speed_y;
		speed_y += GRAVITY_SPEED;
	}
}

void Personaje::render()
{
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

void Personaje::jump()
{
	if(state != STATE_JUMPING)
	{
		speed_y += -8.5;
		state = STATE_JUMPING;
	}

	/*
	for(int i=0 ; i < 15 ; i++)
	{
		pos_y = pos_y - 5;
		SDL_RenderClear(Grapher::gameRenderer);
		this->render();
		SDL_RenderPresent(Grapher::gameRenderer);
		SDL_Delay(15);
	}

	renderTexture = jumpingTexture[1];
	for(int i=0 ; i < 14 ; i++)
	{
		 pos_y = pos_y + 5;
		 SDL_RenderClear(Grapher::gameRenderer);
		 this->render();
	     SDL_RenderPresent(Grapher::gameRenderer);
		 SDL_Delay(15);
	}

	pos_y = pos_y + 5;
	SDL_RenderClear(Grapher::gameRenderer);
	renderTexture = idleTexture[0];
	this->render();
	SDL_RenderPresent(Grapher::gameRenderer);
	SDL_Delay(30);
	*/
}

void Personaje::walk(int _speed_x)
{
	speed_x = _speed_x;

	renderTexture = walkingTexture[posCaminando];
	posCaminando++;

	if(posCaminando == 4)
		posCaminando = 0;
}
