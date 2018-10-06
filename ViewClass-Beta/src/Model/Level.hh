/*
 * Level.h
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#ifndef SRC_LEVEL_HH_
#define SRC_LEVEL_HH_

#include "../Utils/GameParser.hh"
#include "../Utils/PlatformParser.hh"
#include "../Vista/GameView.hh"
#include "Platform.hh"
#include "../Vista/Sprite.hh"
#include "../Utils/Headers.hh"
#include "Enemy.hh"
#include "CameraLogic.hh"

enum LevelNumber {LEVEL1, LEVEL2, LEVEL3};

class Level
{
	public:

		Level(GameParser* gameParser, GameView* gameView, CameraLogic* _cameraLogic, LogicToViewTransporter* _logicToViewTransporter, LevelNumber _level);
		virtual ~Level();

		void render();
		void destroy();
		void moveForward(int playerPosX, int playerPosY);

		int getSpawnPointX() { return playerSpawnX; }
		int getSpawnPointY() { return playerSpawnY; }
		list<Platform*>* getPlataformList(){ return &platforms; }

		void restart();

	private:

		GameView* gameView;
		CameraLogic* cameraLogic;
		LogicToViewTransporter* logicToViewTransporter;

		Sprite* background1Sprite;
		Sprite* background2Sprite;
		Sprite* background3Sprite;

		int playerSpawnX, playerSpawnY, border;

		enum ScrollingType {SCROLLING_VERTICAL, SCROLLING_HORIZONTAL};
		ScrollingType scrolling;

		std::list<PlataformParser> platformParser;
		std::list<PlataformParser>::iterator platformParserIterator;
		std::list<Platform*> platforms;
		std::list<Platform*>::iterator platformsIterator;

        Enemy* enemy;

};

#endif /* SRC_LEVEL_HH_ */
