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
	pos_x = 150;
	pos_y = 300;
	maxDistanceJump=140;
	falling = true ;

	state = STATE_STANDING;
	direction = DIRECTION_FRONT;

	animations[STATE_WALKINGRIGHT] = new Sprite(gameView,"image/walkingRight.png", 25, 38, 58, 87);
	animations[STATE_WALKINGRIGHTPOINTUP] = new Sprite(gameView,"image/walkingRightPointingUp.png", 19, 38, 44, 87);
	animations[STATE_WALKINGRIGHTPOITNDOWN] = new Sprite(gameView,"image/walkingRightPointingDown.png", 21, 38, 48, 87);
	animations[STATE_WALKINGLEFT] = new Sprite(gameView,"image/walkingLeft.png", 25, 38, 58, 87);
	animations[STATE_WALKINGLEFTPOINTUP] = new Sprite(gameView,"image/walkingLeftPointingUp.png", 19, 38, 44, 87);
	animations[STATE_WALKINGLEFTPOINTDOWN] = new Sprite(gameView,"image/walkingLeftPointingDown.png", 21, 38, 48, 87);
	animations[STATE_STANDING] = new Sprite(gameView,"image/standing.png", 16, 38, 39, 87);
	animations[STATE_STANDING_BACK] = new Sprite(gameView,"image/standingBack.png", 16, 38, 39, 87);
	animations[STATE_JUMPINGUP] = new Sprite(gameView,"image/jumping.png", 20, 38, 46, 114);
	animations[STATE_JUMPINGDOWN] = new Sprite(gameView,"image/jumping.png", 20, 38, 46, 87);
	animations[STATE_POINTUP] = new Sprite(gameView,"image/pointUp.png", 18, 36, 41, 82);
	animations[STATE_POINTFRONT] = new Sprite(gameView,"image/pointFront.png", 25, 36, 58, 82);
	animations[STATE_POINTBACK] = new Sprite(gameView,"image/pointBack.png", 25, 36, 58, 82);
	animations[STATE_POINTDOWN] = new Sprite(gameView,"image/pointDown.png", 22, 37, 51, 85);
	animations[STATE_POINTBODYTOGROUND] = new Sprite(gameView,"image/bodyToGround.png", 32, 38, 96, 87);
	animations[STATE_POINTDOWN_BACK] = new Sprite(gameView,"image/pointDownBack.png", 22, 37, 51, 85);
	animations[STATE_POINTBODYTOGROUND_BACK] = new Sprite(gameView,"image/bodyToGroundBack.png", 32, 38, 74, 87);
	animations[STATE_POINTUP_BACK] = new Sprite(gameView,"image/pointUpBack.png", 18, 36, 41, 82);


	aimingAt = AIM_FRONT;

	bulletSprite = new Sprite(gameView, "imagenes/CharacterSprites.png", 8, 8, 8, 8);
	bulletSprite->setSourceRectXY(104, 8);

	lastShotTime = 0;
	shotCooldown = 175;
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

string Player::toString()
{
	switch(state)
	{
		case STATE_WALKINGRIGHT:
			return "STATE_WALKINGRIGHT";
		case STATE_WALKINGRIGHTPOINTUP:
			return "STATE_WALKINGRIGHTPOINTUP";
		case STATE_WALKINGRIGHTPOITNDOWN:
			return "STATE_WALKINGRIGHTPOITNDOWN";
		case STATE_WALKINGLEFT:
			return "STATE_WALKINGLEFT";
		case STATE_WALKINGLEFTPOINTUP:
			return "STATE_WALKINGLEFTPOINTUP";
		case STATE_WALKINGLEFTPOINTDOWN:
			return "STATE_WALKINGLEFTPOINTDOWN";
		case STATE_STANDING:
			return "STATE_STANDING";
		case STATE_STANDING_BACK:
			return "STATE_STANDING_BACK";
		case STATE_JUMPINGUP:
			return "STATE_JUMPINGUP";
		case STATE_JUMPINGDOWN:
			return "STATE_JUMPINGDOWN";
		case STATE_POINTUP:
			return "STATE_POINTUP";
		case STATE_POINTFRONT:
			return "STATE_POINTFRONT";
		case STATE_POINTBACK:
			return "STATE_POINTBACK";
		case STATE_POINTDOWN:
			return "STATE_POINTDOWN";
		case STATE_POINTBODYTOGROUND:
			return "STATE_POINTBODYTOGROUND";
		case STATE_POINTUP_BACK:
			return "STATE_POINTUP_BACK";
		case STATE_POINTDOWN_BACK:
			return "STATE_POINTDOWN_BACK";
		case STATE_POINTBODYTOGROUND_BACK:
			return "STATE_POINTBODYTOGROUND_BACK";
	}
	return "SIN ESTADO";
}

