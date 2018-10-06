/*
 * Level.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#include "Level.hh"

Level::Level(GameParser* gameParser, GameView* _gameView, CameraLogic* _cameraLogic, LogicToViewTransporter* _logicToViewTransporter, LevelNumber _level)
{
	this->gameView = _gameView;
	cameraLogic = _cameraLogic;
	logicToViewTransporter = _logicToViewTransporter;

	switch(_level)
	{
		case LEVEL1:
		{
			scrolling = SCROLLING_HORIZONTAL;

			background1Sprite = new Sprite(gameView, gameParser->getFondo1Nivel1(), 800, 600, 800, 600);
			background2Sprite = new Sprite(gameView, gameParser->getFondo2Nivel1(), 800, 600, 800, 600);
			background3Sprite = new Sprite(gameView, gameParser->getFondo3Nivel1(), 800, 600, 800, 600);

			// Cargo plataformas del XML
			platformParser = gameParser->getPlataformas();

			playerSpawnX = 150;
			playerSpawnY = 300;

			enemy = new Enemy(cameraLogic, logicToViewTransporter, ".images/enemies/contra_boss_level1.png", 7800, 200, 95, 111);

			break;
		}
		case LEVEL2:
		{
			scrolling = SCROLLING_VERTICAL;

			background1Sprite = new Sprite(gameView, gameParser->getFondo1Nivel2(), 800, 600, 800, 600);
			background2Sprite = new Sprite(gameView, gameParser->getFondo2Nivel2(), 800, 600, 800, 600);
			background3Sprite = new Sprite(gameView, gameParser->getFondo3Nivel2(), 800, 600, 800, 600);

			// Cargo plataformas del XML
			platformParser = gameParser->getPlataforms2();

			playerSpawnX = 150;
			playerSpawnY = 3800;

			enemy = new Enemy(cameraLogic, logicToViewTransporter, ".images/enemies/contra_boss_level2.png", 150, 0, 253, 103);

			break;
		}
		case LEVEL3:
		{
			scrolling = SCROLLING_HORIZONTAL;

			background1Sprite = new Sprite(gameView, gameParser->getFondo1Nivel3(), 800, 600, 800, 600);
			background2Sprite = new Sprite(gameView, gameParser->getFondo2Nivel3(), 800, 600, 800, 600);
			background3Sprite = new Sprite(gameView, gameParser->getFondo3Nivel3(), 800, 600, 800, 600);

			// Cargo plataformas del XML
			platformParser = gameParser->getPlataforms3();

			playerSpawnX = 150;
			playerSpawnY = 400;

			enemy = new Enemy(cameraLogic, logicToViewTransporter, ".images/enemies/contra_boss_level3.png", 7800, 310, 127, 95);

			break;
		}
	}

	// Creo las plataformas desde lo cargado por el parser
	for (platformParserIterator = platformParser.begin(); platformParserIterator != platformParser.end(); platformParserIterator++){
		string platformType = (*platformParserIterator).getTipo();
		int platformXInitial = (*platformParserIterator).getXInicial();
		int platformXFinal = (*platformParserIterator).getXFinal();
		int platformY = (*platformParserIterator).getAltura();
		platforms.push_back(new Platform(gameView, cameraLogic, platformType, platformXInitial, platformY, platformXFinal - platformXInitial));
	}

	if(scrolling == SCROLLING_HORIZONTAL)
	{
		border = cameraLogic->getCameraWidth() * 0.6; // Margen al 60% del ancho
		background1Sprite->setSourceRectXY(0, 0);
		background2Sprite->setSourceRectXY(0, 0);
		background3Sprite->setSourceRectXY(0, 0);
	}
	else
	{
		// Si no encuentro el fondo 1 debo hardcodear parámetros
		int bg1TextureHeight = background1Sprite->getTextureHeight();
		if (bg1TextureHeight < 4000) bg1TextureHeight = 4000;

		border = bg1TextureHeight - cameraLogic->getCameraHeight() * 0.6; // Margen al 60% de la altura
		background1Sprite->setSourceRectXY(0, bg1TextureHeight - cameraLogic->getCameraHeight()); // El nivel vertical arranca abajo, con la coordenada 'y' bien grande
		background2Sprite->setSourceRectXY(0, background2Sprite->getTextureHeight() - cameraLogic->getCameraHeight()); // El nivel vertical arranca abajo, con la coordenada 'y' bien grande
		background3Sprite->setSourceRectXY(0, background3Sprite->getTextureHeight() - cameraLogic->getCameraHeight()); // El nivel vertical arranca abajo, con la coordenada 'y' bien grande
	}

	cameraLogic->setCameraPosition(background1Sprite->getSourceRectX(), background1Sprite->getSourceRectY()); // Ubicar la camara en la posicion donde arranca ese nivel
}

Level::~Level()
{
	this->destroy();
}

void Level::render()
{
	background3Sprite->render(0, 0);
	background2Sprite->render(0, 0);
	background1Sprite->render(0, 0);

    // Renderizado de plataformas
	for(platformsIterator = platforms.begin(); platformsIterator != platforms.end();)
	{
		(*platformsIterator)->render();
		++platformsIterator;
	}

	enemy->sendToDraw();
}

void Level::destroy()
{
	background3Sprite->destroy();
	background2Sprite->destroy();
	background1Sprite->destroy();

	delete enemy;
}

void Level::moveForward(int playerPosX, int playerPosY)
{
	if(scrolling == SCROLLING_HORIZONTAL)
	{
		// Si no encuentro el fondo 1 debo hardcodear parámetros
		int bg1TextureWidth = background1Sprite->getTextureWidth();
		if (bg1TextureWidth < 8000) bg1TextureWidth = 8000;

		if((background1Sprite->getSourceRectX() + cameraLogic->getCameraWidth()) < bg1TextureWidth)
		{
			if(playerPosX >= border)
			{
				background1Sprite->setSourceRectX(background1Sprite->getSourceRectX() + (playerPosX - border));
				background2Sprite->setSourceRectX(background2Sprite->getSourceRectX() + (playerPosX - border) * 0.7);
				background3Sprite->setSourceRectX(background3Sprite->getSourceRectX() + (playerPosX - border) * 0.3);

				border = playerPosX;
				cameraLogic->setCameraPosX(background1Sprite->getSourceRectX()); // Muevo el offset de camara con el cual se va a renderizar todo lo demas
			}
		}
	}
	else // Vertical
	{
		if(background1Sprite->getSourceRectY() > 0)
		{
			if(playerPosY <= border)
			{
				background1Sprite->setSourceRectY(background1Sprite->getSourceRectY() - (border - playerPosY));
				background2Sprite->setSourceRectY(background2Sprite->getSourceRectY() - (border - playerPosY) * 0.3);
				background3Sprite->setSourceRectY(background3Sprite->getSourceRectY() - (border - playerPosY) * 0.2);

				border = playerPosY;
				cameraLogic->setCameraPosY(background1Sprite->getSourceRectY()); // Muevo el offset de camara con el cual se va a renderizar todo lo demascameraLogic->getCameraHeight
			}
		}
	}
}

// Esto solo mueve los fondos y la camara a la posicion inicial del nivel. No borra enemigos ni plataformas ni los crea devuelta.
// Para eso usar destroy y construir nuevamente el mismo nivel o crear un metodo restartComplete, que reinicie los enemigos y aparezcan nuevamente.
void Level::restart()
{
	if(scrolling == SCROLLING_HORIZONTAL)
	{
		border = cameraLogic->getCameraWidth() * 0.6; // Margen al 60% del ancho
		background1Sprite->setSourceRectXY(0, 0);
		background2Sprite->setSourceRectXY(0, 0);
		background3Sprite->setSourceRectXY(0, 0);
	}
	else
	{
		// Si no encuentro el fondo 1 debo hardcodear parámetros
		int bg1TextureHeight = background1Sprite->getTextureHeight();
		if (bg1TextureHeight < 4000) bg1TextureHeight = 4000;

		border = bg1TextureHeight - cameraLogic->getCameraHeight() * 0.6; // Margen al 60% de la altura
		background1Sprite->setSourceRectXY(0, bg1TextureHeight - cameraLogic->getCameraHeight()); // El nivel vertical arranca abajo, con la coordenada 'y' bien grande
		background2Sprite->setSourceRectXY(0, background2Sprite->getTextureHeight() - cameraLogic->getCameraHeight()); // El nivel vertical arranca abajo, con la coordenada 'y' bien grande
		background3Sprite->setSourceRectXY(0, background3Sprite->getTextureHeight() - cameraLogic->getCameraHeight()); // El nivel vertical arranca abajo, con la coordenada 'y' bien grande
	}

	cameraLogic->setCameraPosition(background1Sprite->getSourceRectX(), background1Sprite->getSourceRectY()); // Ubicar la camara en la posicion donde arranca ese nivel
}
