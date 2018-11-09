/*
 * Level.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#include "Level.hh"

Level::Level(CameraLogic* _cameraLogic, int _level, ServerMessageHandler* _serverMessageHandler, GameParser* _gameParser)
{
	cameraLogic = _cameraLogic;
	gameParser = _gameParser ;
	serverMessageHandler = _serverMessageHandler;

	switch(_level)
	{
		case LEVEL1:
		{
			serverMessageHandler->sendToAllClients(new MessageServer(SOUND,LOAD,0,1));

			scrolling = SCROLLING_HORIZONTAL;

			background1Path = "set1/fondo1.png"; // ESTO DEBERIA LEVANTARLO DEL PARSER O NO?
			background2Path = "set1/fondo2.png";
			background3Path = "set1/fondo3.png";

			serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, LOAD, background1Path, "1"));
			serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, LOAD, background2Path, "2"));
			serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, LOAD, background3Path, "3"));

			background1Width = 8000;
			background1Height = 600;

			background2Width = 7950;
			background2Height = 600;

			background3Width = 4608;
			background3Height = 600;

		    //================================= CARGA DE ENTIDADES DEL NIVEL ============================================

			this->loadPlatforms(gameParser->getPlatforms1());

			this->loadItems(gameParser->getItems1());

			//this->loadEnemies(gameParser->getRunners1(), gameParser->getRiflemans1())

		    //============================================================================================================

			playerSpawnX = 150;
			playerSpawnY = 300;

			playerRespawnX = 100; // Relativo a la ventana, donde van a aparecer cuando caigan
			playerRespawnY = 200;

			break;
		}

		case LEVEL2:
		{
			serverMessageHandler->sendToAllClients(new MessageServer(SOUND,LOAD,0,2));

			scrolling = SCROLLING_VERTICAL;

			background1Path = "set2/fondo1.png"; // ESTO DEBERIA LEVANTARLO DEL PARSER O NO?
			background2Path = "set2/fondo2.png";
			background3Path = "set2/fondo3.png";

			serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, LOAD, background1Path, "1"));
			serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, LOAD, background2Path, "2"));
			serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, LOAD, background3Path, "3"));

			background1Width = 800;
			background1Height = 4000;

			background2Width = 800;
			background2Height = 3000;

			background3Width = 800;
			background3Height = 1300;

			//================================= CARGA DE ENTIDADES DEL NIVEL ============================================

			this->loadPlatforms(gameParser->getPlatforms2());

			this->loadItems(gameParser->getItems2());

			//this->loadEnemies(gameParser->getRunners2(), gameParser->getRiflemans2())

		    //============================================================================================================

			playerSpawnX = 150;
			playerSpawnY = 3800;

			playerRespawnX = 400; // Relativo a la ventana, donde van a aparecer cuando caigan
			playerRespawnY = 350;

			//enemy = new Enemy(cameraLogic, ".images/enemies/contra_boss_level2.png", 150, 0, 253, 103);

			break;
		}

		case LEVEL3:
		{
			serverMessageHandler->sendToAllClients(new MessageServer(SOUND,LOAD,0,3));

			scrolling = SCROLLING_HORIZONTAL;

			background1Path = "set3/fondo1.png"; // ESTO DEBERIA LEVANTARLO DEL PARSER O NO?
			background2Path = "set3/fondo2.png";
			background3Path = "set3/fondo3.png";

			serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, LOAD, background1Path, "1"));
			serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, LOAD, background2Path, "2"));
			serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, LOAD, background3Path, "3"));

			background1Width = 8000;
			background1Height = 600;

			background2Width = 7200;
			background2Height = 600;

			background3Width = 4800;
			background3Height = 600;

			//================================= CARGA DE ENTIDADES DEL NIVEL ============================================

			this->loadPlatforms(gameParser->getPlatforms3());

			this->loadItems(gameParser->getItems3());

			//this->loadEnemies(gameParser->getRunners3(), gameParser->getRiflemans3())

		    //============================================================================================================

			playerSpawnX = 150;
			playerSpawnY = 300;

			playerRespawnX = 100; // Relativo a la ventana, donde van a aparecer cuando caigan
			playerRespawnY = 200;

			//enemy = new Enemy(cameraLogic, ".images/enemies/contra_boss_level3.png", 7800, 310, 127, 95);

			break;
		}
	}

    //========================================= CARGA DE ENEMIGOS ================================================

	this->loadEnemies();

    //============================================================================================================

    //============================== CONFIGURACION DE POSICIONES INICIALES Y BORDE ===============================

	if(scrolling == SCROLLING_HORIZONTAL)
	{
		border = cameraLogic->getCameraWidth() * 0.5; // Margen al 50% del ancho

		background1PosX = 0;
		background1PosY = 0;

		background2PosX = 0;
		background2PosY = 0;

		background3PosX = 0;
		background3PosY = 0;
	}
	else
	{
		border = background1Height - cameraLogic->getCameraHeight() * 0.7; // Margen al 70% de la altura

		background1PosX = 0;
		background1PosY = background1Height - cameraLogic->getCameraHeight();

		background2PosX = 0;
		background2PosY = background2Height - cameraLogic->getCameraHeight();

		background3PosX = 0;
		background3PosY = background3Height - cameraLogic->getCameraHeight();
	}

    //============================================================================================================

	//=============================== CONFIGURACION INICIAL DE LA LOGICA DE CAMARA ===============================

	cameraLogic->enableMovement();
	cameraLogic->setBorder(border);
	cameraLogic->setCameraPosition(background1PosX, background1PosY);

	//============================================================================================================
}

Level::~Level()
{
	this->destroy();
}

void Level::loadPlatforms(std::list<PlataformParser>* platformParser)
{
	std::list<PlataformParser>::iterator platformParserIterator;

	for(platformParserIterator = platformParser->begin(); platformParserIterator != platformParser->end(); platformParserIterator++)
	{
		string platformType = (*platformParserIterator).getTipo();
		int platformXInitial = (*platformParserIterator).getXInicial();
		int platformXFinal = (*platformParserIterator).getXFinal();
		int platformY = (*platformParserIterator).getAltura();

		platforms.push_back(new Platform(cameraLogic, platformType, platformXInitial, platformY, platformXFinal - platformXInitial , serverMessageHandler));
	}
}

void Level::loadItems(std::list<ItemParser>* itemParser)
{
	std::list<ItemParser>::iterator itemParserIterator;

	for(itemParserIterator = itemParser->begin(); itemParserIterator != itemParser->end(); itemParserIterator++)
	{
		string itemType = (*itemParserIterator).getTipo();
		int itemXPos = (*itemParserIterator).getPosX();
		int itemYPos = (*itemParserIterator).getPosY();
		items.push_back(new Item(cameraLogic, itemType, itemXPos, itemYPos, serverMessageHandler));
	}
}

void Level::loadEnemies(int runner_amount, int rifleman_amount)
{
	int platformsAmount = platforms.size();
	int randomPlatformId;

	for(int i = 0; i < rifleman_amount; i++)
	{
		randomPlatformId = rand() % (platformsAmount-1) + 1; // Buscamos una plataforma al azar entre todas las que hay en el nivel, excepto la primera, que se supone es la de spawn
		std::list<Platform*>::iterator it = platforms.begin();
		std::advance(it, randomPlatformId);
		enemies.push_back(new Enemy(cameraLogic, serverMessageHandler, EnemyType::ENEMY_TYPE_RIFLEMAN, (*it)->getXCentre(), (*it)->getPosY() - 87));
	}

	for(int i = 0; i < runner_amount; i++)
	{
		randomPlatformId = rand() % (platformsAmount-1) + 1; // Buscamos una plataforma al azar entre todas las que hay en el nivel, excepto la primera, que se supone es la de spawn
		std::list<Platform*>::iterator it = platforms.begin();
		std::advance(it, randomPlatformId);
		enemies.push_back(new Enemy(cameraLogic, serverMessageHandler, EnemyType::ENEMY_TYPE_RUNNER, (*it)->getXCentre(), (*it)->getPosY() - 87));
	}
}

void Level::render()
{
	//======================================== DIBUJADO DE ESCENARIO =============================================

	serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, RENDER, background3PosX, background3PosY, 3));
	serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, RENDER, background2PosX, background2PosY, 2));
	serverMessageHandler->sendToAllClients(new MessageServer(LEVEL, RENDER, background1PosX, background1PosY, 1));

    //============================================================================================================

	//======================================== DIBUJADO DE PLATAFORMAS ===========================================

	for(platformsIterator = platforms.begin(); platformsIterator != platforms.end(); ++platformsIterator)
	{
		(*platformsIterator)->render();
	}

	//======================================== DIBUJADO DE ITEMS ===========================================

	for(itemsIterator = items.begin(); itemsIterator != items.end(); ++itemsIterator)
	{
		(*itemsIterator)->render();
	}

    //============================================================================================================

	//========================================= DIBUJADO DE ENEMIGOS =============================================

	for(enemiesIterator = enemies.begin(); enemiesIterator != enemies.end(); ++enemiesIterator)
	{
		(*enemiesIterator)->render();
	}

	//============================================================================================================
}
void Level::update()
{
	//====================================== ACTUALIZACION DE ENEMIGOS ===========================================

	for(enemiesIterator = enemies.begin(); enemiesIterator != enemies.end(); ++enemiesIterator)
	{
		(*enemiesIterator)->update();
	}

    //============================================================================================================
}

void Level::deleteEnemy(Enemy* _enemy)
{
	enemies.remove(_enemy);
}

void Level::destroy()
{
	enemies.clear();
	items.clear();
	platforms.clear();
}

void Level::moveForward(int pixels_to_move)
{
	if(scrolling == SCROLLING_HORIZONTAL)
	{
		if((background1PosX + cameraLogic->getCameraWidth()) < background1Width)
		{
			background1PosX += pixels_to_move;
			background2PosX += pixels_to_move * 0.7;
			background3PosX += pixels_to_move * 0.3;

			border += pixels_to_move;

			cameraLogic->incrementBorder(pixels_to_move);
			cameraLogic->setCameraPosX(background1PosX);
		}
		else
		{
			cameraLogic->disableMovement();
		}
	}
	else // Vertical
	{
		if(background1PosY > 0)
		{
			background1PosY -= pixels_to_move;
			background2PosY -= pixels_to_move * 0.3;
			background3PosY -= pixels_to_move * 0.2;

			border -= pixels_to_move;

			cameraLogic->decreaseBorder(pixels_to_move);
			cameraLogic->setCameraPosY(background1PosY);
		}
		else
		{
			cameraLogic->disableMovement();
		}
	}
}

// Esto solo mueve los fondos y la camara a la posicion inicial del nivel. No borra enemigos ni plataformas ni los crea devuelta.
// Para eso usar destroy y construir nuevamente el mismo nivel o crear un metodo restartComplete, que reinicie los enemigos y aparezcan nuevamente.
void Level::restart()
{
	if(scrolling == SCROLLING_HORIZONTAL)
	{
		border = cameraLogic->getCameraWidth() * 0.5; // Margen al 50% del ancho

		background1PosX = 0;
		background1PosY = 0;

		background2PosX = 0;
		background2PosY = 0;

		background3PosX = 0;
		background3PosY = 0;
	}
	else
	{
		border = background1Height - cameraLogic->getCameraHeight() * 0.7; // Margen al 70% de la altura

		background1PosX = 0;
		background1PosY = background1Height - cameraLogic->getCameraHeight();

		background2PosX = 0;
		background2PosY = background2Height - cameraLogic->getCameraHeight();

		background3PosX = 0;
		background3PosY = background3Height - cameraLogic->getCameraHeight();
	}

	//=============================== CONFIGURACION INICIAL DE LA LOGICA DE CAMARA ===============================

	cameraLogic->enableMovement();
	cameraLogic->setBorder(border);
	cameraLogic->setCameraPosition(background1PosX, background1PosY);

	//============================================================================================================
}
