/*
 * Character.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "Player.h"

Player::Player(GameView* _view) {
	gameView = _view;
	pos_x =200;
	pos_y =225;
	maxDistanceJump=150;

	state = STATE_STADING;

	animations[STATE_WALKINGRIGHT] = new Sprite(gameView,"image/walkingRight.png",128, 128, 64, 64);
	animations[STATE_WALKINGlEFT] = new Sprite(gameView,"image/walkingLeft.png",128, 128,64, 64);
	animations[STATE_STADING] = new Sprite(gameView,"image/stading.png",512, 384,64, 64);
	animations[STATE_JUMPINGUP] = new Sprite(gameView,"image/jumpUp.png",512, 384, 64, 64);
	animations[STATE_JUMPINGDOWN] = new Sprite(gameView,"image/jumpDown.png",512, 384,64, 64);
	animations[STATE_POINTUP] = new Sprite(gameView,"image/pointUp.png",512, 384,64, 64);
	animations[STATE_POINTFRONT] = new Sprite(gameView,"image/pointFront.png",512, 384,64, 64);
	animations[STATE_POINTDOWN] = new Sprite(gameView,"image/pointDown.png",512, 384, 64, 64);
	animations[STATE_POINTBODYTOGROUND] = new Sprite(gameView,"image/bodyToGround.png",512, 384,64, 64);

	aimingAt = AIM_FRONT;

	bulletSprite = new Sprite(gameView,"imagenes/CharacterSprites.png",8,8,8,8);
	bulletSprite->setSourcePostion(104,8);

}

Player::~Player() {}

void Player::render()
{
	animations[state]->render(pos_x, pos_y);

    // Renderizado de balas
	for(bulletsIterator = bullets.begin(); bulletsIterator != bullets.end();)
	{
		(*bulletsIterator)->render();
		++bulletsIterator;
	}
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

	// Actualizacion de posicion de balas
	for(bulletsIterator = bullets.begin(); bulletsIterator != bullets.end();)
	{
	    (*bulletsIterator)->fly();

	    if((*bulletsIterator)->outOfLimits())
	    {
	        delete (*bulletsIterator);
	        bullets.erase(bulletsIterator++);
	    }
	    else
	    {
	        ++bulletsIterator;
	    }
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
		aimingAt = AIM_BACK;
	}
}
void Player::walkRight(){

	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN ){
		state = STATE_WALKINGRIGHT;
		animations[state]->update();
		pos_x += 5 ;
		aimingAt = AIM_FRONT;
	}
}
void Player::pointUP(){
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN){
		state = STATE_POINTUP;
		aimingAt = AIM_UP;
	}
}
void Player::pointDown(){
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN){
		state = STATE_POINTDOWN;
		aimingAt = AIM_DOWN;
	}
}
void Player::bodyToGround(){
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN){
		state = STATE_POINTBODYTOGROUND;
		aimingAt = AIM_BODYTOGROUND;
	}
}

void Player::shoot()
{
	Uint32 currentShotTime = gameView->getTricks();
	int distanceToTravel = 200;

	if((gameView->getTricks() - lastShotTime) > shotCooldown)
	{
		switch(aimingAt)
		{
			case AIM_FRONT:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x+50, pos_y+25, 10, 0, distanceToTravel));
				break;

			case AIM_BACK:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x-7, pos_y+25, -10, 0, distanceToTravel));
				break;

			case AIM_UP:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x+50, pos_y, 7, -7, distanceToTravel));
				break;

			case AIM_DOWN:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x+50, pos_y+25, 7, 7, distanceToTravel));
				break;

			case AIM_BODYTOGROUND:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x+60, pos_y+50, 10, 0, distanceToTravel));
				break;

		}

		lastShotTime = currentShotTime;
	}
}

void Player::destroy()
{
	for(int i = 0 ; i < MAX_ANIMATIONS ; i ++){
		animations[i]->destroy();
	}
}
