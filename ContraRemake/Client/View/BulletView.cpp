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
	}

	laserSprites[1] = new Sprite(gameView, "../.images/bullet/p1/laserBack.png", 19, 7, 28, 11);
	laserSprites[2] = new Sprite(gameView, "../.images/bullet/p1/laserBackDW.png", 8, 8, 8, 8);
	laserSprites[3] = new Sprite(gameView, "../.images/bullet/p1/laserBackUP.png", 8, 8, 8, 8);
	laserSprites[4] = new Sprite(gameView, "../.images/bullet/p1/laserFront.png", 8, 8, 8, 8);
	laserSprites[5] = new Sprite(gameView, "../.images/bullet/p1/laserFrontDW.png", 8, 8, 8, 8);
	laserSprites[6] = new Sprite(gameView, "../.images/bullet/p1/laserFrontUP.png", 8, 8, 8, 8);

}

BulletView::~BulletView()
{
	this->destroy();
}

void BulletView::renderLaser(int player_id, int pos_x, int pos_y, int direction)
{
	laserSprites[direction]->render(pos_x, pos_y);
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
