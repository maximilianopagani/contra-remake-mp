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
		sprites[i] = new Sprite(gameView, "../.images/bullet/p" + std::to_string(i+1) + "/bullet.png", 8, 8, 8, 8);

}

BulletView::~BulletView()
{
	this->destroy();
}

void BulletView::render(int player_id, int pos_x, int pos_y)
{
	sprites[player_id]->render(pos_x, pos_y);
}

void BulletView::destroy()
{
	for(int player = 0; player < 4; player++)
		sprites[player]->destroy();
}
