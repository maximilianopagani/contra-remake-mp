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
				int platformY = (*platformParserIterator).getAltura();
				platforms.push_back(new Platform(gameView, platformType, platformXInitial, platformY, platformXFinal - platformXInitial));
			}

			playerSpawnX = 200;
			playerSpawnY = 400;

			enemy = new Enemy(gameView, "imagenes/enemigos/contra_boss_level1.png", 7800, 200, 95, 111);

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

			platformParser = gameParser->getPlataforms2();
			for (platformParserIterator = platformParser.begin(); platformParserIterator != platformParser.end(); platformParserIterator++){
				string platformType = (*platformParserIterator).getTipo();
				int platformXInitial = (*platformParserIterator).getXInicial();
				int platformXFinal = (*platformParserIterator).getXFinal();
				int platformY = (*platformParserIterator).getAltura();
				platforms.push_back(new Platform(gameView, platformType, platformXInitial, platformY, platformXFinal - platformXInitial));
			}

			playerSpawnX = 200;
			playerSpawnY = 3800;

			enemy = new Enemy(gameView, "imagenes/enemigos/contra_boss_level2.png", 150, 0, 253, 103);

			break;
		}
		case LEVEL3:
		{
			scrolling = SCROLLING_HORIZONTAL;

			background1Sprite = new Sprite(gameView, gameParser->getFondo1Nivel3(), 800, 600, 800, 600);
			background2Sprite = new Sprite(gameView, gameParser->getFondo2Nivel3(), 800, 600, 800, 600);
			background3Sprite = new Sprite(gameView, gameParser->getFondo3Nivel3(), 800, 600, 800, 600);

			platformParser = gameParser->getPlataforms3();
			for (platformParserIterator = platformParser.begin(); platformParserIterator != platformParser.end(); platformParserIterator++){
				string platformType = (*platformParserIterator).getTipo();
				int platformXInitial = (*platformParserIterator).getXInicial();
				int platformXFinal = (*platformParserIterator).getXFinal();
				int platformY = (*platformParserIterator).getAltura();
				platforms.push_back(new Platform(gameView, platformType, platformXInitial, platformY, platformXFinal - platformXInitial));
			}

			playerSpawnX = 200;
			playerSpawnY = 400;

			enemy = new Enemy(gameView, "imagenes/enemigos/contra_boss_level3.png", 7800, 310, 127, 95);

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
		// Si no encuentro el fondo 1 debo hardcodear parámetros
		int bg1TextureHeight = background1Sprite->getTextureHeight();
		if (bg1TextureHeight < 4000) bg1TextureHeight = 4000;

		border = bg1TextureHeight - gameView->getWindowHeight() * 0.6; // Margen al 60% de la altura
		background1Sprite->setSourceRectXY(0, bg1TextureHeight - gameView->getWindowHeight()); // El nivel vertical arranca abajo, con la coordenada 'y' bien grande
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
	background3Sprite->render(0, 0);
	background2Sprite->render(0, 0);
	background1Sprite->render(0, 0);

    // Renderizado de plataformas
	for(platformsIterator = platforms.begin(); platformsIterator != platforms.end();)
	{
		(*platformsIterator)->render();
		++platformsIterator;
	}

	enemy->render();
}

void Level::destroy()
{
	background3Sprite->destroy();
	background2Sprite->destroy();
	background1Sprite->destroy();

	enemy->destroy();
}

void Level::moveForward(int playerPosX, int playerPosY)
{
	if(scrolling == SCROLLING_HORIZONTAL)
	{
		// Si no encuentro el fondo 1 debo hardcodear parámetros
		int bg1TextureWidth = background1Sprite->getTextureWidth();
		if (bg1TextureWidth < 8000) bg1TextureWidth = 8000;

		if((background1Sprite->getSourceRectX() + gameView->getWindowWidth()) < bg1TextureWidth)
		{
			if(playerPosX >= border)
			{
				background1Sprite->setSourceRectX(background1Sprite->getSourceRectX() + (playerPosX - border));
				background2Sprite->setSourceRectX(background2Sprite->getSourceRectX() + (playerPosX - border) * 0.7);
				background3Sprite->setSourceRectX(background3Sprite->getSourceRectX() + (playerPosX - border) * 0.3);

				border = playerPosX;
				gameView->setCameraPosX(background1Sprite->getSourceRectX()); // Muevo el offset de camara con el cual se va a renderizar todo lo demas
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
			}
		}
	}
}

void Level::restart()
{
	//FALTA IMPLEMENTAR PARA QUE REINICIE LOS 3 FONDOS DESPUES DEL SCROLEO
}
