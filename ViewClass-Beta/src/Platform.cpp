/*
 * Platform.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: pola17
 */

#include "Platform.hh"


Platform::Platform(GameView* _gameView, GroundType _type, int pos_x, int pos_y, int pixels)
{
	gameView = _gameView;
	posX = pos_x;
	posY = pos_y;
	type = _type;

	std::string path = ""; //TODO poner default

	switch(type)
	{
		case GRASS:
		{
			path = "imagenes/plataformas/blocks.png";
			break;
		}
		case ROCK:
		{
			//TODO
			path = "";
			break;
		}
		case WOOD:
		{
			path = "imagenes/plataformas/wood log sprite sheet.png";
			break;
		}
		case ICE:
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
		posicionX = posicionX + ((Sprite*)(*partsIterator))->getDestinationWidth();
		++partsIterator;
	}
}

