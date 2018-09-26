/*
 * Platform.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: pola17
 */

#include "Platform.hh"


Platform::Platform(GameView* _gameView, string _type, int pos_x, int pos_y, int pixels)
{
	gameView = _gameView;
	posX = pos_x;
	posY = pos_y;
	type = _type;

	std::string path = "";

	if (type == "GRASS")
		path = ".images/platforms/grass1_48x48.png";
	else if (type == "ROCK")
		path = ".images/platforms/rock1_48x48.png";
	else if (type == "WOOD")
		path = ".images/platforms/wood2_48x48.png";
	else if (type == "ICE")
		path = ".images/platforms/ice1_48x48.png";

	int width, height;

	if (path == "")
	{
		width = 48;
		height = 48;
	} else {
		// se obtienen las dimensiones
		gameView->queryTexture(path.c_str(),&width,&height);
	}

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
	for(partsIterator = parts.begin(); partsIterator != parts.end(); ++partsIterator)
	{
		(*partsIterator)->render(posicionX - gameView->getCameraPosX(), posY - gameView->getCameraPosY());
		posicionX = posicionX + ((Sprite*)(*partsIterator))->getDestinationWidth();
	}
}

int Platform::getLeftLimit()
{
	return posX;
}

int Platform::getRightLimit()
{
	int w = 0;
	for(partsIterator = parts.begin(); partsIterator != parts.end(); ++partsIterator)
	{
		w = w + ((Sprite*)(*partsIterator))->getDestinationWidth();
	}
	return w + getLeftLimit();
}

int Platform::getTopLimit()
{
	return posY;
}

int Platform::getBottomLimit()
{
	return getTopLimit() + 10;
}
