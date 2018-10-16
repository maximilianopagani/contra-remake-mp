/*
 * Level.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#include "Level.hh"

Level::Level( CameraLogic* _cameraLogic, int _level,ServerMessageHandler* _serverMessageHandler)
{
	cameraLogic = _cameraLogic;
	//logicToViewTransporter = _logicToViewTransporter;
	serverMessageHandler = _serverMessageHandler;

	switch(_level)
	{
		case LEVEL1:
		{
			scrolling = SCROLLING_HORIZONTAL;

			serverMessageHandler->sendToAllClients(new MessageServer(LEVEL,LOAD,"set1/fondo1.png","1"));
			serverMessageHandler->sendToAllClients(new MessageServer(LEVEL,LOAD,"set1/fondo2.png","2"));
			serverMessageHandler->sendToAllClients(new MessageServer(LEVEL,LOAD,"set1/fondo3.png","3"));

			background1Width = 8000;
			background1Height = 600;

			background2Width = 7950;
			background2Height = 600;

			background3Width = 4608;
			background3Height = 600;

			// Cargo plataformas del XML
			//platformParser = gameParser->getPlataformas();

			playerSpawnX = 150;
			playerSpawnY = 300;

			enemy = new Enemy(cameraLogic, ".images/enemies/contra_boss_level1.png", 7800, 200, 95, 111);

			break;
		}

		case LEVEL2:
		{
			scrolling = SCROLLING_VERTICAL;

			/*logicToViewTransporter->sendToLoad(LEVELVIEW, gameParser->getFondo1Nivel2(), 1);
			logicToViewTransporter->sendToLoad(LEVELVIEW, gameParser->getFondo2Nivel2(), 2);
			logicToViewTransporter->sendToLoad(LEVELVIEW, gameParser->getFondo3Nivel2(), 3);
*/
			background1Width = 800;
			background1Height = 4000;

			background2Width = 800;
			background2Height = 3000;

			background3Width = 800;
			background3Height = 1300;

			// Cargo plataformas del XML
			//platformParser = gameParser->getPlataforms2();

			playerSpawnX = 150;
			playerSpawnY = 3800;

			enemy = new Enemy(cameraLogic, ".images/enemies/contra_boss_level2.png", 150, 0, 253, 103);

			break;
		}

		case LEVEL3:
		{
			scrolling = SCROLLING_HORIZONTAL;

		/*	logicToViewTransporter->sendToLoad(LEVELVIEW, gameParser->getFondo1Nivel3(), 1);
			logicToViewTransporter->sendToLoad(LEVELVIEW, gameParser->getFondo2Nivel3(), 2);
			logicToViewTransporter->sendToLoad(LEVELVIEW, gameParser->getFondo3Nivel3(), 3);
*/
			background1Width = 8000;
			background1Height = 600;

			background2Width = 7200;
			background2Height = 600;

			background3Width = 4800;
			background3Height = 600;

			// Cargo plataformas del XML
			//platformParser = gameParser->getPlataforms3();

			playerSpawnX = 150;
			playerSpawnY = 400;

			enemy = new Enemy(cameraLogic, ".images/enemies/contra_boss_level3.png", 7800, 310, 127, 95);

			break;
		}
	}

	// Creo las plataformas desde lo cargado por el parser
	/*for (platformParserIterator = platformParser.begin(); platformParserIterator != platformParser.end(); platformParserIterator++)
	{
		string platformType = (*platformParserIterator).getTipo();
		int platformXInitial = (*platformParserIterator).getXInicial();
		int platformXFinal = (*platformParserIterator).getXFinal();
		int platformY = (*platformParserIterator).getAltura();

		platforms.push_back(new Platform(cameraLogic, platformType, platformXInitial, platformY, platformXFinal - platformXInitial));
	}*/

	if(scrolling == SCROLLING_HORIZONTAL)
	{
		border = cameraLogic->getCameraWidth() * 0.6; // Margen al 60% del ancho

		background1PosX = 0;
		background1PosY = 0;

		background2PosX = 0;
		background2PosY = 0;

		background3PosX = 0;
		background3PosY = 0;
	}
	else
	{
		border = background1Height - cameraLogic->getCameraHeight() * 0.6; // Margen al 60% de la altura

		background1PosX = 0;
		background1PosY = background1Height - cameraLogic->getCameraHeight();

		background2PosX = 0;
		background2PosY = background2Height - cameraLogic->getCameraHeight();

		background3PosX = 0;
		background3PosY = background3Height - cameraLogic->getCameraHeight();
	}

	cameraLogic->setCameraPosition(background1PosX, background1PosY);
}

