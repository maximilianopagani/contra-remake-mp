/*
 * Enemy.hh
 *
 *  Created on: 24 sep. 2018
 *      Author: nacho
 */

#ifndef ENEMY_HH_
#define ENEMY_HH_

#include "../../Utils/ICollisional.hh"
#include "../../Utils/MessageServer.hh"
#include "CameraLogic.hh"
#include "../../../Utils/Logger.hh"
#include "ServerMessageHandler.hh"

class Enemy: public ICollisional
{
	public:

		Enemy(CameraLogic* _cameraLogic, int _type,int _state, int pos_x, int pos_y,ServerMessageHandler* _serverMessageHandler);
		virtual ~Enemy();

		int getPosX() { return posX; }
		int getPosY() { return posY; }

		void render();
		void update();
		void fallingStop(){falling = false; }
		void fallingDown(){falling = true;}
		void wasHit(){ dead = true; };//ANIMACION DE MUERTO O DIRECTAMENTE BORRARLO


		//Collisional
		int getLeftLimit();
		int getRightLimit();
		int getTopLimit();
		int getBottomLimit();

	private:

		ServerMessageHandler* serverMessageHandler;
		CameraLogic* cameraLogic ;

		int timeAtIterationStart;
		int posX, posY ,type ,direction;
		bool falling ,dead ;
};

#endif /* ENEMY_HH_ */
