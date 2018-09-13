/*
 * Character.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "Player.h"

Player::Player(GameView* _view) {
	view = _view;
	pos_x =200;
	pos_y =200;
	sprite = new Sprite(view,"imagenes/walking.png",128, 128, 128, 128);
}

Player::~Player() {}

void Player::render(){
	sprite->render(pos_x, pos_y);
}

void Player::update(){
	//TODO
}

void Player::destroy(){
	//TODO liberar memoria de sprite
}
