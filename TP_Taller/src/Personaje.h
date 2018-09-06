/*
 * Personaje.h
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "Headers.h"
#include "Level.h"

extern Level* level1;

class Personaje
{
	public:

		Personaje();

		void update();
		void render();
		void handleEvent(SDL_Event evento);
		void clean();

		void jump();
		void walk(int _speed_x);
		void shoot(int distanceToTravel = 0); // En un futuro, si se pide, se podria definir aca, segun el arma y ciertas condiciones del personaje, que tipo de bullet crear, que velocidad, duracion, etc
		int getPositionX() { return pos_x; }
		int getPositionY() { return pos_y; }
		bool onPlatform() { return (pos_y > 210 && pos_y < 240); }

		virtual ~Personaje();

	private:

		int pos_x, pos_y; // Posicion absoluta con respecto al mapa gigante.

		int pos;
		int posCaminando;

		float speed_x, speed_y;

		enum AimingPosition {AIM_UP, AIM_DOWN, AIM_FRONT};
		AimingPosition aimingAt;

		enum CharacterState {STATE_JUMPING, STATE_STANDING, STATE_WALKING, STATE_CROUCHING};
		CharacterState state;

		Uint32 lastShotTime;
		Uint32 shotCooldown;

		SDL_Texture* renderTexture;
		SDL_Texture* idleTexture[4];
		SDL_Texture* walkingTexture[4];
		SDL_Texture* crouchTexture;
		SDL_Texture* aimDownTexture;
		SDL_Texture* aimUpTexture;
		SDL_Texture* aimFrontTexture;
		SDL_Texture* jumpingTexture[2];

		SDL_Rect srcRect;

		SDL_Rect renderRect;
};

#endif /* SRC_PERSONAJE_H_ */
