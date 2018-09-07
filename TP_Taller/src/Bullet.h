/*
 * Bullet.h
 *
 *  Created on: Sep 4, 2018
 *      Author: maximiliano
 */

#ifndef SRC_BULLET_H_
#define SRC_BULLET_H_

#include "Grapher.h"

#include "Level.h"

class Bullet
{
	public:

		Bullet(int _pos_x, int _pos_y, int _speed_x, int _speed_y, int distanceToTravel = 0);

		void move();
		void checkCollision();
		bool outOfLimits();
		bool render();

		static void loadBulletsGraphicsResources();

		virtual ~Bullet();

	private:

		// Personaje* shotBy; // O puede ser un gameActor, no unicamente personaje

		int pos_x, pos_y; // Posicion absoluta con respecto al mapa gigante.

		int speed_x, speed_y; // Velocidad que avanza en cada coordenada en cada update

		int max_travel_distance, traveled_distance; // Gestion de la vida de la bala segun su distancia viajada

		SDL_Rect render_rect; // Rectangulo en el cual voy a renderizarlo. Es distinto a la posicion absoluta, porque en este caso es respecto a la ventana

		static SDL_Rect* source_rect;
		static void setSourceRect();

		static SDL_Texture* source_texture;
		static void setSourceTexture();
};

// STATIC MEMBER DATA POINTERS, HOW TO DELETE??

#endif /* SRC_BULLET_H_ */
