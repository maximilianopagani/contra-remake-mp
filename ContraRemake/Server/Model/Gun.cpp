/*
 * Gunn.cpp
 *      Author: ldea
 */

#include "Gun.hh"

Gun::Gun(CameraLogic* _cameraLogic, ServerMessageHandler* _serverMessageHandler)
{
	cameraLogic = _cameraLogic;
	serverMessageHandler = _serverMessageHandler;

	setType(BulletType::RIFLE);

	lastShotTime = 0;
}

Gun::~Gun(){}

void Gun::clear()
{
	bullets.clear();
	lastShotTime = 0;
}

void Gun::render(int player_id)
{
	for(bulletsIterator = bullets.begin(); bulletsIterator != bullets.end();)
	{
		(*bulletsIterator)->render(player_id, bulletType);
		++bulletsIterator;
	}
}

void Gun::update()
{
	for(bulletsIterator = bullets.begin(); bulletsIterator != bullets.end();)
	{
		(*bulletsIterator)->updatePos();

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

void Gun::setType(BulletType type)
{
	bulletType = type;
	shotCooldown = BulletTypeHandler::getCooldown(bulletType);
	distanceToTravel = BulletTypeHandler::getDistance(bulletType);
}

void Gun::shoot(int aimingAt, int state, int pos_x, int pos_y)
{
	Uint32 currentShotTime = Utils::getTicks();

	if((currentShotTime - lastShotTime) > shotCooldown)
	{
		bool oneShot = true;
		if (bulletType == BulletType::LASER)
			oneShot = false;

		switch(aimingAt)
		{
			case AIM_FRONT:
				bullets.push_back(new Bullet(cameraLogic, pos_x+47, pos_y+25, 10, 0, distanceToTravel, oneShot, serverMessageHandler));
				if (bulletType == BulletType::SPREAD)
				{
					if (state == STATE_WALKINGRIGHT)
					{
						bullets.push_back(new Bullet(cameraLogic, pos_x+47, pos_y+25, 9, -5, distanceToTravel, oneShot, serverMessageHandler));
						bullets.push_back(new Bullet(cameraLogic, pos_x+47, pos_y+25, 9, 5, distanceToTravel, oneShot, serverMessageHandler));
					} else {
						bullets.push_back(new Bullet(cameraLogic, pos_x+47, pos_y+25, 7, -7, distanceToTravel, oneShot, serverMessageHandler));
						bullets.push_back(new Bullet(cameraLogic, pos_x+47, pos_y+25, 7, 7, distanceToTravel, oneShot, serverMessageHandler));
					}
				}
				break;

			case AIM_BACK:
				bullets.push_back(new Bullet(cameraLogic, pos_x-1, pos_y+25, -10, 0, distanceToTravel, oneShot, serverMessageHandler));
				if (bulletType == BulletType::SPREAD)
				{
					if (state == STATE_WALKINGLEFT)
					{
						bullets.push_back(new Bullet(cameraLogic, pos_x-1, pos_y+25, -9, -5, distanceToTravel, oneShot, serverMessageHandler));
						bullets.push_back(new Bullet(cameraLogic, pos_x-1, pos_y+25, -9, 5, distanceToTravel, oneShot, serverMessageHandler));
					} else {
						bullets.push_back(new Bullet(cameraLogic, pos_x-1, pos_y+25, -7, -7, distanceToTravel, oneShot, serverMessageHandler));
						bullets.push_back(new Bullet(cameraLogic, pos_x-1, pos_y+25, -7, 7, distanceToTravel, oneShot, serverMessageHandler));
					}
				}
				break;

			case AIM_UP:
				if (state == STATE_WALKINGRIGHTPOINTUP)
				{
					bullets.push_back(new Bullet(cameraLogic, pos_x+35, pos_y, 9, -5, distanceToTravel, oneShot, serverMessageHandler));
					if (bulletType == BulletType::SPREAD)
					{
						bullets.push_back(new Bullet(cameraLogic, pos_x+35, pos_y, 5, -8, distanceToTravel, oneShot, serverMessageHandler));
						bullets.push_back(new Bullet(cameraLogic, pos_x+35, pos_y, 10, 0, distanceToTravel, oneShot, serverMessageHandler));
					}
				} else {
					bullets.push_back(new Bullet(cameraLogic, pos_x+35, pos_y, 7, -7, distanceToTravel, oneShot, serverMessageHandler));
					if (bulletType == BulletType::SPREAD)
					{
						bullets.push_back(new Bullet(cameraLogic, pos_x+35, pos_y, 0, -10, distanceToTravel, oneShot, serverMessageHandler));
						bullets.push_back(new Bullet(cameraLogic, pos_x+35, pos_y, 10, 0, distanceToTravel, oneShot, serverMessageHandler));
					}
				}
				break;

			case AIM_UP_BACK:
				if (state == STATE_WALKINGLEFTPOINTUP)
				{
					bullets.push_back(new Bullet(cameraLogic, pos_x, pos_y, -9, -5, distanceToTravel, oneShot, serverMessageHandler));
					if (bulletType == BulletType::SPREAD)
					{
						bullets.push_back(new Bullet(cameraLogic, pos_x, pos_y, -5, -8, distanceToTravel, oneShot, serverMessageHandler));
						bullets.push_back(new Bullet(cameraLogic, pos_x, pos_y, -10, 0, distanceToTravel, oneShot, serverMessageHandler));
					}
				} else {
					bullets.push_back(new Bullet(cameraLogic, pos_x, pos_y, -7, -7, distanceToTravel, oneShot, serverMessageHandler));
					if (bulletType == BulletType::SPREAD)
					{
						bullets.push_back(new Bullet(cameraLogic, pos_x, pos_y, 0, -10, distanceToTravel, oneShot, serverMessageHandler));
						bullets.push_back(new Bullet(cameraLogic, pos_x, pos_y, -10, 0, distanceToTravel, oneShot, serverMessageHandler));
					}
				}
				break;

			case AIM_DOWN:
				bullets.push_back(new Bullet(cameraLogic, pos_x+40, pos_y+46, 9, 5, distanceToTravel, oneShot, serverMessageHandler));
				if (bulletType == BulletType::SPREAD)
				{
					bullets.push_back(new Bullet(cameraLogic, pos_x+40, pos_y+46, 10, 0, distanceToTravel, oneShot, serverMessageHandler));
					bullets.push_back(new Bullet(cameraLogic, pos_x+40, pos_y+46, 5, 8, distanceToTravel, oneShot, serverMessageHandler));
				}
				break;

			case AIM_DOWN_BACK:
				bullets.push_back(new Bullet(cameraLogic, pos_x, pos_y+46, -9, 5, distanceToTravel, oneShot, serverMessageHandler));
				if (bulletType == BulletType::SPREAD)
				{
					bullets.push_back(new Bullet(cameraLogic, pos_x, pos_y+46, -10, 0, distanceToTravel, oneShot, serverMessageHandler));
					bullets.push_back(new Bullet(cameraLogic, pos_x, pos_y+46, -5, 8, distanceToTravel, oneShot, serverMessageHandler));
				}
				break;

			case AIM_BODYTOGROUND:
				bullets.push_back(new Bullet(cameraLogic, pos_x+70, pos_y+64, 10, 0, distanceToTravel, oneShot, serverMessageHandler));
				if (bulletType == BulletType::SPREAD)
				{
					bullets.push_back(new Bullet(cameraLogic, pos_x+70, pos_y+64, 7, -7, distanceToTravel, oneShot, serverMessageHandler));
					bullets.push_back(new Bullet(cameraLogic, pos_x+70, pos_y+64, 7, 7, distanceToTravel, oneShot, serverMessageHandler));
				}
				break;

			case AIM_BODYTOGROUND_BACK:
				bullets.push_back(new Bullet(cameraLogic, pos_x-5, pos_y+64, -10, 0, distanceToTravel, oneShot, serverMessageHandler));
				if (bulletType == BulletType::SPREAD)
				{
					bullets.push_back(new Bullet(cameraLogic, pos_x-5, pos_y+64, -7, -7, distanceToTravel, oneShot, serverMessageHandler));
					bullets.push_back(new Bullet(cameraLogic, pos_x-5, pos_y+64, -7, 7, distanceToTravel, oneShot, serverMessageHandler));
				}
				break;
		}

		lastShotTime = currentShotTime;

		serverMessageHandler->sendToAllClients(new MessageServer(SOUND,LOAD,4,bulletType));
	}
}
