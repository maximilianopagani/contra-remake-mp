/*
 * Enemy.cpp
 *
 *  Created on: 24 sep. 2018
 *      Author: nacho
 */

#include "Enemy.hh"
#include <math.h>

Enemy::Enemy(CameraLogic* _cameraLogic, ServerMessageHandler* _serverMessageHandler, EnemyType _type, int pos_x, int pos_y)
{
	serverMessageHandler = _serverMessageHandler;
	cameraLogic = _cameraLogic;
	posX = pos_x;
	posY = pos_y;
	type = _type;
	timeAtIterationStart = 0;
	falling = false;
	dead = false;

	// Default states por enemigo
	switch(_type)
	{
		case EnemyType::ENEMY_TYPE_RUNNER:
		{
			state = EnemyRunnerStates::RUNNER_STATE_RUNNING_LEFT;
			break;
		}
		case EnemyType::ENEMY_TYPE_RIFLEMAN:
		{
			state = EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_FRONT;
			break;
		}
		default:
			break;
	}

	changeDirectionTime = 0;

	isTargetingPlayer = false;
	targetingPlayerId = 0;
	targetX = 0;
	targetY = 0;
	targetTime = 90; // frames que va a durar el target time

	//Manejo de balas
	lastShotTime = 0;
	shotCooldown = 1000;
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

		changeDirectionTime--;

		switch(type)
		{
			case EnemyType::ENEMY_TYPE_RUNNER:
			{
				if(isTargetingPlayer)
				{
					if(changeDirectionTime <= 0)
					{
						changeDirectionTime = 80;

						if(posX > targetX - 130)
							state = EnemyRunnerStates::RUNNER_STATE_RUNNING_LEFT;
						else if(posX < targetX + 130)
							state = EnemyRunnerStates::RUNNER_STATE_RUNNING_RIGHT;
					}

					if(state == EnemyRunnerStates::RUNNER_STATE_RUNNING_LEFT)
						posX -= 5;
					else if(EnemyRunnerStates::RUNNER_STATE_RUNNING_RIGHT)
						posX += 5;

					timeAtIterationStart++;

					if(timeAtIterationStart > 3)
					{
						serverMessageHandler->sendToAllClients(new MessageServer(ENEMY, LOAD, type, state, animation));

						animation++;

						if(animation > 5) // para avisarle cual foto de la animacion de walk dibujar
							animation = 0;

						timeAtIterationStart = 0;
					}
				}
				break;
			}

			case EnemyType::ENEMY_TYPE_RIFLEMAN:
			{
				if(isTargetingPlayer)
				{
					Uint32 currentShotTime = Utils::getTicks();

					if((currentShotTime - lastShotTime) > shotCooldown)
					{
						int velocity_x, velocity_y, bullet_offset_x, bullet_offset_y;

						float angle = atan2(targetX - posX, targetY - posY) * 180 / 3.14159265;

						// no se me ocurrio otra, si hay alguna mas facil avisen y/o cambienlo

						if(angle >= -180 && angle < -112.5) { velocity_x = -7; velocity_y = -7; bullet_offset_x = 0; bullet_offset_y = 0; state = EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_UP; }
						else if(angle >= -112.5 && angle < -67.5) { velocity_x = -10; velocity_y = 0; bullet_offset_x = 0; bullet_offset_y = 22; state = EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_FRONT; }
						else if(angle >= -67.5 && angle < 0) { velocity_x = -7; velocity_y = 7; bullet_offset_x = 0; bullet_offset_y = 56; state = EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_DOWN; }
						else if(angle >= 0 && angle < 67.5) { velocity_x = 7; velocity_y = 7; bullet_offset_x = 51; bullet_offset_y = 56; state = EnemyRiflemanStates::RIFLEMAN_STATE_RIGHT_DOWN; }
						else if(angle >= 67.5 && angle < 112.5) { velocity_x = 10; velocity_y = 0; bullet_offset_x = 56; bullet_offset_y = 22; state = EnemyRiflemanStates::RIFLEMAN_STATE_RIGHT_FRONT; }
						else if(angle >= 112.5 && angle < 180) { velocity_x = 7; velocity_y = -7; bullet_offset_x = 37; bullet_offset_y = 0; state = EnemyRiflemanStates::RIFLEMAN_STATE_RIGHT_UP; }


						bullets.push_back(new Bullet(cameraLogic, posX + bullet_offset_x, posY + bullet_offset_y, velocity_x, velocity_y, distanceToTravel, true, serverMessageHandler));
						lastShotTime = currentShotTime;
						shotCooldown = 1000 + rand() % 1500; // Cierta incertudimbre sobre cuan seguido dispara, para que no sea tan predecible
						serverMessageHandler->sendToAllClients(new MessageServer(SOUND, LOAD, 4, 2));
					}
				}
				break;
			}

			default:
				break;
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
		serverMessageHandler->sendToAllClients(new MessageServer(ENEMY, RENDER, type, state, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY()));
	}

	for(bulletsIterator = bullets.begin(); bulletsIterator != bullets.end(); ++bulletsIterator)
	{
		(*bulletsIterator)->render(2, RIFLE);
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

