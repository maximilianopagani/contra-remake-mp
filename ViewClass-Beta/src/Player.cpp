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
	pos_y =225;
	maxDistanceJump=150;

	state = STATE_STADING;

	animations[STATE_WALKINGRIGHT] = new Sprite(view,"image/walkingRight.png",128, 128, 64, 64);
	animations[STATE_WALKINGlEFT] = new Sprite(view,"image/walkingLeft.png",128, 128,64, 64);
	animations[STATE_STADING] = new Sprite(view,"image/stading.png",512, 384,64, 64);
	animations[STATE_JUMPINGUP] = new Sprite(view,"image/jumpUp.png",512, 384, 64, 64);
	animations[STATE_JUMPINGDOWN] = new Sprite(view,"image/jumpDown.png",512, 384,64, 64);
	animations[STATE_POINTUP] = new Sprite(view,"image/pointUp.png",512, 384,64, 64);
	animations[STATE_POINTFRONT] = new Sprite(view,"image/pointFront.png",512, 384,64, 64);
	animations[STATE_POINTDOWN] = new Sprite(view,"image/pointDown.png",512, 384, 64, 64);
	animations[STATE_POINTBODYTOGROUND] = new Sprite(view,"image/bodyToGround.png",512, 384,64, 64);
}

Player::~Player() {}

void Player::render(){

	animations[state]->render(pos_x, pos_y);
}

void Player::update(){
//ESTA MEDIO MAL PERO PARA PROBAR AHORA LO PONGO
	switch(state) {

		case STATE_JUMPINGUP:
				pos_x+=2;
				pos_y-=5;
				maxDistanceJump-=5;
				if(maxDistanceJump == 0) {
					pos_x += 2;
					state = STATE_JUMPINGDOWN;
				}
				break;
		case STATE_JUMPINGDOWN:
				pos_y += 5;
				pos_x += 1;
				maxDistanceJump += 5;
				if(maxDistanceJump == 150) 	state = STATE_STADING;

				break;
		default:
				break;
	}
}

void Player::jump(){
	state = STATE_JUMPINGUP;
}
void Player::walkLeft(){

	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN ){
		state = STATE_WALKINGlEFT;
		animations[state]->update();
		pos_x -= 5 ;
	}
}
void Player::walkRight(){

	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN ){
		state = STATE_WALKINGRIGHT;
		animations[state]->update();
		pos_x += 5 ;
	}
}
void Player::pointUP(){
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN){
		state = STATE_POINTUP;
	}
}
void Player::pointDown(){
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN){
		state = STATE_POINTDOWN;
	}
}
void Player::bodyToGround(){
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN){
		state = STATE_POINTBODYTOGROUND;
	}
}
void Player::shoot(){

}

void Player::destroy(){
	for(int i = 0 ; i < MAX_ANIMATIONS ; i ++){
		animations[i]->destroy();
	}
}
