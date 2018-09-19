/*
 * Level.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#include "Level.hh"

Level::Level(GameParser* gameParser, GameView* _gameView, LevelNumber _level)
{
	this->gameView = _gameView;

	switch(_level)
	{
		case LEVEL1:
		{
			scrolling = SCROLLING_HORIZONTAL;

			//parallax = new Parallax(gameView, gameParser->getFondo2Nivel1(), gameParser->getFondo3Nivel1(), _level);
			//sprite = new Sprite(gameView, gameParser->getFondo1Nivel1(), 800, 600, 800, 600);

			background1Sprite = new Sprite(gameView, gameParser->getFondo1Nivel1(), 800, 600, 800, 600);
			background2Sprite = new Sprite(gameView, gameParser->getFondo2Nivel1(), 800, 600, 800, 600);
			background3Sprite = new Sprite(gameView, gameParser->getFondo3Nivel1(), 800, 600, 800, 600);

			//se crean las plataformas, ej:
			platformParser = gameParser->getPlataformas();
			for (platformParserIterator = platformParser.begin(); platformParserIterator != platformParser.end(); platformParserIterator++){
				string platformType = (*platformParserIterator).getTipo();
				int platformXInitial = (*platformParserIterator).getXInicial();
				int platformXFinal = (*platformParserIterator).getXFinal();
				int platformHeight = (*platformParserIterator).getAltura();
				platforms.push_back(new Platform(gameView, platformType, platformXInitial, platformHeight, platformXFinal - platformXInitial));
			}

			playerSpawnX = 200;
			playerSpawnY = 400;

			break;
		}
		case LEVEL2:
		{
			scrolling = SCROLLING_VERTICAL;

			//parallax = new Parallax(gameView, gameParser->getFondo2Nivel2(), gameParser->getFondo3Nivel2(), _level);
			//sprite = new Sprite(gameView, gameParser->getFondo1Nivel2(), 800, 600, 800, 600);

			background1Sprite = new Sprite(gameView, gameParser->getFondo1Nivel2(), 800, 600, 800, 600);
			background2Sprite = new Sprite(gameView, gameParser->getFondo2Nivel2(), 800, 600, 800, 600);
			background3Sprite = new Sprite(gameView, gameParser->getFondo3Nivel2(), 800, 600, 800, 600);

			playerSpawnX = 200;
			playerSpawnY = 3850;

			break;
		}
		case LEVEL3:
		{
			scrolling = SCROLLING_HORIZONTAL;

			//parallax = new Parallax(gameView, gameParser->getFondo2Nivel3(), gameParser->getFondo3Nivel3(), _level);
			//sprite = new Sprite(gameView, gameParser->getFondo1Nivel3(), 800, 600, 800, 600);

			background1Sprite = new Sprite(gameView, gameParser->getFondo1Nivel3(), 800, 600, 800, 600);
			background2Sprite = new Sprite(gameView, gameParser->getFondo2Nivel3(), 800, 600, 800, 600);
			background3Sprite = new Sprite(gameView, gameParser->getFondo3Nivel3(), 800, 600, 800, 600);

			playerSpawnX = 200;
			playerSpawnY = 400;

			break;
		}
	}

	if(scrolling == SCROLLING_HORIZONTAL)
	{
		border = gameView->getWindowWidth() * 0.6; // Margen al 60% del ancho
		background1Sprite->setSourceRectXY(0, 0);
	}
	else
	{
		border = background1Sprite->getTextureHeight() - gameView->getWindowHeight() * 0.6; // Margen al 60% de la altura
		background1Sprite->setSourceRectXY(0, background1Sprite->getTextureHeight() - gameView->getWindowHeight()); // El nivel vertical arranca abajo, con la coordenada 'y' bien grande
		background2Sprite->setSourceRectXY(0, background2Sprite->getTextureHeight() - gameView->getWindowHeight()); // El nivel vertical arranca abajo, con la coordenada 'y' bien grande
		background3Sprite->setSourceRectXY(0, background3Sprite->getTextureHeight() - gameView->getWindowHeight()); // El nivel vertical arranca abajo, con la coordenada 'y' bien grande
	}

	gameView->setCameraPosition(background1Sprite->getSourceRectX(), background1Sprite->getSourceRectY()); // Ubicar la camara en la posicion donde arranca ese nivel
}

Level::~Level()
{
	this->destroy();
}

void Level::render()
{
	//parallax->render();
	//sprite->render(0, 0);

	background3Sprite->render(0, 0);
	background2Sprite->render(0, 0);
	background1Sprite->render(0, 0);

    // Renderizado de plataformas
	for(platformsIterator = platforms.begin(); platformsIterator != platforms.end();)
	{
		(*platformsIterator)->render();
		++platformsIterator;
	}
}

void Level::destroy()
{
	// LOGGER_INFO("Nivel destruido.");
	//sprite->destroy();
	//parallax->~Parallax();

	background3Sprite->destroy();
	background2Sprite->destroy();
	background1Sprite->destroy();
}

void Level::moveForward(int playerPosX, int playerPosY)
{
	if(scrolling == SCROLLING_HORIZONTAL)
	{
		if((background1Sprite->getSourceRectX() + gameView->getWindowWidth()) < background1Sprite->getTextureWidth())
		{
			if(playerPosX >= border)
			{
				background1Sprite->setSourceRectX(background1Sprite->getSourceRectX() + (playerPosX - border));
				background2Sprite->setSourceRectX(background2Sprite->getSourceRectX() + (playerPosX - border) * 0.7);
				background3Sprite->setSourceRectX(background3Sprite->getSourceRectX() + (playerPosX - border) * 0.3);

				border = playerPosX;
				gameView->setCameraPosX(background1Sprite->getSourceRectX()); // Muevo el offset de camara con el cual se va a renderizar todo lo demas

				//parallax->updatePlayerPos(playerPosX, playerPosY, true);
			}
			else {
				//parallax->updatePlayerPos(playerPosX, playerPosY, false);
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
				gameView->setCameraPosY(background1Sprite->getSourceRectY()); // Muevo el offset de camara con el cual se va a renderizar todo lo demas

				//parallax->updatePlayerPos(playerPosX, playerPosY, true);
			}
			else {
				//parallax->updatePlayerPos(playerPosX, playerPosY, false);
			}
		}
	}
}
