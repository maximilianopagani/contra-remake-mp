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

	isTargetingPlayer = false;
	targetingPlayerId = 0;
	targetX = 0;
	targetY = 0;
	targetTime = 90; // frames que va a durar el target time

	//Manejo de balas
	lastShotTime = 0;
	shotCooldown = 800;
}

Enemy::~Enemy() {}

void Enemy::update()
{
	// Actualizacion de posicion de balas
	for(bulletsIterator = bullets.begin(); bulletsIterator != bullets.end();)
	{
	    (*bulletsIterator)->updatePos();

	    if((*bulletsIterator)->outOfLimits())
	    {
	        delete (*bulletsIterator);
	        bullets.erase(bulletsIterator++);
	    }
	    else
	    {
	        ++bulletsIterator;
	    }
	}

	if(this->isOnScreen())
	{
		if(falling)
			posY += 5;

		targetTime--;
		if(targetTime < 0)
		{
			isTargetingPlayer = false;
		}

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
				if(isTargetingPlayer)
				{
					Uint32 currentShotTime = Utils::getTicks();

					if((currentShotTime - lastShotTime) > shotCooldown)
					{
						int x_dist = targetX - posX;
						int y_dist = targetY - posY;

						int magnitude = sqrt(x_dist * x_dist + y_dist * y_dist);

						int velocity_x = (x_dist * 10) /magnitude;
						int velocity_y = (y_dist * 10) /magnitude;

						bullets.push_back(new Bullet(cameraLogic, posX, posY, velocity_x, velocity_y, distanceToTravel, serverMessageHandler));
						lastShotTime = currentShotTime;
					}
				}
				break;
			}
		}
	}
}

void Enemy::targetPlayer(int playerId, int playerPosX, int playerPosY)
{
	isTargetingPlayer = true;
	targetingPlayerId = playerId;
	targetX = playerPosX;
	targetY = playerPosY;
	targetTime = 90;
}

void Enemy::updateTargetPos(int playerPosX, int playerPosY)
{
	targetX = playerPosX;
	targetY = playerPosY;
}

void Enemy::render()
{
	if(!dead && this->isOnScreen())
	{
		serverMessageHandler->sendToAllClients(new MessageServer(ENEMY, RENDER, type, direction, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY()));
	}

	for(bulletsIterator = bullets.begin(); bulletsIterator != bullets.end(); ++bulletsIterator)
	{
		(*bulletsIterator)->render();
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

