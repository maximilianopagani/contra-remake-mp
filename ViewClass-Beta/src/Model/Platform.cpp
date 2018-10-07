/*
 * Platform.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: pola17
 */

#include "Platform.hh"


Platform::Platform(GameView* _gameView, CameraLogic* _cameraLogic, LogicToViewTransporter* _logicToViewTransporter, string _type, int pos_x, int pos_y, int pixels)
{
	gameView = _gameView;
	cameraLogic = _cameraLogic;
	logicToViewTransporter = _logicToViewTransporter;
	posX = pos_x;
	posY = pos_y;
	type = _type;

//	path = "";
//
//	if (type == "GRASS")
//		path = ".images/platforms/grass1_48x48.png";
//	else if (type == "ROCK")
//		path = ".images/platforms/rock1_48x48.png";
//	else if (type == "WOOD")
//		path = ".images/platforms/wood2_48x48.png";
//	else if (type == "ICE")
//		path = ".images/platforms/ice1_48x48.png";


	// el alto y ancho lo podriamos dejar harcodeado en 48, total no va a variar, no se puede poner otro sprite y no vamos a cambiar más de sprite, facilita el tema de crear las texturas en PlatformView

//	tileSprite = new Sprite(gameView, path.c_str(), 0, 0, 0, 0); // Como a esta altura no conozco las dimensiones de la textura, lo hacemos con 0 0 0 0

//	if (path == "")
//	{
		tileWidth = 48;
		height = 48;
//	}
//	else
//	{
//		tileWidth = tileSprite->getTextureWidth(); // Una vez cargada la sprite obtengo sus dimensiones
//		height = tileSprite->getTextureHeight();
//	}

	tileAmount = pixels/tileWidth;
	if (tileAmount * tileWidth < pixels)
		++tileAmount;

//	logicToViewTransporter->sendToLoad(PLATFORMVIEW, path.c_str(), tileWidth, height);
//	tileSprite->setSourceRectWidthHeight(tileWidth, height); // Con su ancho y alto le digo al sprite ancho y alto de origen y destino
//	tileSprite->setDestinationWidthHeight(tileWidth, height);
}

Platform::~Platform()
{
	this->destroy();
}

void Platform::destroy()
{
//	tileSprite->destroy();
}

void Platform::render() // convendria dejar cierto procesamiento en  PlatformView? es decir, mandarle por ejemplo donde está la plataforma x-y + el ancho y el tipo, y con eso el PlatformView la renderizaria en el cleinte haciendo el calculito
{
	// se manda aca por ahora, muchas llamadas a disco, revisar
//	logicToViewTransporter->sendToLoad(PLATFORMVIEW, path.c_str(), tileWidth, height);
	// no se esta usando el width y height
	logicToViewTransporter->sendToLoad(PLATFORMVIEW, type, tileWidth, height);

	for(int i = 0; i < tileAmount; i++)
	{
		logicToViewTransporter->sendToDraw(PLATFORMVIEW, posX + i * tileWidth - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY());
//		tileSprite->render(posX + i * tileWidth - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY());
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
