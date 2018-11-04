/*
 * Enemy.cpp
 *
 *  Created on: 24 sep. 2018
 *      Author: nacho
 */

#include "Enemy.hh"

Enemy::Enemy(CameraLogic* _cameraLogic, ENEMY_TYPE _type , int _direction, int pos_x, int pos_y, ServerMessageHandler* _serverMessageHandler)
{
	serverMessageHandler = _serverMessageHandler;
	cameraLogic = _cameraLogic;
	posX = pos_x;
	posY = pos_y;
	type = _type;
	direction = _direction ;
	timeAtIterationStart= 0;
	falling = false;
	dead = false;
}

Enemy::~Enemy() {}

void Enemy::update()
{
	if(falling)
		posY += 5;

	switch(type)
	{
		case TYPE_MOVING_ENEMY:
		{
			if(direction == 0)
				posX += 5 ;
			else
				posX -= 5 ;

			//serverMessageHandler->sendToAllClients(new MessageServer(ENEMY,LOAD,type,direction));
			timeAtIterationStart++;

			if(timeAtIterationStart > 3)
			{
				serverMessageHandler->sendToAllClients(new MessageServer(ENEMY, LOAD, type, direction));
				timeAtIterationStart = 0;
			}
			break;
		}

		case TYPE_STANDING_ENEMY:
		{
			//Otro movimiento
			break;
		}
		default:
			break ;
	}
}

void Enemy::render()
{
	if(!dead)
	{
		serverMessageHandler->sendToAllClients(new MessageServer(ENEMY, RENDER, type, direction, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY()));
	}
}

int Enemy::getLeftLimit()
{
	return posX + 15 ;
}

int Enemy::getRightLimit()
{
	return (posX + 44 - 15);
}

int Enemy::getTopLimit()
{
	return posY;
}

int Enemy::getBottomLimit()
{
	return posY + 87;
}

