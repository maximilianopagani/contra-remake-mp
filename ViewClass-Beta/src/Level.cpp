/*
 * Level.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#include "Level.hh"

Level::Level(GameView* _gameView, LevelNumber _level)
{
	this->gameView = _gameView;

	switch(_level)
	{
		case LEVEL1:
		{
			scrolling = SCROLLING_HORIZONTAL;

			parallax = new Parallax(gameView, "imagenes/ContraLevel1Mountains.png", "imagenes/ContraLevel1Night.png", _level);
			sprite = new Sprite(gameView, "imagenes/ContraLevel1BackgroundRezised8312x600.png", 800, 600, 800, 600);

			//se crean las plataformas, ej:
			platforms.push_back(new Platform(gameView, Platform::WOOD, 150, 150, 33));
			platforms.push_back(new Platform(gameView, Platform::GRASS, 300, 150, 97));
			platforms.push_back(new Platform(gameView, Platform::GRASS, 300, 200, 96));

			playerSpawnX = 200;
			playerSpawnY = 225;

			break;
		}
		case LEVEL2:
		{
			scrolling = SCROLLING_VERTICAL;

			parallax = new Parallax(gameView, "imagenes/ContraLevel1Mountains.png", "imagenes/ContraLevel1Night.png", _level);
			sprite = new Sprite(gameView, "imagenes/ContraLevel3BackgroundRezised800x6797.png", 800, 600, 800, 600);

			playerSpawnX = 200;
			playerSpawnY = 6600;

			break;
		}
		case LEVEL3:
		{
			scrolling = SCROLLING_HORIZONTAL;

			parallax = new Parallax(gameView, "imagenes/ContraLevel1Mountains.png", "imagenes/ContraLevel1Night.png", _level);
			sprite = new Sprite(gameView, "imagenes/ContraLevel5BackgroundRezised12760x600.png", 800, 600, 800, 600);

			playerSpawnX = 200;
			playerSpawnY = 225;

			break;
		}
	}

	if(scrolling == SCROLLING_HORIZONTAL)
	{
		border = gameView->getWindowWidth() * 0.6; // Margen al 60% del ancho
		sprite->setSourceRectXY(0, 0);
	}
	else
	{
		border = sprite->getTextureHeight() - gameView->getWindowHeight() * 0.6; // Margen al 60% de la altura
		sprite->setSourceRectXY(0, sprite->getTextureHeight() - gameView->getWindowHeight()); // El nivel vertical arranca abajo, con la coordenada 'y' bien grande
	}

	gameView->setCameraPosition(sprite->getSourceRectX(), sprite->getSourceRectY()); // Ubicar la camara en la posicion donde arranca ese nivel
}

Level::~Level()
{
	this->destroy();
}

void Level::render()
{
	parallax->render();
	sprite->render(0, 0);
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
	sprite->destroy();
	parallax->~Parallax();
}

void Level::moveForward(int playerPosX, int playerPosY)
{
	if(scrolling == SCROLLING_HORIZONTAL)
	{
		if((sprite->getSourceRectX() + gameView->getWindowWidth()) < sprite->getTextureWidth())
		{
			if(playerPosX >= border)
			{
				sprite->setSourceRectX(sprite->getSourceRectX() + (playerPosX - border));
				border = playerPosX;
				gameView->setCameraPosX(sprite->getSourceRectX()); // Muevo el offset de camara con el cual se va a renderizar todo lo demas
			}
		}
	}
	else // Vertical
	{
		if(sprite->getSourceRectY() > 0)
		{
			if(playerPosY <= border)
			{
				sprite->setSourceRectY(sprite->getSourceRectY() - (border - playerPosY));
				border = playerPosY;
				gameView->setCameraPosY(sprite->getSourceRectY()); // Muevo el offset de camara con el cual se va a renderizar todo lo demas
			}
		}
	}
	parallax->updatePlayerPos(playerPosX, playerPosY);
}
