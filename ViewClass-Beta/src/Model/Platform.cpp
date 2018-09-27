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

	int height;

	if (path == "")
	{
		tileWidth = 48;
		height = 48;
	}
	else
	{
		gameView->queryTexture(path.c_str(), &tileWidth, &height);
	}

	tileAmount = pixels/tileWidth;
	if (tileAmount * tileWidth < pixels)
		++tileAmount;

	tileSprite = new Sprite(gameView, path.c_str(), tileWidth, height, tileWidth, height);
	// primero crear sprite, luego hacerle un query mediante sprite para saber sus dimensiones y luego ajustar el rectangulo source y destination? asi evitamos cargar la textura desde un path
}

Platform::~Platform()
{
	this->destroy();
}

void Platform::destroy()
{
	tileSprite->destroy();
}

void Platform::render()
{
	for(int i = 0; i < tileAmount; i++)
	{
		tileSprite->render(posX + i * tileWidth - gameView->getCameraPosX(), posY - gameView->getCameraPosY());
	}
}

int Platform::getLeftLimit()
{
	return posX;
}

int Platform::getRightLimit()
{
	return (posX + tileAmount * tileWidth);
}

int Platform::getTopLimit()
{
	return posY;
}

int Platform::getBottomLimit()
{
	return (posY + 10);
}
