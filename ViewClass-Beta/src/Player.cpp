/*
 * Character.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "Player.hh"

Player::Player(GameView* _view)
{
	gameView = _view;
	pos_x = 200;
	pos_y = 425;
	maxDistanceJump=150;

	state = STATE_STANDING;
	direction = DIRECTION_FRONT;

	animations[STATE_WALKINGRIGHT] = new Sprite(gameView,"image/walkingRight.png",128, 128, 64, 64);
	animations[STATE_WALKINGLEFT] = new Sprite(gameView,"image/walkingLeft.png",128, 128,64, 64);
	animations[STATE_STANDING] = new Sprite(gameView,"image/standing.png",128, 128,64, 64);

	animations[STATE_JUMPINGUP] = new Sprite(gameView,"image/jumping.png",128, 128, 64, 64);
	animations[STATE_JUMPINGDOWN] = new Sprite(gameView,"image/jumping.png",128, 128,64, 64);

	animations[STATE_POINTUP] = new Sprite(gameView,"image/pointUp.png",128, 128,64, 64);
	animations[STATE_POINTFRONT] = new Sprite(gameView,"image/pointFront.png",128, 128,64, 64);
	animations[STATE_POINTBACK] = new Sprite(gameView,"image/pointBack.png",128, 128,64, 64);
	animations[STATE_POINTDOWN] = new Sprite(gameView,"image/pointDown.png",128, 128, 64, 64);
	animations[STATE_POINTBODYTOGROUND] = new Sprite(gameView,"image/bodyToGround.png",128, 128,64, 64);
	animations[STATE_POINTDOWN_BACK] = new Sprite(gameView,"image/pointDownBack.png",128, 128, 64, 64);
	animations[STATE_POINTBODYTOGROUND_BACK] = new Sprite(gameView,"image/bodyToGroundBack.png",128, 128,64, 64);
	animations[STATE_POINTUP_BACK] = new Sprite(gameView,"image/pointUpBack.png",128, 128, 64, 64);


	aimingAt = AIM_FRONT;

	bulletSprite = new Sprite(gameView, "imagenes/CharacterSprites.png", 8, 8, 8, 8);
	bulletSprite->setSourceRectXY(104, 8);

	lastShotTime = 0;
	shotCooldown = 100;
}

Player::~Player()
{
	this->destroy();
}

void Player::render()
{
	//if(!gameView->outOfWindow(pos_x, pos_y)) // EN este caso tampoco haria falta porque el player nunca se deberia mover afuera de la ventana. Se deberia limitar dentro del mov del player
	//{
		animations[state]->render(pos_x - gameView->getCameraPosX(), pos_y - gameView->getCameraPosY());
	//}

    // Renderizado de balas
	for(bulletsIterator = bullets.begin(); bulletsIterator != bullets.end();)
	{
		(*bulletsIterator)->render();
		++bulletsIterator;
	}
}

void Player::handleKeys(const Uint8* _currentKeyStates)
{
	currentKeyStates = _currentKeyStates;

	//Caminar derecho
	if(currentKeyStates[SDL_SCANCODE_RIGHT]&&currentKeyStates[SDL_SCANCODE_Z]&&currentKeyStates[SDL_SCANCODE_UP]) {
		if(!currentKeyStates[SDL_SCANCODE_LCTRL]) this->pointUP(false);
	}
	if(currentKeyStates[SDL_SCANCODE_RIGHT]&&currentKeyStates[SDL_SCANCODE_Z]&&currentKeyStates[SDL_SCANCODE_DOWN]) {
		if(!currentKeyStates[SDL_SCANCODE_LCTRL]) this->pointDown(false);
	}
	if(currentKeyStates[SDL_SCANCODE_RIGHT]&&currentKeyStates[SDL_SCANCODE_Z]) {
		this->shoot();
	}
	if(currentKeyStates[SDL_SCANCODE_RIGHT]) {
		if(!currentKeyStates[SDL_SCANCODE_LCTRL])  this->walkRight();
		this->pointDefault(false);
	}
	//caminar izquierda
	if(currentKeyStates[SDL_SCANCODE_LEFT]&&currentKeyStates[SDL_SCANCODE_Z]&&currentKeyStates[SDL_SCANCODE_UP]) {
		if(!currentKeyStates[SDL_SCANCODE_LCTRL]) this->pointUP(false);
	}
	if(currentKeyStates[SDL_SCANCODE_LEFT]&&currentKeyStates[SDL_SCANCODE_Z]&&currentKeyStates[SDL_SCANCODE_DOWN]) {
		if(!currentKeyStates[SDL_SCANCODE_LCTRL]) this->pointDown(false);
	}
	if(currentKeyStates[SDL_SCANCODE_LEFT]&&currentKeyStates[SDL_SCANCODE_Z]) {
		this->shoot();
	}
	if(currentKeyStates[SDL_SCANCODE_LEFT]) {
		if(!currentKeyStates[SDL_SCANCODE_LCTRL])  this->walkLeft();
		this->pointDefault(false);
	}
	//disparo parado
	if(currentKeyStates[SDL_SCANCODE_Z]&&currentKeyStates[SDL_SCANCODE_UP]){
		if(!currentKeyStates[SDL_SCANCODE_RIGHT]&&!currentKeyStates[SDL_SCANCODE_LEFT]
			&&!currentKeyStates[SDL_SCANCODE_LCTRL]){
			if(state != STATE_JUMPINGDOWN && state !=STATE_JUMPINGUP){
				this->pointUP(true);
			}else this->pointUP(false);
		}
	}
	if(currentKeyStates[SDL_SCANCODE_Z]&&currentKeyStates[SDL_SCANCODE_DOWN]){
		if(!currentKeyStates[SDL_SCANCODE_RIGHT]&&!currentKeyStates[SDL_SCANCODE_LEFT]
			&&!currentKeyStates[SDL_SCANCODE_LCTRL]){
			if(state != STATE_JUMPINGDOWN && state !=STATE_JUMPINGUP){
				this->pointDown(true);
			}else this->pointDown(false);
		}
	}
	//disparos en salto
	if(currentKeyStates[SDL_SCANCODE_Z]){
		this->shoot();
		if(!currentKeyStates[SDL_SCANCODE_UP]&&!currentKeyStates[SDL_SCANCODE_DOWN]
			 &&!currentKeyStates[SDL_SCANCODE_LEFT]&&!currentKeyStates[SDL_SCANCODE_RIGHT]){

			if(state != STATE_JUMPINGDOWN && state !=STATE_JUMPINGUP){
				this->pointDefault(true);
			}else this->pointDefault(false);
		}
	}
	//Salto
	if(currentKeyStates[SDL_SCANCODE_SPACE]){
		this->jump();
	}
	//disparo bajo
	if(currentKeyStates[SDL_SCANCODE_LCTRL]){
			this->bodyToGround();
	}
	if(currentKeyStates[SDL_SCANCODE_A]){
			pos_y-=5;
	}
}

void Player::update(){
	//Salto
	switch(state) {
		case STATE_JUMPINGUP:
				pos_y-=5;
				maxDistanceJump-=5;
				animations[state]->update();
				if(maxDistanceJump == 0) {
					state = STATE_JUMPINGDOWN;
				}
				break;
		case STATE_JUMPINGDOWN:
				pos_y += 5;
				maxDistanceJump += 5;
				animations[state]->update();
				if(maxDistanceJump == 150)  state = STATE_STANDING;
				break;

		default:
				break;
	}
	// Actualizacion de posicion de balas
	for(bulletsIterator = bullets.begin(); bulletsIterator != bullets.end();)
	{
	    (*bulletsIterator)->updatePos();

	    if((*bulletsIterator)->outOfLimits())
	    {
	        delete (*bulletsIterator);
	        bullets.erase(bulletsIterator++);
	    }
	    else {
	        ++bulletsIterator;
	    }
	}
}

void Player::jump(){
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN) state = STATE_JUMPINGUP;
}

void Player::walkLeft(){
	direction = DIRECTION_BACK;
	pos_x-=5;
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN) {
		state = STATE_WALKINGLEFT;
		animations[state]->update();
	}
}

void Player::walkRight(){
	direction = DIRECTION_FRONT;
	pos_x+=5;
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN) {
		state = STATE_WALKINGRIGHT;
		animations[state]->update();
	}
}

void Player::pointUP(bool cond ){
	if(direction == DIRECTION_BACK){
		aimingAt = AIM_UP_BACK;
	}else aimingAt = AIM_UP;

	if(cond){
		if(direction == DIRECTION_BACK){
			state=STATE_POINTUP_BACK;

		}else state=STATE_POINTUP;
	}
}

void Player::pointDown(bool cond){
	if(direction == DIRECTION_BACK){
			aimingAt = AIM_DOWN_BACK;
	}else aimingAt = AIM_DOWN;

	if(cond){
		if(direction == DIRECTION_BACK){
			state=STATE_POINTDOWN_BACK;
		}else state=STATE_POINTDOWN;
	}
}

void Player::pointDefault(bool cond){
	if(direction == DIRECTION_BACK) {
			aimingAt = AIM_BACK;
	}else aimingAt = AIM_FRONT;

	if(cond){
		if(direction == DIRECTION_BACK){
			state=STATE_POINTBACK;
		}else state=STATE_POINTFRONT;
	}
}

void Player::bodyToGround(){
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN){
		if(direction == DIRECTION_BACK) {
			aimingAt = AIM_BODYTOGROUND_BACK;
			state = STATE_POINTBODYTOGROUND_BACK;
		}else {
			aimingAt = AIM_BODYTOGROUND;
			state = STATE_POINTBODYTOGROUND;
		}
	}
}
void Player::normalState(){
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN){
		state= STATE_STANDING;
	}
}


void Player::shoot()
{
	Uint32 currentShotTime = gameView->getTicks();
	int distanceToTravel = 400;

	if((currentShotTime - lastShotTime) > shotCooldown)
	{
		switch(aimingAt){
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

			case AIM_DOWN_BACK:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x, pos_y+25, -7, 7, distanceToTravel));
				break;

			case AIM_UP_BACK:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x, pos_y, -7, -7, distanceToTravel));
				break;
			case AIM_BODYTOGROUND_BACK:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x, pos_y+50, -10, 0, distanceToTravel));
				break;
		}

		lastShotTime = currentShotTime;
	}
}

void Player::spawn(int x, int y){
	pos_x = x;
	pos_y = y;
	state = STATE_STANDING;
	aimingAt = AIM_FRONT;
	lastShotTime = 0;
	shotCooldown = 200;
	bullets.clear();
}

void Player::destroy()
{
	for(int i = 0 ; i < MAX_ANIMATIONS ; i ++){
		animations[i]->destroy();
	}

	bulletSprite->destroy();
	bulletSprite = NULL;
}
