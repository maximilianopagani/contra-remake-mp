/*
 * Character.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "Player.hh"

Player::Player(CameraLogic* _cameraLogic, LogicToViewTransporter* _logicToViewTransporter)
{
	cameraLogic = _cameraLogic;
	logicToViewTransporter = _logicToViewTransporter;
	pos_x = 150;
	pos_y = 300;
	maxDistanceJump=150;
	falling = true;

	state = STATE_STANDING;
	direction = DIRECTION_FRONT;

	aimingAt = AIM_FRONT;

	lastShotTime = 0;
	shotCooldown = 175;
}

Player::~Player()
{
	this->destroy();
}

void Player::render()
{
	//logica para que camine lento
	if(state == STATE_WALKINGRIGHT ||state == STATE_WALKINGRIGHTPOINTUP || state == STATE_WALKINGRIGHTPOITNDOWN
		|| state == STATE_WALKINGLEFT ||state == STATE_WALKINGLEFTPOINTUP || state == STATE_WALKINGLEFTPOINTDOWN){

		timeAtIterationStart++;

		if(timeAtIterationStart > 3){
			logicToViewTransporter->sendToLoad(PLAYERVIEW, PlayerStateHandler::stateToString(state));
			timeAtIterationStart =0;
		}
	}

	logicToViewTransporter->sendToDraw(PLAYERVIEW, state, pos_x - cameraLogic->getCameraPosX(), pos_y - cameraLogic->getCameraPosY());

    // Renderizado de balas
	for(bulletsIterator = bullets.begin(); bulletsIterator != bullets.end();)
	{
		(*bulletsIterator)->sendToDraw();
		++bulletsIterator;
	}
}

void Player::handleKeys(const Uint8* _currentKeyStates)
{
	LOGGER_DEBUG("Comienzo handle en state : " + PlayerStateHandler::stateToString(state) );
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
		LOGGER_DEBUG("El jugador SALTA");
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
				logicToViewTransporter->sendToLoad(PLAYERVIEW, PlayerStateHandler::stateToString(state));
				if(maxDistanceJump == 0) state = STATE_JUMPINGDOWN;
				break;
		case STATE_JUMPINGDOWN:
				maxDistanceJump += 5;
				logicToViewTransporter->sendToLoad(PLAYERVIEW, PlayerStateHandler::stateToString(state));
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
	if (!cameraLogic->outOfCameraLeftLimit(pos_x - 5)) {
		pos_x-=5;
	}
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN) {

		if(aimingAt==AIM_UP_BACK){
			state = STATE_WALKINGLEFTPOINTUP;
		}
		else if(aimingAt==AIM_DOWN_BACK){
			state = STATE_WALKINGLEFTPOINTDOWN;
		}
		else {
			state = STATE_WALKINGLEFT;
		}
	}
}

void Player::walkRight(){
	direction = DIRECTION_FRONT;
	if (!cameraLogic->outOfCameraRightLimit(pos_x + 5)) {
		pos_x+=5;
	}
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN) {
		if(aimingAt==AIM_UP){
			state = STATE_WALKINGRIGHTPOINTUP;
		}
		else if(aimingAt==AIM_DOWN){
			state = STATE_WALKINGRIGHTPOITNDOWN;
		}
		else {
			state = STATE_WALKINGRIGHT;
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
//	TODO sacar SDL_GetTicks() de aca
	Uint32 currentShotTime = SDL_GetTicks();
	int distanceToTravel = 425;

	if((currentShotTime - lastShotTime) > shotCooldown)
	{
		switch(aimingAt){
			case AIM_FRONT:
				bullets.push_back(new Bullet(cameraLogic, logicToViewTransporter, pos_x+47, pos_y+25, 10, 0, distanceToTravel));
				break;

			case AIM_BACK:
				bullets.push_back(new Bullet(cameraLogic, logicToViewTransporter, pos_x-1, pos_y+25, -10, 0, distanceToTravel));
				break;

			case AIM_UP:
				if (state == STATE_WALKINGRIGHTPOINTUP)
					bullets.push_back(new Bullet(cameraLogic, logicToViewTransporter, pos_x+35, pos_y, 9, -5, distanceToTravel));
				else
					bullets.push_back(new Bullet(cameraLogic, logicToViewTransporter, pos_x+35, pos_y, 7, -7, distanceToTravel));
				break;

			case AIM_UP_BACK:
				if (state == STATE_WALKINGLEFTPOINTUP)
					bullets.push_back(new Bullet(cameraLogic, logicToViewTransporter, pos_x, pos_y, -9, -5, distanceToTravel));
				else
				bullets.push_back(new Bullet(cameraLogic, logicToViewTransporter, pos_x, pos_y, -7, -7, distanceToTravel));
				break;

			case AIM_DOWN:
				bullets.push_back(new Bullet(cameraLogic, logicToViewTransporter, pos_x+40, pos_y+46, 9, 5, distanceToTravel));
				break;

			case AIM_DOWN_BACK:
				bullets.push_back(new Bullet(cameraLogic, logicToViewTransporter, pos_x, pos_y+46, -9, 5, distanceToTravel));
				break;

			case AIM_BODYTOGROUND:
				bullets.push_back(new Bullet(cameraLogic, logicToViewTransporter, pos_x+90, pos_y+64, 10, 0, distanceToTravel));
				break;

			case AIM_BODYTOGROUND_BACK:
				bullets.push_back(new Bullet(cameraLogic, logicToViewTransporter, pos_x, pos_y+64, -10, 0, distanceToTravel));
				break;
		}

		lastShotTime = currentShotTime;
	}
}

void Player::spawn(int x, int y)
{
	pos_x = x;
	pos_y = y;
	state = STATE_STANDING;
	aimingAt = AIM_FRONT;
	direction = DIRECTION_FRONT;
	maxDistanceJump = 150;
	falling = true;
	lastShotTime = 0;
	bullets.clear();
}

void Player::destroy()
{
}

int Player::getLeftLimit()
{
	return getPosX() + 15;
}

int Player::getRightLimit()
{
	return getPosX() + PlayerStateHandler::getDestinationWidth(state) - 15;
}

int Player::getTopLimit()
{
	return getPosY();
}

int Player::getBottomLimit()
{
	return getTopLimit() + PlayerStateHandler::getDestinationHeight(state);
}
