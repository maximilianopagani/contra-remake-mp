/*
 * EnemyView.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#include "EnemyView.hh"

EnemyView::EnemyView(GameView* _gameView){

	gameView = _gameView;

	sprites[0] = sprites_e1;
	sprites[1] = sprites_e2;

	for(int i = 0; i < MAX_ENEMIES; i++)
	{
		sprites[i][0] = new Sprite(gameView, "../.images/enemies/e1/enemy1Right.png", 16, 32, 42, 84);
		sprites[i][1] = new Sprite(gameView, "../.images/enemies/e1/enemy1Left.png", 16, 32, 42, 84);
	}
}

EnemyView::~EnemyView()
{
	this->destroy();
}

void EnemyView::update(int enemy_type, int state)
{
	sprites[enemy_type][state]->update();
}

void EnemyView::render(int enemy_type, int state, int pos_x, int pos_y)
{
	sprites[enemy_type][state]->render(pos_x, pos_y);
}

void EnemyView::destroy()
{
	for(int x = 0; x < MAX_ENEMIES; x++)
	{
		for(int i = 0 ; i < MAX_ANIMATIONS ; i++)
		{
			if(sprites[x][i])
			{
				sprites[x][i]->destroy();
			}
		}
	}
}
