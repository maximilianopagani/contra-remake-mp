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
	sprite = NULL;
}

PlatformView::~PlatformView()
{
	this->destroy();
}

void PlatformView::loadSprite(string spritePath, int width, int height)
{
//	this->destroy();
	sprite = new Sprite(gameView, spritePath, width, height, width, height);
}


void PlatformView::render(int pos_x, int pos_y)
{
	// El ajuste de desfasaje lo haria el servidor que ya le manda las posiciones a dibujar respecto a la ventana o se debería hacer aca y que el servidor mande el offset a ajustar?
	sprite->render(pos_x, pos_y);
}

void PlatformView::destroy()
{
	sprite->destroy();
	sprite = NULL;
}

