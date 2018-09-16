/*
 * Platform.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: pola17
 */

#include "Platform.hh"

Platform::Platform(GameView* _gameView, GroundType type, int pos_x, int pos_y)
{
	gameView = _gameView;
	posX = pos_x;
	posY = pos_y;
	this->type = type;
	if (type == GroundType::GRASS){
		sprite = new Sprite(gameView, "", 0, 0, 0, 0);
	}
	else if (type == GroundType::ROCK){
		sprite = new Sprite(gameView, "", 0, 0, 0, 0);
	}
	else if (type == GroundType::WOOD){
		sprite = new Sprite(gameView, "", 0, 0, 0, 0);
	}

}

Platform::~Platform() {}

void Platform::render()
{
	sprite->render(posX - gameView->getCameraPosX(), posY - gameView->getCameraPosY());
}