void Player::handleKeys(const Uint8* _currentKeyStates)
{
	LOGGER_DEBUG("Comienzo handle en state : " + toString() );
	currentKeyStates = _currentKeyStates;

	// bug de ambas direcciones
	if(currentKeyStates[SDL_SCANCODE_RIGHT] && currentKeyStates[SDL_SCANCODE_LEFT])
	{
		LOGGER_DEBUG("IZQ Y DER");
		if(state != STATE_JUMPINGDOWN && state != STATE_JUMPINGUP)
			this->pointDefault(true);
	}
	// caminar derecha
	else if(currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		LOGGER_DEBUG("El jugador presiona DERECHA");
		this->walkRight();
		if(currentKeyStates[SDL_SCANCODE_DOWN] && !currentKeyStates[SDL_SCANCODE_UP])
			this->pointDown(false);
	}
	// caminar izq
	else if(currentKeyStates[SDL_SCANCODE_LEFT])
	{
		LOGGER_DEBUG("El jugador presiona IZQUIERDA");
		this->walkLeft();
		if(currentKeyStates[SDL_SCANCODE_DOWN] && !currentKeyStates[SDL_SCANCODE_UP])
			this->pointDown(false);
	}
	else if(currentKeyStates[SDL_SCANCODE_DOWN] && !currentKeyStates[SDL_SCANCODE_UP])
	{
		LOGGER_DEBUG("El jugador presiona ABAJO y NO ARRIBA");
		//caer de plataforma solo si se tocan ambas teclas a la vez
		if(currentKeyStates[SDL_SCANCODE_SPACE] && !currentKeyStates[SDL_SCANCODE_LCTRL])
			this->goDown();
		//cuerpo a tierra -- bug arriba+abajo
		else
			this->bodyToGround();
	}
	// cuando no es niguno vuelve a estado de reposo
	else if(state != STATE_JUMPINGDOWN && state != STATE_JUMPINGUP)
	{
		this->pointDefault(true);
	}

	//Salto
	if(currentKeyStates[SDL_SCANCODE_SPACE])
	{
		LOGGER_DEBUG("El jugaodor SALTA");
		this->jump();
	}

	// apunta arriba
	if(currentKeyStates[SDL_SCANCODE_UP])
	{
		if(currentKeyStates[SDL_SCANCODE_DOWN])
		{
			this->pointDefault(false);
			LOGGER_DEBUG("El jugador presiona ARRIBA y ABAJO");
		}
		else if(currentKeyStates[SDL_SCANCODE_RIGHT] && currentKeyStates[SDL_SCANCODE_LEFT] && state != STATE_JUMPINGDOWN && state != STATE_JUMPINGUP) // para bug de ambas direcciones
			this->pointUP(true);
		else if(currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_LEFT] || state == STATE_JUMPINGDOWN || state == STATE_JUMPINGUP)
			this->pointUP(false);
		else if (state != STATE_JUMPINGDOWN && state != STATE_JUMPINGUP)
			this->pointUP(true);
	}
	else if(!currentKeyStates[SDL_SCANCODE_DOWN])
	{
		this->pointDefault(false);
	}

	// dispara, es independiente a lo demas
	if(currentKeyStates[SDL_SCANCODE_LCTRL])
	{
		LOGGER_DEBUG("El jugador DISPARA");
		this->shoot();
	}

}

void Player::update(){

	if(falling) pos_y += 5;
	//Salto
	switch(state) {
		case STATE_JUMPINGUP:
				pos_y-=10;
				maxDistanceJump-=5;
				animations[state]->update();
				if(maxDistanceJump == 0) state = STATE_JUMPINGDOWN;
				break;
		case STATE_JUMPINGDOWN:
				maxDistanceJump += 5;
				animations[state]->update();
				if(!falling) {
					state = STATE_STANDING;
					maxDistanceJump=150;
				}
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
void Player::resetPos(int _pos_y){
	pos_x = 150;
	pos_y = _pos_y;
	maxDistanceJump=150;
	state = STATE_STANDING;
	direction = DIRECTION_FRONT;
}

void Player::jump(){
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN && !falling) state = STATE_JUMPINGUP;
}

void Player::goDown(){
	if(!falling)
	{
		if (direction == DIRECTION_BACK)
			state = STATE_STANDING_BACK;
		else
			state = STATE_STANDING;
		falling = true;
	}
}

void Player::walkLeft(){
	direction = DIRECTION_BACK;
	if (!gameView->outOfWindowLeftBorder(pos_x - 5)) {
		pos_x-=5;
	}
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN) {

		if(aimingAt==AIM_UP_BACK){
			state = STATE_WALKINGLEFTPOINTUP;
			animations[state]->update();
		}
		else if(aimingAt==AIM_DOWN_BACK){
			state = STATE_WALKINGLEFTPOINTDOWN;
			animations[state]->update();
		}
		else {
			state = STATE_WALKINGLEFT;
				animations[state]->update();
		}
	}
}

