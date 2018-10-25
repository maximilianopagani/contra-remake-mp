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
	posX = pos_x;
	posY = pos_y;

	typeString = _type;

	if(typeString == "GRASS")
		typeCode = TYPE_GRASS;
	else if(typeString == "ROCK")
		typeCode = TYPE_ROCK;
	else if(typeString == "WOOD")
		typeCode = TYPE_WOOD;
	else if(typeString == "ICE")
		typeCode = TYPE_ICE;
	else
		typeCode = TYPE_ERROR;

	// TODO revisar width hardcodeado
	tileHeight = 48;
	tileWidth = 48;

	tileAmount = pixels/tileWidth;
	if (tileAmount * tileWidth < pixels)
		++tileAmount;
}

Platform::~Platform() {}

void Platform::render()
{
	// Chequeo si alguna parte de la plataforma va a verse dentro de la ventana, y si se vé, se la mando al cliente
	if( !(cameraLogic->outOfCameraRightLimit(posX - 40) || cameraLogic->outOfCameraLeftLimit(posX + tileAmount * tileWidth) || cameraLogic->outOfCameraHigherLimit(posY + tileHeight) || cameraLogic->outOfCameraLowerLimit(posY - 10)) )
	{
		serverMessageHandler->sendToAllClients(new MessageServer(PLATFORM, RENDER, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY(), tileAmount, typeCode));
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
