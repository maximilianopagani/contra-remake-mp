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

		Personaje(std::string texturePath);

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

		// enum CharacterState {STATE_JUMPING, STATE_STANDING, STATE_CROUCHING};
		// CharacterState state;

		int pos;
		int posCaminando;
		bool rebote;
		Uint32 lastShotTime;
		Uint32 shotCooldown;

		std::string spriteNames[4];
		std::string spriteCaminando[4];

		SDL_Texture* personajeTextura;
		SDL_Rect srcRect, desRect;
};

#endif /* SRC_PERSONAJE_H_ */
