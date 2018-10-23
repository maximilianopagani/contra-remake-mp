/*
 * Level.h
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#ifndef MODEL_LEVEL_HH_
#define MODEL_LEVEL_HH_

#include "../../Utils/PlatformParser.hh"
#include "../../Utils/GameParser.hh"
#include "Platform.hh"
#include "Enemy.hh"
#include "CameraLogic.hh"
#include "ServerMessageHandler.hh"

enum LevelNumber {LEVEL1, LEVEL2, LEVEL3};
enum ScrollingType {SCROLLING_VERTICAL, SCROLLING_HORIZONTAL};

class Level
{
	public:

		Level( CameraLogic* _cameraLogic, int _level , ServerMessageHandler* _serverMessageHandler,GameParser* _gameParser);
		virtual ~Level();

		void render();
		void destroy();
		void moveForward(int pixels_to_move);

		int getSpawnPointX() { return playerSpawnX; }
		int getSpawnPointY() { return playerSpawnY; }

		int getRespawnPointX() { return playerRespawnX; }
		int getRespawnPointY() { return playerRespawnY; }

		std::string getBackground1Path() { return background1Path; }
		std::string getBackground2Path() { return background2Path; }
		std::string getBackground3Path() { return background3Path; }

		int getBorder() { return border; }
		int getScrollingType() { return scrolling; }

		list<Platform*>* getPlataformList(){ return &platforms; }

		void restart();

	private:

		CameraLogic* cameraLogic;
		GameParser* gameParser;

		int background1PosX, background1PosY, background1Width, background1Height;
		int background2PosX, background2PosY, background2Width, background2Height;
		int background3PosX, background3PosY, background3Width, background3Height;

		std::string background1Path;
		std::string background2Path;
		std::string background3Path;

		int playerSpawnX, playerSpawnY, playerRespawnX, playerRespawnY, border;

		ScrollingType scrolling;

		ServerMessageHandler* serverMessageHandler;

		std::list<PlataformParser> platformParser;
		std::list<PlataformParser>::iterator platformParserIterator;
		std::list<Platform*> platforms;
		std::list<Platform*>::iterator platformsIterator;

        Enemy* enemy;
};

#endif /* MODEL_LEVEL_HH_ */
