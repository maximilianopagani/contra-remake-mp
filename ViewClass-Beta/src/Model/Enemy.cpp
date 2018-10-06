/*
 * Enemy.cpp
 *
 *  Created on: 24 sep. 2018
 *      Author: nacho
 */

#include "Enemy.hh"

Enemy::Enemy (CameraLogic* _cameraLogic, LogicToViewTransporter* _logicToViewTransporter, string spritePath, int _posX, int _posY, int width, int height)
{
	cameraLogic = _cameraLogic;
	logicToViewTransporter = _logicToViewTransporter;

	posX = _posX;
	posY = _posY;

	logicToViewTransporter->sendToLoad(ENEMYVIEW, spritePath, 0, 0, width, height);
}

Enemy::~Enemy() {}

void Enemy::sendToDraw()
{
	logicToViewTransporter->sendToDraw(ENEMYVIEW, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY());
}

