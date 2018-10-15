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
	ice = new Sprite(gameView, "Client/.images/platforms/ice1_48x48.png", 48, 48, 48, 48);
	wood = new Sprite(gameView, "Client/.images/platforms/wood2_48x48.png", 48, 48, 48, 48);
	rock = new Sprite(gameView, "Client/.images/platforms/rock1_48x48.png", 48, 48, 48, 48);
	grass = new Sprite(gameView, "Client/.images/platforms/grass1_48x48.png", 48, 48, 48, 48);
	error = new Sprite(gameView, "", 48, 48, 48, 48);
	toRender = NULL;
}

PlatformView::~PlatformView()
{
	this->destroy();
}

void PlatformView::loadSprite(string type)
{
//	this->destroy();
	if (type == "GRASS")
		toRender = grass;
	else if (type == "ROCK")
		toRender = rock;
	else if (type == "WOOD")
		toRender = wood;
	else if (type == "ICE")
		toRender = ice;
	else
		toRender = error;
}

void PlatformView::render(int pos_x, int pos_y, int tileAmount)
{
	for(int i = 0; i < tileAmount; i++)
	{
		toRender->render(pos_x + i * 48, pos_y);
	}
}

void PlatformView::destroy()
{
	ice->destroy();
	wood->destroy();
	rock->destroy();
	grass->destroy();
	error->destroy();
	toRender->destroy();
	ice = NULL;
	wood = NULL;
	rock = NULL;
	grass = NULL;
	error = NULL;
	toRender = NULL;
}

