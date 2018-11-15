/*
 * Character.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "Player.hh"

Player::Player(CameraLogic* _cameraLogic, ServerMessageHandler* _serverMessageHandler, int _player_id, string _username) // @suppress("Class members should be properly initialized")
{
	cameraLogic = _cameraLogic;
	serverMessageHandler = _serverMessageHandler;
	player_id = _player_id;
	username = _username;

	gun = new Gun(_cameraLogic, _serverMessageHandler);

	pos_x = 600;
	pos_y = 200;
	maxDistanceJump = 150;
	falling = true;
	lives_remaining = 3;
	immortal_mode = false;
	processedKeys = false;

	state = STATE_STANDING;
	direction = DIRECTION_FRONT;
	aimingAt = AIM_FRONT;

	movement_beyond_border = true;

	std::cout<<"CREADO PLAYER CON ID Y USERNAME "<<player_id<<" "<<username<<std::endl;
}

Player::~Player()
{
	this->destroy();
}

void Player::pickupItem(Item* item)
{
	ItemType item_type = item->getType();

	switch(item_type)
	{
		case TYPE_MACHINEGUNFALCON:
		{
			gun->setType(MACHINEGUN);
			break;
		}
		case TYPE_SPREADGUNFALCON:
		{
			gun->setType(TRIPLE);
			break;
		}
		default:
		{
			break;
		}
	}
}

void Player::renderLives()
{
	serverMessageHandler->sendToAllClients(new MessageServer(LIVES, RENDER, player_id, lives_remaining));
}

void Player::renderPlayer()
{
	if(state == STATE_WALKINGRIGHT || state == STATE_WALKINGRIGHTPOINTUP || state == STATE_WALKINGRIGHTPOITNDOWN || state == STATE_WALKINGLEFT ||state == STATE_WALKINGLEFTPOINTUP || state == STATE_WALKINGLEFTPOINTDOWN)
	{ // ESTO PASARLO A VIEW COMO ANTES, ASI LE AHORRAMOS TRABAJO AL SERVER, Y DE LA OTRA FORMA NO CHEQUEO POR TODOS LOS ESTADOS
		timeAtIterationStart++;

		if(timeAtIterationStart > 3)
		{
			serverMessageHandler->sendToAllClients(new MessageServer(PLAYER, LOAD, player_id, state));
			timeAtIterationStart =0;
		}
	}

	serverMessageHandler->sendToAllClients(new MessageServer(PLAYER, RENDER, player_id, state, pos_x - cameraLogic->getCameraPosX(), pos_y - cameraLogic->getCameraPosY()));
}

void Player::renderGun()
{
	gun->render(player_id);
}

void Player::handleKeys(const Uint8* playerKeyStates)
{
	if(this->isOffline() || this->isDead())
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

	//================================ MODO INMORTAL ================================
	if(playerKeyStates[KEYCODE_I])
	{
		Uint32 currentTime = Utils::getTicks();

		if(last_immortal_mode + 1000 < currentTime)
		{
			if(immortal_mode)
				immortal_mode = false;
			else
				immortal_mode = true;

			last_immortal_mode = currentTime;
		}

	}
	//===============================================================================

	processedKeys = true;
}

void Player::updatePlayer()
{
	if(falling)
		pos_y += 5;

	switch(state)
	{
		case STATE_JUMPINGUP:
		{
			pos_y-=10;
			maxDistanceJump-=5;

			serverMessageHandler->sendToAllClients(new MessageServer(PLAYER, LOAD, player_id, state));

			if(maxDistanceJump == 0)
				state = STATE_JUMPINGDOWN;

			break;
		}

		case STATE_JUMPINGDOWN:
		{
			maxDistanceJump += 5;

			serverMessageHandler->sendToAllClients(new MessageServer(PLAYER, LOAD, player_id, state));

			if(!falling)
			{
				state = STATE_STANDING;
				maxDistanceJump=150;
			}

			break;
		}

		default:
			break;
	}

	this->updateCollisionBox();

	processedKeys = false;
}

void Player::updateGun()
{
	gun->update();
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
			state = STATE_POINTUP_BACK;
		else
			state = STATE_POINTUP;
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

void Player::kill()
{
	state = STATE_DEAD;
	lives_remaining--;
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
	gun->setType(NORMAL);
}

void Player::freeze()
{
	state = STATE_FREEZED;
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

void Player::setOnlineAgain()
{
	if(this->outOfLives())
	{
		state = STATE_DEAD;
	}
	else
	{
		state = STATE_STANDING;
	}
}

void Player::destroy() {}

void Player::updateCollisionBox()
{
	if(state == STATE_POINTBODYTOGROUND_BACK || state == STATE_POINTBODYTOGROUND)
	{
		col_box_xi = pos_x + 15;
		col_box_yi = pos_y + 53; // Esto es lo que se ajusta para el col box
		col_box_xf = pos_x + 74 - 15;
		col_box_yf = col_box_yi + 34; // Esto es lo que se ajusta para el col box
	}
	else if(state == STATE_JUMPINGUP || state == STATE_JUMPINGDOWN)
	{
		col_box_xi = pos_x + 15;
		col_box_yi = pos_y + 27; // Esto es lo que se ajusta para el col box
		col_box_xf = pos_x + 46 - 15;
		col_box_yf = pos_y + 87; // Pongo esto y no le da abajo porque sino me queda un rectangulo de alto menor al de la textura y al venir de un estado anterior
		// con altura mayor, la posxy es distinta y no colisiona bien, la solucion seria rehacer los sprites de salto, haciendo que el player girando quede bien abajo en la sprite
		//col_box_yf = col_box_yi + 46; // Esto es lo que se ajusta para el col box
	}
	else
	{
		col_box_xi = pos_x + 15;
		col_box_yi = pos_y;
		col_box_xf = pos_x + PlayerStateHandler::getDestinationWidth(state) - 15;
		col_box_yf = pos_y + PlayerStateHandler::getDestinationHeight(state);
	}
}
