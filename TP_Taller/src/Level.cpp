/*
 * Level.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#include "Level.h"

Level::Level(LevelNumber _level)
{
	switch(_level)
	{
		case LEVEL1:
		{
			scrolling = SCROLLING_HORIZONTAL;

			background1 = Grapher::loadTexture("imagenes/ContraLevel1BackgroundRezised8312x600.png");
			//background2 = NULL;
			//background3 = NULL;

			playerSpawnX = 200;
			playerSpawnY = 225;
			break;
		}
		case LEVEL2:
		{
			scrolling = SCROLLING_VERTICAL;

			background1 = Grapher::loadTexture("imagenes/ContraLevel3BackgroundRezised800x6797.png");
			//background2 = NULL;
			//background3 = NULL;

			playerSpawnX = 200;
			playerSpawnY = 6600;
			break;
		}
		case LEVEL3:
		{
			scrolling = SCROLLING_HORIZONTAL;

			background1 = Grapher::loadTexture("imagenes/ContraLevel5BackgroundRezised12760x600.png");
			//background2 = NULL;
			//background3 = NULL;

			playerSpawnX = 200;
			playerSpawnY = 225;
			break;
		}
	}

	SDL_QueryTexture(background1, NULL, NULL, &mapWidth, &mapHeight);

	if(scrolling == SCROLLING_HORIZONTAL)
	{
		border = (Grapher::windowWidth / 10) * 6; // Margen al 60% del ancho
		renderRect.y = 0;
	}
	else
	{
		border = mapHeight - (Grapher::windowHeight / 10) * 6; // Margen al 60% de la altura
		renderRect.y = mapHeight - Grapher::windowHeight;
	}

	renderRect.x = 0;
	renderRect.h = Grapher::windowHeight;
	renderRect.w = Grapher::windowWidth;
}

Level::~Level() {
	// TODO Auto-generated destructor stub
}

void Level::render()
{
    SDL_RenderCopy(Grapher::gameRenderer, background1, &renderRect, NULL);
}

void Level::clean()
{
	SDL_DestroyTexture(background1);
	//SDL_DestroyTexture(background2);
	//SDL_DestroyTexture(background3);

	background1 = NULL;
	//background2 = NULL;
	//background3 = NULL;

}

void Level::updateCamera(int playerPosX, int playerPosY)
{
	if(scrolling == SCROLLING_HORIZONTAL)
	{
		if((renderRect.x + Grapher::windowWidth) < mapWidth)
		{
			if(playerPosX >= border)
			{
				renderRect.x += (playerPosX - border);
				border = playerPosX;
			}
		}
	}
	else // Vertical
	{
		if(renderRect.y > 0)
		{
			if(playerPosY <= border)
			{
				renderRect.y -= (border - playerPosY);
				border = playerPosY;
			}
		}
	}
}

