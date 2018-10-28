/*
 * Enemy.cpp
 *
 *  Created on: 24 sep. 2018
 *      Author: nacho
 */

#include "Enemy.hh"

Enemy::Enemy(CameraLogic* _cameraLogic, int _type ,int _direction, int pos_x, int pos_y ,ServerMessageHandler* _serverMessageHandler)
{
	serverMessageHandler = _serverMessageHandler;
	cameraLogic = _cameraLogic;
	posX = pos_x;
	posY = pos_y;
	type = _type;
	direction = _direction ;
	timeAtIterationStart= 0;
	falling = true;
	dead = false;
}

Enemy::~Enemy() {}

void Enemy::update(){
	if(falling)	posY += 5;

	// Movimiento por defecto de cada tipo de enemigo
	switch(type){
		case 0:{

			if(direction == 0 )posX += 5 ;
			else posX -= 5 ;

			//serverMessageHandler->sendToAllClients(new MessageServer(ENEMY,LOAD,type,direction));
			timeAtIterationStart++;

			if(timeAtIterationStart > 3)
			{
				serverMessageHandler->sendToAllClients(new MessageServer(ENEMY,LOAD,type,direction));
				timeAtIterationStart =0;
			}

			break;
		}
		case 1:{
			//Otro movimiento
			break;
		}

		default: break ;
	}
}

void Enemy::render(){

	//if( !(cameraLogic->outOfCameraRightLimit(posX - 40) || cameraLogic->outOfCameraLeftLimit(posX) || cameraLogic->outOfCameraHigherLimit(posY ) || cameraLogic->outOfCameraLowerLimit(posY - 10)) )
	//{
		if(!dead) serverMessageHandler->sendToAllClients(new MessageServer(ENEMY,RENDER,type,direction,posX - cameraLogic->getCameraPosX(),posY - cameraLogic->getCameraPosY() ) );
	//}
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
	return getTopLimit() + 87;
}

