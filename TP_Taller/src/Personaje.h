/*
 * Personaje.h
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "Headers.h"

class Personaje
{
	public:

		Personaje();

		void update();
		void render();
		void handleEvent(SDL_Event evento);
		void clean();

		void jumping();
		void walking();
		void shoot(int distanceToTravel = 0); // EN un futuro, si se pide, se podria definir aca, segun el arma y ciertas condiciones del personaje, que tipo de bullet crear, que velocidad, duracion, etc
		void setCondition(bool _rebote) { rebote = _rebote; }
		SDL_Rect getPosition() { return desRect; }

		virtual ~Personaje();

	private:

		int pos;
		int posCaminando;
		bool rebote;

		//int speed_x, speed_y;

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

		SDL_Rect srcRect, desRect;
};

#endif /* SRC_PERSONAJE_H_ */
