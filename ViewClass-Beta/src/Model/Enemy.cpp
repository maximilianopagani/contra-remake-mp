/*
 * Enemy.cpp
 *
 *  Created on: 24 sep. 2018
 *      Author: nacho
 */

#include "Enemy.hh"

Enemy::Enemy (GameView* _view, string spritePath, int _posX, int _posY, int width, int height) {

	gameView = _view;
	posX = _posX;
	posY = _posY;

	animations[0] = new Sprite(gameView, spritePath, width, height, width * 2, height * 2);
}

Enemy::~Enemy() {
	this->destroy();
}

void Enemy::render() {
	animations[0]->render(posX - gameView->getCameraPosX(), posY - gameView->getCameraPosY());
}

void Enemy::update() {

}

void Enemy::destroy() {
	for (int i = 0; i < MAX_ANIMATIONS; i++) {
		if (animations[i]) {
			animations[i]->destroy();
		}
	}
}
