/*
 * Level.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#include "Level.h"

Level::Level(ScrollingType _scrolling)
{
	background1 = Grapher::loadTexture("imagenes/ContraOriginalBackgroundRezised8312x600.png");
	//background2 = NULL;
	//background3 = NULL;

	scrolling = _scrolling;

	if(scrolling == HORIZONTAL)
		border = (Grapher::windowWidth / 10) * 6; // Margen al 60% del ancho
	else
		border = (Grapher::windowHeight / 10) * 6; // Margen al 60% de la altura

	SDL_QueryTexture(background1, NULL, NULL, &mapWidth, &mapHeight);

	renderRect.x = 0;
	renderRect.y = 0;
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
	if(scrolling == HORIZONTAL)
	{
		if((renderRect.x + Grapher::windowWidth) < mapWidth)
		{
			if(playerPosX >= border)
			{
				renderRect.x += (playerPosX - border);
				border += (playerPosX - border);

			}
		}
	}
	else // Vertical
	{
		if((renderRect.y + Grapher::windowHeight) < mapHeight)
		{
			if(playerPosX >= border)
			{
				renderRect.x += (playerPosX - border);
				border += (playerPosX - border);

			}
		}
	}
}

