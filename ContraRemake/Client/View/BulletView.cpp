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

	for(int i = 0; i < 4; i++)
	{
		sprites[i] = new Sprite(gameView, "../.images/bullet/p" + std::to_string(i+1) + "/bullet.png", 8, 8, 8, 8);
		for(int j = 0; j<6; j++)
		{
			if (j==1 || j==4) //tiro recto
				laserSprites[i][j] = new Sprite(gameView, "../.images/bullet/p" + std::to_string(i+1) + "/laser" + std::to_string(j) + ".png", 19, 7, 28, 11);
			else
				laserSprites[i][j] = new Sprite(gameView, "../.images/bullet/p" + std::to_string(i+1) + "/laser" + std::to_string(j) + ".png", 15, 16, 21, 29);
		}
	}
}

BulletView::~BulletView()
{
	this->destroy();
}

void BulletView::renderLaser(int player_id, int pos_x, int pos_y, int direction)
{
	laserSprites[player_id][direction]->render(pos_x, pos_y);
}

void BulletView::render(int player_id, int pos_x, int pos_y)
{
	sprites[player_id]->render(pos_x, pos_y);
}

void BulletView::destroy()
{
	for(int player = 0; player < 4; player++)
	{
		sprites[player]->destroy();
	}
}
