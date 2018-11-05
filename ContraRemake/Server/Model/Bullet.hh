/*
 * Bullet.h
 *
 *  Created on: Sep 4, 2018
 *      Author: maximiliano
 */

#ifndef MODEL_BULLET_HH_
#define MODEL_BULLET_HH_

#include "CameraLogic.hh"
#include <math.h>
#include "ServerMessageHandler.hh"
#include "../../Utils/ICollisional.hh"

class Bullet : public ICollisional
{
	public:

		Bullet(CameraLogic* _cameraLogic, int _pos_x, int _pos_y, int _speed_x, int _speed_y, int distanceToTravel, ServerMessageHandler* _serverMessageHandler);
		virtual ~Bullet();

		void updatePos();
		bool outOfLimits();
		void render(int player_id);

		//Collisional
		int getLeftLimit();
		int getRightLimit();
		int getTopLimit();
		int getBottomLimit();

	private:

		CameraLogic* cameraLogic;
		ServerMessageHandler* serverMessageHandler;

		int pos_x, pos_y; // Posicion absoluta con respecto al mapa gigante.
		int speed_x, speed_y; // Velocidad que avanza en cada coordenada en cada update
		int max_travel_distance, traveled_distance; // Gestion de la vida de la bala segun su distancia viajada
};

#endif /* MODEL_BULLET_HH_ */
