/*
 * Bullet.h
 *
 *  Created on: Sep 4, 2018
 *      Author: maximiliano
 */

#ifndef SRC_BULLET_H_
#define SRC_BULLET_H_


#include "GameView.h"
#include "Sprite.h"

class Bullet
{
	public:

		Bullet(GameView* _gameView, Sprite* _sprite, int _pos_x, int _pos_y, int _speed_x, int _speed_y, int distanceToTravel);
		virtual ~Bullet();

		void updatePos();
		bool outOfLimits();
		void render();

	private:

		GameView* gameView;
		Sprite* sprite;

		int pos_x, pos_y; // Posicion absoluta con respecto al mapa gigante.
		int speed_x, speed_y; // Velocidad que avanza en cada coordenada en cada update
		int max_travel_distance, traveled_distance; // Gestion de la vida de la bala segun su distancia viajada
};

#endif /* SRC_BULLET_H_ */
