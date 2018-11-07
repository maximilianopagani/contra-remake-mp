/*
 * Item.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: gmc
 */

#include "Item.hh"

Item::Item(CameraLogic* _cameraLogic, std::string _type, int pos_x, int pos_y, int pixels , ServerMessageHandler* _serverMessageHandler)
{
	cameraLogic = _cameraLogic;
	serverMessageHandler = _serverMessageHandler ;
	posX = pos_x;
	posY = pos_y;

	typeString = _type;

	if(typeString == "FIREBALLFALCON")
		typeCode = TYPE_FIREBALLFALCON;
	else if(typeString == "FIREFIELDFALCON")
		typeCode = TYPE_FIREFIELDFALCON;
	else if(typeString == "LASERFALCON")
		typeCode = TYPE_LASERFALCON;
	else if(typeString == "MACHINEGUNFALCON")
		typeCode = TYPE_MACHINEGUNFALCON;
	else if(typeString == "RAPIDFIREFALCON")
		typeCode = TYPE_RAPIDFIREFALCON;
	else if(typeString == "SPREADGUNFALCON")
		typeCode = TYPE_SPREADGUNFALCON;
	else
		typeCode = TYPE_ERROR;

	// TODO revisar width hardcodeado
	tileHeight = 25;
	tileWidth = 40;

	tileAmount = 1;
//	tileAmount = pixels/tileWidth;
//	if (tileAmount * tileWidth < pixels)
//		++tileAmount;
}

Item::~Item() {}

void Item::render()
{
	// Chequeo si alguna parte del item va a verse dentro de la ventana, y si se vé, se la mando al cliente
	if( !(cameraLogic->outOfCameraRightLimit(posX - 40) || cameraLogic->outOfCameraLeftLimit(posX + tileAmount * tileWidth) || cameraLogic->outOfCameraHigherLimit(posY + tileHeight) || cameraLogic->outOfCameraLowerLimit(posY - 10)) )
	{
		serverMessageHandler->sendToAllClients(new MessageServer(ITEM, RENDER, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY(), tileAmount, typeCode));
	}
}

int Item::getLeftLimit()
{
	return posX;
}

int Item::getRightLimit()
{
	return (posX + tileAmount * tileWidth);
}

int Item::getTopLimit()
{
	return posY;
}

int Item::getBottomLimit()
{
	return (posY + 10);
}
