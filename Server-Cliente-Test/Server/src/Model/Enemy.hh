/*
 * Enemy.hh
 *
 *  Created on: 24 sep. 2018
 *      Author: nacho
 */

#ifndef ENEMY_HH_
#define ENEMY_HH_

#include "CameraLogic.hh"
#include "LogicToViewTransporter.hh"
#include "../Utils/Logger.hh"

class Enemy
{
	public:

		Enemy(CameraLogic* _cameraLogic, LogicToViewTransporter* _logicToViewTransporter, string spritePath, int _posX, int _posY, int width, int height);
		virtual ~Enemy();

		int getPosX() { return posX; }
		int getPosY() { return posY; }

		void sendToDraw();

	private:

		CameraLogic* cameraLogic;
		LogicToViewTransporter* logicToViewTransporter;

		int posX, posY;
};

#endif /* ENEMY_HH_ */
