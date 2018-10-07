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
	// Chequeo si alguna parte de la plataforma va a verse dentro de la ventana, y si se vé, se la mando al cliente
	if( !(cameraLogic->outOfCameraRightLimit(posX - 40) || cameraLogic->outOfCameraLeftLimit(posX + tileAmount * tileWidth)) )
	{
		logicToViewTransporter->sendToLoad(PLATFORMVIEW, type); // ver si es mejor en lugar de realizar 2 envios distintos, si enviar uno solo con el tipo en el sendToDraw
		logicToViewTransporter->sendToDraw(PLATFORMVIEW, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY(), tileAmount); // le mando xinicial, yinicial y cantidad de tiles
	}
	// TODO ver que se envian muchos mensajes para dibujar una sola plataforma
	// mandarle al cliente solo las plataformas que va a ver: que outOfCameraRightLimit(xinicial) == false y outOfCameraLeftLimit(xinicial+tileamount*tilewidth) == false, y mandarle tipo, xinicial, yinicial, y tileamount nada mas
	//for(int i = 0; i < tileAmount; i++)
	//	logicToViewTransporter->sendToDraw(PLATFORMVIEW, posX + i * tileWidth - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY());
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
