/*
 * BulletView.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#include "BulletView.hh"

BulletView::BulletView(GameView* _gameView)
{
	gameView = _gameView;
	sprite = new Sprite(gameView, ".images/CharacterSprites.png", 8, 8, 8, 8);
	sprite->setSourceRectXY(104, 8);
}

BulletView::~BulletView()
{
	this->destroy();
}

void BulletView::render(int pos_x, int pos_y)
{
	// El ajuste de desfasaje lo haria el servidor que ya le manda las posiciones a dibujar respecto a la ventana o se debería hacer aca y que el servidor mande el offset a ajustar?
	sprite->render(pos_x, pos_y);
}

void BulletView::destroy()
{
	sprite->destroy();
	sprite = NULL;
}

