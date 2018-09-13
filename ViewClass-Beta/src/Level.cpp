/*
 * Level.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#include "Level.h"
#include "Sprite.h"

Level::Level(GameView* gameView, LevelNumber _level)
{
	this->gameView = gameView;
	posX = 0;
	posY = 0;
	switch(_level)
	{
		case LEVEL1:
		{
			scrolling = SCROLLING_HORIZONTAL;

			sprite = new Sprite(gameView,"image/level1.png",800, 600, 800, 600);
			sprite->manualMod();
			playerSpawnX = 200;
			playerSpawnY = 225;
			break;
		}
		case LEVEL2:
		{
			scrolling = SCROLLING_VERTICAL;

			//background = this->gameView->textureGenerator("imagenes/ContraLevel3BackgroundRezised800x6797.png");
			sprite = new Sprite(gameView,"imagenes/ContraLevel1BackgroundRezised8312x600.png",800, 600, 800, 600);

			playerSpawnX = 200;
			playerSpawnY = 6600;
			break;
		}
		case LEVEL3:
		{
			scrolling = SCROLLING_HORIZONTAL;

			//background = this->gameView->textureGenerator("imagenes/ContraLevel5BackgroundRezised12760x600.png");
			sprite = new Sprite(gameView,"imagenes/ContraLevel1BackgroundRezised8312x600.png",800, 600, 800, 600);

			playerSpawnX = 200;
			playerSpawnY = 225;
			break;
		}
	}

	//TODO pasar esto a gameView
	//gameView->queryTexture(background1, NULL, NULL, &mapWidth, &mapHeight);
//
	if(scrolling == SCROLLING_HORIZONTAL)
	{
		border = this->gameView->getWidth()*0.6; // Margen al 60% del ancho
		//renderRect.y = 0;
	}
//	else
//	{
//		border = mapHeight - (this->gameView->getHeight() / 10) * 6; // Margen al 60% de la altura
//		renderRect.y = mapHeight - this->gameView->getHeight();
//	}
//
//	renderRect.x = 0;
//	renderRect.h = Grapher::windowHeight;
//	renderRect.w = Grapher::windowWidth;
	// rehacer hasta aca
}

Level::~Level() {
	// TODO Auto-generated destructor stub
}

void Level::render()
{
	gameView->setCameraPosition(posX,posY);
	sprite->render(posX,posY);
}

void Level::destroy()
{
	sprite->destroy();
}

void Level::updateCamera(int playerPosX, int playerPosY)
{
	//TODO cambiar posX y posY
	if(scrolling == SCROLLING_HORIZONTAL)
	{
		if((sprite->getRecX() + gameView->getWidth() ) < sprite->getMapWidth())
		{
			if(playerPosX >= border)
			{
				//sprite->getRecX() + (playerPosX - border);
				sprite->setPostion( sprite->getRecX() + (playerPosX - border) , 0);
				border = playerPosX;
			}
		}
	}
	else // Vertical
	{
//		if(renderRect.y > 0)
//		{
//			if(playerPosY <= border)
//			{
//				renderRect.y -= (border - playerPosY);
//				border = playerPosY;
//			}
//		}
	}
}

