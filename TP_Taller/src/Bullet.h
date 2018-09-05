/*
 * Bullet.h
 *
 *  Created on: Sep 4, 2018
 *      Author: maximiliano
 */

#ifndef SRC_BULLET_H_
#define SRC_BULLET_H_

#include "Grapher.h"

class Bullet
{
	public:

		Bullet(int posx, int posy, int speedx, int speedy, int distanceToTravel = 0);

		void move();
		void checkCollision();
		bool outOfLimits();
		bool render();

		static void loadBulletsGraphicsResources();

		virtual ~Bullet();

	private:

		// Personaje* shotBy; // O puede ser un gameActor, no unicamente personaje

		int speed_x, speed_y, max_travel_distance, traveled_distance;
		SDL_Rect pos_rect;

		static SDL_Rect* source_rect;
		static void setSourceRect();

		static SDL_Texture* source_texture;
		static void setSourceTexture();
};

// STATIC MEMBER DATA POINTERS, HOW TO DELETE??

#endif /* SRC_BULLET_H_ */
