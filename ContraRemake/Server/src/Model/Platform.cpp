/*
 * Platform.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: pola17
 */

#include "Platform.hh"


Platform::Platform(CameraLogic* _cameraLogic, std::string _type, int pos_x, int pos_y, int pixels , ServerMessageHandler* _serverMessageHandler)
{
	cameraLogic = _cameraLogic;
	serverMessageHandler = _serverMessageHandler ;
	//logicToViewTransporter = _logicToViewTransporter;
	posX = pos_x;
	posY = pos_y;
	type = _type;

	// TODO revisar width hardcodeado
	tileHeight = 48;
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
	if( !(cameraLogic->outOfCameraRightLimit(posX - 40) || cameraLogic->outOfCameraLeftLimit(posX + tileAmount * tileWidth) || cameraLogic->outOfCameraHigherLimit(posY + tileHeight) || cameraLogic->outOfCameraLowerLimit(posY - 10)) )
	{
		serverMessageHandler->sendToAllClients(new MessageServer(PLATFORM,LOAD,type));
		serverMessageHandler->sendToAllClients(new MessageServer(PLATFORM,RENDER,posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY(), tileAmount));

		//logicToViewTransporter->sendToLoad(PLATFORMVIEW, type); // ver si es mejor en lugar de realizar 2 envios distintos, si enviar uno solo con el tipo en el sendToDraw
	//	logicToViewTransporter->sendToDraw(PLATFORMVIEW, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY(), tileAmount); // le mando xinicial, yinicial y cantidad de tiles
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
