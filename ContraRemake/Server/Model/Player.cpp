/*
 * Character.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "Player.hh"

Player::Player(CameraLogic* _cameraLogic, ServerMessageHandler* _serverMessageHandler, int _player_id)
{
	cameraLogic = _cameraLogic;
	serverMessageHandler = _serverMessageHandler;
	player_id = _player_id;

	gun = new Gun(_cameraLogic, _serverMessageHandler);

	pos_x = 600;
	pos_y = 200;
	maxDistanceJump = 150;
	falling = true;
	processedKeys = false;

	state = STATE_STANDING;
	direction = DIRECTION_FRONT;
	aimingAt = AIM_FRONT;

	movement_beyond_border = true;
}

Player::~Player()
{
	this->destroy();
}

void Player::render()
{
	//----------------------------------------------------------------------
	//Mandar Mensaje para dibujar cuando camina

	if(state == STATE_WALKINGRIGHT ||state == STATE_WALKINGRIGHTPOINTUP || state == STATE_WALKINGRIGHTPOITNDOWN
			|| state == STATE_WALKINGLEFT ||state == STATE_WALKINGLEFTPOINTUP || state == STATE_WALKINGLEFTPOINTDOWN){ // ESTO PASARLO A VIEW COMO ANTES, ASI LE AHORRAMOS TRABAJO AL SERVER, Y DE LA OTRA FORMA NO CHEQUEO POR TODOS LOS ESTADOS

		timeAtIterationStart++;

		if(timeAtIterationStart > 3)
		{
			serverMessageHandler->sendToAllClients(new MessageServer(PLAYER, LOAD, player_id, state));
			timeAtIterationStart =0;
		}
	}

	serverMessageHandler->sendToAllClients(new MessageServer(PLAYER, RENDER, player_id, state, pos_x - cameraLogic->getCameraPosX(), pos_y - cameraLogic->getCameraPosY()));

	gun->render();

}

void Player::handleKeys(const Uint8* playerKeyStates)
{
	if(state == STATE_FREEZED || state == STATE_DEAD )
		return;

	// bug de ambas direcciones
	if(playerKeyStates[KEYCODE_RIGHT] && playerKeyStates[KEYCODE_LEFT])
	{
		LOGGER_DEBUG("IZQ Y DER");
		if(state != STATE_JUMPINGDOWN && state != STATE_JUMPINGUP)
			this->pointDefault(true);
	}
	// caminar derecha
	else if(playerKeyStates[KEYCODE_RIGHT])
	{
		LOGGER_DEBUG("El jugador presiona DERECHA");
		this->walkRight();
		if(playerKeyStates[KEYCODE_DOWN] && !playerKeyStates[KEYCODE_UP])
			this->pointDown(false);
	}
	// caminar izq
	else if(playerKeyStates[KEYCODE_LEFT])
	{
		LOGGER_DEBUG("El jugador presiona IZQUIERDA");
		this->walkLeft();
		if(playerKeyStates[KEYCODE_DOWN] && !playerKeyStates[KEYCODE_UP])
			this->pointDown(false);
	}
	else if(playerKeyStates[KEYCODE_DOWN] && !playerKeyStates[KEYCODE_UP])
	{
		LOGGER_DEBUG("El jugador presiona ABAJO y NO ARRIBA");
		//caer de plataforma solo si se tocan ambas teclas a la vez
		if(playerKeyStates[KEYCODE_SPACE] && !playerKeyStates[KEYCODE_LCTRL])
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
	if(playerKeyStates[KEYCODE_SPACE])
	{
		LOGGER_DEBUG("El jugador SALTA");
		this->jump();
	}

	// apunta arriba
	if(playerKeyStates[KEYCODE_UP])
	{
		if(playerKeyStates[KEYCODE_DOWN])
		{
			this->pointDefault(false);
			LOGGER_DEBUG("El jugador presiona ARRIBA y ABAJO");
		}
		else if(playerKeyStates[KEYCODE_RIGHT] && playerKeyStates[KEYCODE_LEFT] && state != STATE_JUMPINGDOWN && state != STATE_JUMPINGUP) // para bug de ambas direcciones
			this->pointUP(true);
		else if(playerKeyStates[KEYCODE_RIGHT] || playerKeyStates[KEYCODE_LEFT] || state == STATE_JUMPINGDOWN || state == STATE_JUMPINGUP)
			this->pointUP(false);
		else if (state != STATE_JUMPINGDOWN && state != STATE_JUMPINGUP)
			this->pointUP(true);
	}
	else if(!playerKeyStates[KEYCODE_DOWN])
	{
		this->pointDefault(false);
	}

	// dispara, es independiente a lo demas
	if(playerKeyStates[KEYCODE_LCTRL])
	{
		//LOGGER_DEBUG("El jugador DISPARA");
		this->shoot();
	}

	processedKeys = true;
}

void Player::update()
{
	if(falling)
		pos_y += 5;

	//------------------------------------------------------
	//Salto
	switch(state)
	{
		case STATE_JUMPINGUP:
				pos_y-=10;
				maxDistanceJump-=5;
				serverMessageHandler->sendToAllClients(new MessageServer(PLAYER, LOAD, player_id, state));
				if(maxDistanceJump == 0)
					state = STATE_JUMPINGDOWN;

				break;

		case STATE_JUMPINGDOWN:
				maxDistanceJump += 5;
				serverMessageHandler->sendToAllClients(new MessageServer(PLAYER, LOAD, player_id, state));
				if(!falling)
				{
					state = STATE_STANDING;
					maxDistanceJump=150;
				}

				break;

		default:
				break;
	}

	//------------------------------------------------------
	// Actualizacion de posicion de balas
	gun->update();

	processedKeys = false;
}

void Player::jump()
{
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN && !falling)
		state = STATE_JUMPINGUP;
}

void Player::goDown()
{
	if(!falling)
	{
		if (direction == DIRECTION_BACK)
			state = STATE_STANDING_BACK;
		else
			state = STATE_STANDING;

		falling = true;
	}
}

void Player::walkLeft()
{
	direction = DIRECTION_BACK;
	if (!cameraLogic->outOfCameraLeftLimit(pos_x - 5))
	{
		pos_x-=5;
	}
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN)
	{

		if(aimingAt==AIM_UP_BACK)
		{
			state = STATE_WALKINGLEFTPOINTUP;
		}
		else if(aimingAt==AIM_DOWN_BACK)
		{
			state = STATE_WALKINGLEFTPOINTDOWN;
		}
		else
		{
			state = STATE_WALKINGLEFT;
		}
	}
}

bool Player::canMoveRight(int new_pos_x)
{
	if(!cameraLogic->canMoveForward()) // si ya la camara esta bloqueada, es decir llegué al fondo del nivel
	{
		if(!cameraLogic->outOfCameraRightLimit(new_pos_x))
			return true;
		else
			return false;
	}
	else if(!this->canMoveBeyondBorder() && new_pos_x >= cameraLogic->getBorder())
	{
		return false;
	}
	else
		return true;
}

void Player::walkRight()
{
	direction = DIRECTION_FRONT;
	if(this->canMoveRight(pos_x + 5))
	{
		pos_x+=5;
	}

	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN)
	{
		if(aimingAt==AIM_UP)
		{
			state = STATE_WALKINGRIGHTPOINTUP;
		}
		else if(aimingAt==AIM_DOWN)
		{
			state = STATE_WALKINGRIGHTPOITNDOWN;
		}
		else
		{
			state = STATE_WALKINGRIGHT;
		}
	}
}

void Player::pointUP(bool cond)
{
	if(direction == DIRECTION_BACK)
		aimingAt = AIM_UP_BACK;
	else
		aimingAt = AIM_UP;

	if(cond)
	{
		if(direction == DIRECTION_BACK)
			state=STATE_POINTUP_BACK;
		else
			state=STATE_POINTUP;
	}
}

void Player::pointDown(bool cond)
{
	if(direction == DIRECTION_BACK)
			aimingAt = AIM_DOWN_BACK;
	else
		aimingAt = AIM_DOWN;

	if(cond)
	{
		if(direction == DIRECTION_BACK)
			state = STATE_POINTDOWN_BACK;
		else
			state = STATE_POINTDOWN;
	}
}

void Player::pointDefault(bool cond)
{
	if(direction == DIRECTION_BACK)
	{
		aimingAt = AIM_BACK;

		if(cond)
		{
			state = STATE_POINTBACK;
		}
	}
	else
	{
		aimingAt = AIM_FRONT;

		if(cond)
		{
			state = STATE_POINTFRONT;
		}
	}
}

void Player::bodyToGround()
{
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN && !falling)
	{
		if(direction == DIRECTION_BACK)
		{
			aimingAt = AIM_BODYTOGROUND_BACK;
			state = STATE_POINTBODYTOGROUND_BACK;
		}
		else
		{
			aimingAt = AIM_BODYTOGROUND;
			state = STATE_POINTBODYTOGROUND;
		}
	}
}

void Player::normalState()
{
	if(state != STATE_JUMPINGUP && state != STATE_JUMPINGDOWN)
	{
		state = STATE_STANDING;
	}
}

void Player::shoot()
{
	gun->shoot(aimingAt, state, pos_x, pos_y);
}

void Player::spawn(int x, int y)
{
	pos_x = x;
	pos_y = y;

	if(this->isOnline())
	{
		state = STATE_STANDING;
	}

	aimingAt = AIM_FRONT;
	direction = DIRECTION_FRONT;
	maxDistanceJump = 150;
	falling = false;
	processedKeys = false;
	gun->clear();
}

void Player::freeze()
{
	//pos_x = cameraLogic->getCameraPosX();
//	pos_y = y;
	state = STATE_FREEZED;
//	aimingAt = AIM_FRONT;
//	direction = DIRECTION_FRONT;
	maxDistanceJump = 150;
	falling = false;
	processedKeys = true;
	gun->clear();
}

void Player::dragOfflinePlayer()
{
	if(cameraLogic->outOfCameraLeftLimit(pos_x))
	{
		pos_x = cameraLogic->getCameraPosX();
	}
	else if(cameraLogic->outOfCameraLowerLimit(pos_y + 90))
	{
		pos_y = cameraLogic->getCameraPosY() + cameraLogic->getCameraHeight() - 90;
	}
}

void Player::destroy() {}

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
