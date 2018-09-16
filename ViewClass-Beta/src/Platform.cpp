/*
 * Platform.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: pola17
 */

#include "Platform.hh"

Platform::Platform(GameView* _gameView, GroundType type, int pos_x, int pos_y, int pixels)
{
	gameView = _gameView;
	posX = pos_x;
	posY = pos_y;
	this->type = type;

	std::string path = ""; //poner default

	switch(type)
	{
		case GroundType::GRASS:
		{
			path = "imagenes/plataformas/blocks.png";
			break;
		}
		case GroundType::ROCK:
		{
			//TODO
			path = "";
			break;
		}
		case GroundType::WOOD:
		{
			path = "imagenes/plataformas/wood log sprite sheet.png";
			break;
		}
		case GroundType::ICE:
		{
			//TODO
			path = "";
			break;
		}
	}

	int width, height;
	// se obtienen las dimensiones
	gameView->queryTexture(path.c_str(),&width,&height);

	int top = pixels/width;
	if (top * width < pixels) ++top;

	for(int j=1; j<=top; j++)
	{
		parts.push_back(new Sprite(gameView, path.c_str(), width, height, width, height));
	}
}

Platform::~Platform() {}

void Platform::render()
{

	int posicionX = posX;
	for(partsIterator = parts.begin(); partsIterator != parts.end();)
	{
		(*partsIterator)->render(posicionX - gameView->getCameraPosX(), posY - gameView->getCameraPosY());
		posicionX = posicionX + (*partsIterator)->getDestinationWidth();
		++partsIterator;
	}

//	sprite->render(posX - gameView->getCameraPosX(), posY - gameView->getCameraPosY());
}

