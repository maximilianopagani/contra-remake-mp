/*
 * PlatformView.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: ldea
 */
#include "PlatformView.hh"


PlatformView::PlatformView(GameView* _gameView)
{
	gameView = _gameView;

	// TODO ver el 48 hardcodeado

	sprites[TYPE_GRASS] = new Sprite(gameView, "../.images/platforms/grass1_48x48.png", 48, 48, 48, 48);
	sprites[TYPE_ICE] = new Sprite(gameView, "../.images/platforms/ice1_48x48.png", 48, 48, 48, 48);
	sprites[TYPE_WOOD] = new Sprite(gameView, "../.images/platforms/wood2_48x48.png", 48, 48, 48, 48);
	sprites[TYPE_ROCK] = new Sprite(gameView, "../.images/platforms/rock1_48x48.png", 48, 48, 48, 48);
	sprites[TYPE_ERROR] = new Sprite(gameView, "", 48, 48, 48, 48);
}

PlatformView::~PlatformView()
{
	this->destroy();
}

void PlatformView::render(int pos_x, int pos_y, int tileAmount, int typeCode)
{
	for(int i = 0; i < tileAmount; i++)
	{
		sprites[typeCode]->render(pos_x + i * 48, pos_y);
	}
}

void PlatformView::destroy()
{
	sprites[TYPE_GRASS]->destroy();
	sprites[TYPE_ICE]->destroy();
	sprites[TYPE_WOOD]->destroy();
	sprites[TYPE_ROCK]->destroy();
	sprites[TYPE_ERROR]->destroy();

	sprites[TYPE_GRASS] = NULL;
	sprites[TYPE_ICE] = NULL;
	sprites[TYPE_WOOD] = NULL;
	sprites[TYPE_ROCK] = NULL;
	sprites[TYPE_ERROR] = NULL;
}