void Player::walkRight(){
	direction = DIRECTION_FRONT;
	if (!gameView->outOfWindowRightBorder(pos_x + 5)) {
		pos_x+=5;
	}
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN) {
		if(aimingAt==AIM_UP){
			state = STATE_WALKINGRIGHTPOINTUP;
			animations[state]->update();
		}
		else if(aimingAt==AIM_DOWN){
			state = STATE_WALKINGRIGHTPOITNDOWN;
			animations[state]->update();
		}
		else {
			state = STATE_WALKINGRIGHT;
			animations[state]->update();
		}
	}
}

void Player::pointUP(bool cond){
	if(direction == DIRECTION_BACK)
		aimingAt = AIM_UP_BACK;
	else aimingAt = AIM_UP;

	if(cond){
		if(direction == DIRECTION_BACK)
			state=STATE_POINTUP_BACK;
		else state=STATE_POINTUP;
	}
}

void Player::pointDown(bool cond){
	if(direction == DIRECTION_BACK)
			aimingAt = AIM_DOWN_BACK;
	else aimingAt = AIM_DOWN;

	if(cond){
		if(direction == DIRECTION_BACK)
			state = STATE_POINTDOWN_BACK;
		else state = STATE_POINTDOWN;
	}
}

void Player::pointDefault(bool cond){
	if(direction == DIRECTION_BACK)
			aimingAt = AIM_BACK;
	else aimingAt = AIM_FRONT;

	if(cond){
		if(direction == DIRECTION_BACK)
			state = STATE_POINTBACK;
		else state = STATE_POINTFRONT;
	}
}

void Player::bodyToGround(){
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN && !falling){
		if(direction == DIRECTION_BACK) {
			aimingAt = AIM_BODYTOGROUND_BACK;
			state = STATE_POINTBODYTOGROUND_BACK;
		} else {
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
	int distanceToTravel = 425;

	if((currentShotTime - lastShotTime) > shotCooldown)
	{
		switch(aimingAt){
			case AIM_FRONT:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x+47, pos_y+24, 10, 0, distanceToTravel));
				break;

			case AIM_BACK:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x-1, pos_y+24, -10, 0, distanceToTravel));
				break;

			case AIM_UP:
				if (state == STATE_WALKINGRIGHTPOINTUP)
					bullets.push_back(new Bullet(gameView, bulletSprite, pos_x+35, pos_y, 9, -5, distanceToTravel));
				else
					bullets.push_back(new Bullet(gameView, bulletSprite, pos_x+35, pos_y, 7, -7, distanceToTravel));
				break;

			case AIM_UP_BACK:
				if (state == STATE_WALKINGLEFTPOINTUP)
					bullets.push_back(new Bullet(gameView, bulletSprite, pos_x, pos_y, -9, -5, distanceToTravel));
				else
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x, pos_y, -7, -7, distanceToTravel));
				break;

			case AIM_DOWN:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x+40, pos_y+46, 9, 5, distanceToTravel));
				break;

			case AIM_DOWN_BACK:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x, pos_y+46, -9, 5, distanceToTravel));
				break;

			case AIM_BODYTOGROUND:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x+90, pos_y+64, 10, 0, distanceToTravel));
				break;

			case AIM_BODYTOGROUND_BACK:
				bullets.push_back(new Bullet(gameView, bulletSprite, pos_x, pos_y+64, -10, 0, distanceToTravel));
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
	for(int i = 0 ; i < MAX_ANIMATIONS ; i++){
		if (animations[i]) {animations[i]->destroy();}
	}
	bulletSprite->destroy();
	bulletSprite = NULL;
}

int Player::getLeftLimit()
{
	return getPosX() + 15;
}

int Player::getRightLimit()
{
	return getPosX() + animations[state]->getDestinationWidth() - 15;
}

int Player::getTopLimit()
{
	return getPosY();
}

int Player::getBottomLimit()
{
	return getTopLimit() + animations[state]->getDestinationHeight();
}
