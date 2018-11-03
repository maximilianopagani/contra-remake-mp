/*
 * Bullet.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: maximiliano
 */

#include "Bullet.hh"

Bullet::Bullet(CameraLogic* _cameraLogic, int _pos_x, int _pos_y, int _speed_x, int _speed_y, int distanceToTravel, ServerMessageHandler* _serverMessageHandler)
{
	cameraLogic = _cameraLogic;
	serverMessageHandler = _serverMessageHandler;
	pos_x = _pos_x;
	pos_y = _pos_y;
	speed_x = _speed_x;
	speed_y = _speed_y;
	traveled_distance = 0;
	max_travel_distance = distanceToTravel;

	serverMessageHandler->sendToAllClients(new MessageServer(SOUND,LOAD,4,0));

}

Bullet::~Bullet() {}

void Bullet::updatePos()
{
	pos_x += speed_x;
	pos_y += speed_y;
	traveled_distance += sqrt(pow(speed_x,2)+pow(speed_y,2));
}

bool Bullet::outOfLimits()
{
	if((max_travel_distance > 0 && traveled_distance > max_travel_distance) || cameraLogic->outOfCameraLimits(pos_x, pos_y))
		return true;
	else
		return false;
}

void Bullet::render()
{
	serverMessageHandler->sendToAllClients(new MessageServer(BULLET, RENDER, pos_x - cameraLogic->getCameraPosX(), pos_y - cameraLogic->getCameraPosY()));
}

int Bullet::getLeftLimit()
{
	return pos_x;
}

int Bullet::getRightLimit()
{
	return pos_x + 8;
}

int Bullet::getTopLimit()
{
	return pos_y;
}

int Bullet::getBottomLimit()
{
	return pos_y + 8;
}
