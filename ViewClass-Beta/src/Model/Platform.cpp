/*
 * Platform.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: pola17
 */

#include "Platform.hh"


Platform::Platform(CameraLogic* _cameraLogic, LogicToViewTransporter* _logicToViewTransporter, string _type, int pos_x, int pos_y, int pixels)
{
	cameraLogic = _cameraLogic;
	logicToViewTransporter = _logicToViewTransporter;
	posX = pos_x;
	posY = pos_y;
	type = _type;

	// TODO revisar width hardcodeado
	tileWidth = 48;

	tileAmount = pixels/tileWidth;
	if (tileAmount * tileWidth < pixels)
		++tileAmount;
}

Platform::~Platform()
{
	this->destroy();
}

void Platform::destroy()
{
}

void Platform::render()
{
	logicToViewTransporter->sendToLoad(PLATFORMVIEW, type);
	// TODO ver que se envian muchos mensajes para dibujar una sola plataforma
	for(int i = 0; i < tileAmount; i++)
		logicToViewTransporter->sendToDraw(PLATFORMVIEW, posX + i * tileWidth - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY());
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
