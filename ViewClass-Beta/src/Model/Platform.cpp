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

	tileSprite = new Sprite(gameView, path.c_str(), 0, 0, 0, 0); // Como a esta altura no conozco las dimensiones de la textura, lo hacemos con 0 0 0 0

	int height;

	if (path == "")
	{
		tileWidth = 48;
		height = 48;
	}
	else
	{
		tileWidth = tileSprite->getTextureWidth(); // Una vez cargada la sprite obtengo sus dimensiones
		height = tileSprite->getTextureHeight();
	}

	tileAmount = pixels/tileWidth;
	if (tileAmount * tileWidth < pixels)
		++tileAmount;

	tileSprite->setSourceRectWidthHeight(tileWidth, height); // Con su ancho y alto le digo al sprite ancho y alto de origen y destino
	tileSprite->setDestinationWidthHeight(tileWidth, height);
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