Level::~Level()
{
	this->destroy();
}

void Level::render(){

	//----------------------------------------------------------------------
	//Mandar Mensaje para dibujar fondo

	serverMessageHandler->sendToAllClients(new MessageServer(LEVEL,RENDER, background3PosX, background3PosY, 3));
	serverMessageHandler->sendToAllClients(new MessageServer(LEVEL,RENDER, background2PosX, background2PosY, 2));
	serverMessageHandler->sendToAllClients(new MessageServer(LEVEL,RENDER, background1PosX, background1PosY, 1));

	//----------------------------------------------------------------------
	//Mandar Mensaje para dibujar las plataformas

	/*for(platformsIterator = platforms.begin(); platformsIterator != platforms.end();){
		(*platformsIterator)->render();
		++platformsIterator;
	}*/

	//----------------------------------------------------------------------
	//Mandar Mensaje para dibujar al enemigo

	/*enemy->sendToDraw();*/
}

void Level::destroy()
{
	delete enemy;
}

void Level::moveForward(int playerPosX, int playerPosY)
{
	/*if(scrolling == SCROLLING_HORIZONTAL)
	{
		if((background1PosX + cameraLogic->getCameraWidth()) < background1Width)
		{
			if(playerPosX >= border)
			{
				background1PosX += (playerPosX - border);
				background2PosX += (playerPosX - border) * 0.7;
				background3PosX += (playerPosX - border) * 0.3;

				border = playerPosX;

				cameraLogic->setCameraPosX(background1PosX);
			}
		}
	}
	else // Vertical
	{
		if(background1PosY > 0)
		{
			if(playerPosY <= border)
			{
				background1PosY -= (border - playerPosY);
				background2PosY -= (border - playerPosY) * 0.3;
				background3PosY -= (border - playerPosY) * 0.2;

				border = playerPosY;

				cameraLogic->setCameraPosY(background1PosY);
			}
		}
	}*/
}

// Esto solo mueve los fondos y la camara a la posicion inicial del nivel. No borra enemigos ni plataformas ni los crea devuelta.
// Para eso usar destroy y construir nuevamente el mismo nivel o crear un metodo restartComplete, que reinicie los enemigos y aparezcan nuevamente.
void Level::restart()
{
	if(scrolling == SCROLLING_HORIZONTAL)
	{
		border = cameraLogic->getCameraWidth() * 0.6; // Margen al 60% del ancho

		background1PosX = 0;
		background1PosY = 0;

		background2PosX = 0;
		background2PosY = 0;

		background3PosX = 0;
		background3PosY = 0;

		cameraLogic->setCameraPosition(background1PosX, background1PosY);
	}
	else
	{
		border = background1Height - cameraLogic->getCameraHeight() * 0.6; // Margen al 60% de la altura

		background1PosX = 0;
		background1PosY = background1Height - cameraLogic->getCameraHeight();

		background2PosX = 0;
		background2PosY = background2Height - cameraLogic->getCameraHeight();

		background3PosX = 0;
		background3PosY = background3Height - cameraLogic->getCameraHeight();

		cameraLogic->setCameraPosition(background1PosX, background1PosY);
	}
}
