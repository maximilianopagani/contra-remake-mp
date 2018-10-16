/*
 * Platform.hh
 *
 *  Created on: Sep 16, 2018
 *      Author: pola17
 */

#ifndef PLATFORM_HH_
#define PLATFORM_HH_

#include "../Utils/ICollisional.hh"
#include "../Utils/MessageServer.hh"
#include "CameraLogic.hh"
#include <string>
#include <strings.h>
#include "ServerMessageHandler.hh"

//#include "LogicToViewTransporter.hh"

class Platform : public ICollisional
{
	public:
		//enum GroundType {GRASS, WOOD, ROCK, ICE};

		Platform(CameraLogic* _cameraLogic, std::string type, int pos_x, int pos_y, int pixels,ServerMessageHandler* _serverMessageHandler);
		virtual ~Platform();

		void render();
		int getPosX() { return posX; }
		int getPosY() { return posY; }

		//Collisional
		int getLeftLimit();
		int getRightLimit();
		int getTopLimit();
		int getBottomLimit();

	private:

		enum PlatformType {
			TYPE_GRASS,
			TYPE_ICE,
			TYPE_WOOD,
			TYPE_ROCK,
			TYPE_ERROR
		};

		CameraLogic* cameraLogic;
		ServerMessageHandler* serverMessageHandler;

		std::string typeString;
		PlatformType typeCode;

		int tileAmount, tileWidth, tileHeight, posX, posY;
};

#endif /* PLATFORM_HH_ */
