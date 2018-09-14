/*
 * Bullet.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: maximiliano
 */

#include "Bullet.h"

Bullet::Bullet(GameView* _gameView, Sprite* _sprite, int _pos_x, int _pos_y, int _speed_x, int _speed_y, int distanceToTravel)
{
	gameView = _gameView;
	sprite = _sprite;
	pos_x = _pos_x;
	pos_y = _pos_y;
	speed_x = _speed_x;
	speed_y = _speed_y;
	traveled_distance = 0;
	max_travel_distance = distanceToTravel;
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
	if((max_travel_distance > 0 && traveled_distance > max_travel_distance) || gameView->outOfWindow(pos_x, pos_y))
		return true;
	else
		return false;
}

void Bullet::render()
{
	sprite->render(pos_x, pos_y);
}
