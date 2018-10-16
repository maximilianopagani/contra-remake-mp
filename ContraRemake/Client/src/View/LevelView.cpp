/*
 * LevelView.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: ldea
 */
#include "LevelView.hh"

LevelView::LevelView(GameView* _gameView)
{
	gameView = _gameView;

	background1Sprite = NULL;
	background2Sprite = NULL;
	background3Sprite = NULL;
}

void LevelView::loadSprite(string path, int background)
{
	switch(background)
	{
		case 1:
			if(background1Sprite != NULL)
			{
				background1Sprite->destroy();
			}
			background1Sprite = new Sprite(gameView, "../images/background/"+path, 800, 600, 800, 600);
			break;

		case 2:
			if(background2Sprite != NULL)
			{
				background2Sprite->destroy();
			}

			background2Sprite = new Sprite(gameView, "../images/background/"+path, 800, 600, 800, 600);
			break;

		case 3:
			if(background3Sprite != NULL)
			{
				background3Sprite->destroy();
			}

			background3Sprite = new Sprite(gameView, "../images/background/"+path, 800, 600, 800, 600);
			break;
	}
}

void LevelView::render(int pos_x, int pos_y, int background)
{
	switch(background)
	{
		case 1:
			background1Sprite->setSourceRectXY(0, 0);
			background1Sprite->render(0, 0);
			break;
		case 2:
			background2Sprite->setSourceRectXY(pos_x, pos_y);
			background2Sprite->render(0, 0);
			break;
		case 3:
			background3Sprite->setSourceRectXY(pos_x, pos_y);
			background3Sprite->render(0, 0);
			break;
	}
}

void LevelView::destroy()
{
	background1Sprite->destroy();
	background2Sprite->destroy();
	background3Sprite->destroy();

	background1Sprite = NULL;
	background2Sprite = NULL;
	background3Sprite = NULL;
}

LevelView::~LevelView()
{
	this->destroy();
}
