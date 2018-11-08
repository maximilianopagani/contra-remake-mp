/*
 * Item.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: gmc
 */

#include "Item.hh"

Item::Item(CameraLogic* _cameraLogic, std::string _type, int pos_x, int pos_y, ServerMessageHandler* _serverMessageHandler)
{
	cameraLogic = _cameraLogic;
	serverMessageHandler = _serverMessageHandler ;

	posX = pos_x;
	posY = pos_y;

	typeString = _type;

	if(typeString == "FIREBALLFALCON")
		typeCode = TYPE_FIREBALLFALCON;
	else if(typeString == "FORCEFIELDFALCON")
		typeCode = TYPE_FORCEFIELDFALCON;
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
}

Item::~Item() {}

void Item::render()
{
	if(!cameraLogic->outOfCameraLimits(posX, posY))
	{
		serverMessageHandler->sendToAllClients(new MessageServer(ITEM, RENDER, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY(), typeCode));
	}
}

int Item::getLeftLimit()
{
	return posX;
}

int Item::getRightLimit()
{
	return (posX + ITEMS_WIDTH);
}

int Item::getTopLimit()
{
	return posY;
}

int Item::getBottomLimit()
{
	return (posY + ITEMS_HEIGHT);
}
