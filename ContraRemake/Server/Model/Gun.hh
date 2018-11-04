/*
 * Gun.h
 * Author: lucas
 */

#ifndef MODEL_GUN_HH_
#define MODEL_GUN_HH_

#include "../../Utils/BulletTypeHandler.hh"
#include "../../Utils/AimHandler.hh"
#include "../../Utils/PlayerStateHandler.hh"
#include "Bullet.hh"
#include "CameraLogic.hh"
#include "ServerMessageHandler.hh"
#include <math.h>

class Gun
{
	public:

		Gun(CameraLogic* _cameraLogic, ServerMessageHandler* _serverMessageHandler);
		virtual ~Gun();

		void shoot(int aimingAt, int state, int pos_x, int pos_y);
		void render();
		void update();
		void clear();

		void setType(BulletType type);

		list<Bullet*>* getBullets(){ return &bullets; }

	private:

		CameraLogic* cameraLogic;
		// necesario solo para ser pasado a bullet
		ServerMessageHandler* serverMessageHandler;

		// Manejo de balas
		std::list<Bullet*> bullets;
		std::list<Bullet*>::iterator bulletsIterator;

		// define el comportamiento del arma,la forma de disparar
		BulletType bulletType;
		int distanceToTravel;
		Uint32 shotCooldown;
		Uint32 lastShotTime;

// -----------------------------------------------------------------------------------------

//		int speed_x, speed_y; // Velocidad que avanza en cada coordenada en cada update
//		int max_travel_distance, traveled_distance; // Gestion de la vida de la bala segun su distancia viajada
};

#endif /* MODEL_GUN_HH_ */
