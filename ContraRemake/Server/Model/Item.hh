/*
 * Item.hh
 *
 *  Created on: Nov 6, 2018
 *      Author: gmc
 */

#ifndef SERVER_MODEL_ITEM_HH_
#define SERVER_MODEL_ITEM_HH_

#include "../../Utils/ICollisional.hh"
#include "../../Utils/MessageServer.hh"
#include "CameraLogic.hh"
#include <string>
#include <strings.h>
#include "ServerMessageHandler.hh"
#include "../../Utils/ItemTypes.hh"

class Item: public ICollisional
{
	public:

		Item(CameraLogic* _cameraLogic, std::string type, int pos_x, int pos_y, ServerMessageHandler* _serverMessageHandler);
		virtual ~Item();

		void render();
		int getPosX() { return posX; }
		int getPosY() { return posY; }

		//Collisional
		int getLeftLimit();
		int getRightLimit();
		int getTopLimit();
		int getBottomLimit();

	private:

		CameraLogic* cameraLogic;
		ServerMessageHandler* serverMessageHandler;

		std::string typeString;
		ItemType typeCode;

		int posX, posY;
};

#endif /* SERVER_MODEL_ITEM_HH_ */
