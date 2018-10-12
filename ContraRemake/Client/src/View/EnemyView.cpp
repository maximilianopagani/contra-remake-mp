/*
 * EnemyView.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#include "EnemyView.hh"

EnemyView::EnemyView(GameView* _gameView)
{
	gameView = _gameView;

	for (int i = 0; i < MAX_ANIMATIONS; i++)
	{
		animations[i] = NULL;
	}
}

EnemyView::~EnemyView()
{
	this->destroy();
}

void EnemyView::loadSprite(string spritePath, int width, int height)
{
	this->destroy();

	animations[0] = new Sprite(gameView, spritePath, width, height, width * 2, height * 2);
}

void EnemyView::render(int pos_x, int pos_y)
{
	animations[0]->render(pos_x, pos_y); // El ajuste de desfasaje lo haria el servidor que ya le manda las posiciones a dibujar respecto a la ventana o se debería hacer aca y que el servidor mande el offset a ajustar?
}

void EnemyView::destroy()
{
	for(int i = 0; i < MAX_ANIMATIONS; i++)
	{
		if(animations[i])
		{
			animations[i]->destroy();
			animations[i] = NULL;
		}
	}
}
