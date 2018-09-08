/*
 * Personaje.cpp
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */

#include "Personaje.h"

extern Game* synergy;

#define GRAVITY_SPEED 0.35 // Pixels per iteration

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
		walkingTexture[1] = Grapher::loadTexture("imagenes/caminando2.png");
		walkingTexture[2] = Grapher::loadTexture("imagenes/caminando3.png");
		walkingTexture[3] = Grapher::loadTexture("imagenes/caminando4.png");
		//Texturas de personaje saltando
		jumpingTexture[0] = Grapher::loadTexture("imagenes/salto1.png");
		jumpingTexture[1] = Grapher::loadTexture("imagenes/salto2.png");
		//Textura Principal esta es la que se carga en el renderer
		renderTexture = idleTexture[0];
		//indices utiles
		pos = 0;
		posCaminando = 0;
		distanceJump =120;
		//Direccion por defecto de disparo
		aimingAt = AIM_FRONT;
		//Estado inicial
		state = STATE_STANDING;
		//Posicion inicial del personaje
		pos_x = 200 ;
		pos_y = 225 ;
		//Configuracion del tamaño del personaje
		renderRect.x = pos_x;
		renderRect.y = pos_y;
		renderRect.h = 64;
		renderRect.w = 64 ;
		//Disparo
		lastShotTime = 0;
		/* En milisegundos. Esto podria modelarse dentro de una arma,
		como una caracteristica de la misma, si pidiesen distintas armas.*/
		shotCooldown = 200;
}

Personaje::~Personaje() {}

void Personaje::handleEvent(SDL_Event evento)
{
	 switch(evento.key.keysym.sym) {

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
			this->shoot(800);
			break;

	 case SDLK_DOWN:
			renderTexture = aimDownTexture;
			if(state != STATE_JUMPING && state != STATE_JUMPING_DOWN){
				state = STATE_ALERT ;
				aimingAt = AIM_DOWN;
			}
			break;

	 case SDLK_UP:
			renderTexture = aimUpTexture;
			if(state != STATE_JUMPING && state != STATE_JUMPING_DOWN){
				state = STATE_ALERT ;
				aimingAt = AIM_UP;
			}

			break;

	 case SDLK_LCTRL:
		 	 if(state != STATE_JUMPING && state != STATE_JUMPING_DOWN){
				 renderTexture = crouchTexture;
				 state= STATE_CROUCHING ;
			 }
			 break;

	 default:
			break;
	 }
}

void Personaje::shoot(int distanceToTravel){

	//Despues de caminar o un salto por defecto sea frontal
	if(state == STATE_DEFAULT){
		renderTexture = aimFrontTexture;
		state = STATE_ALERT ;
		aimingAt = AIM_FRONT;
	}
	// Cuando este agachado dispare con la textura de agachado
	if(state ==STATE_CROUCHING){
		state = STATE_ALERT ;
		aimingAt = AIM_CROUCHING;
	}

	Uint32 currentShotTime = SDL_GetTicks();

	//Tipos de disparon dependiento el AIM
	if((SDL_GetTicks() - lastShotTime) > shotCooldown)
	{
		switch(aimingAt)
		{
			case AIM_UP:
				synergy->catchFiredBullet(new Bullet(pos_x+30,pos_y+10, 7, -7, distanceToTravel));
				break;
			case AIM_DOWN:
				synergy->catchFiredBullet(new Bullet(pos_x+30, pos_y+10, 7, 7, distanceToTravel));
				break;
			case AIM_FRONT:
				synergy->catchFiredBullet(new Bullet(pos_x+30, pos_y+10, 10, 0, distanceToTravel));
				break;
			case AIM_CROUCHING:
				synergy->catchFiredBullet(new Bullet(pos_x+30, pos_y+25, 10, 0, distanceToTravel));
				break;
		}

		lastShotTime = currentShotTime;
	}
}

void Personaje::update()
{

	//Establece Lmites
	if(pos_x < level1->getCameraPosX() || pos_x > level1->getMapWidth() - 10)
		pos_x =level1->getCameraPosX();

	//Actualiza animaciones dependiendo del estado actual

	if(state == STATE_WALKING ) {
		renderTexture = walkingTexture[posCaminando];
		posCaminando++;
		if(posCaminando == 4)	posCaminando = 0;
		state =STATE_DEFAULT ;
		aimingAt = AIM_FRONT;
	}
	if(state == STATE_STANDING) {
		renderTexture = idleTexture[pos];
		pos++;
		if(pos == 4) pos = 0;
		aimingAt = AIM_FRONT;
		SDL_Delay(50);
	}
	if(state == STATE_JUMPING) {
		renderTexture = jumpingTexture[0];
		pos_y += -5;
		pos_x += 1;
		distanceJump -= 5;
		if(distanceJump == 0) {
			pos_x += 2;
			state = STATE_JUMPING_DOWN;
		}
		aimingAt = AIM_FRONT;
	}
	if(state == STATE_JUMPING_DOWN) {
		renderTexture = jumpingTexture[1];
		pos_y += 5;
		pos_x += 1;
		distanceJump += 5;
		if(distanceJump == 120) {
			state = STATE_DEFAULT;
			//Ultima parte del salto queda parado
			renderTexture = idleTexture[0];
		}
		aimingAt = AIM_FRONT;
	}

	//Seteo posicion del personaje en la pantalla
	renderRect.x = pos_x - level1->getCameraPosX();
	renderRect.y = pos_y;

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
	//Evita un bug que podia saltar estando saltando parecia q volaba
	if(state != STATE_JUMPING_DOWN) state=STATE_JUMPING;
}

void Personaje::walk(int _pos_x)
{
	pos_x += _pos_x ;
	//Evita caminar mientras esta saltando
	if(state != STATE_JUMPING && state != STATE_JUMPING_DOWN){
		state = STATE_WALKING ;
	}
}
