/*
 * Level.h
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#ifndef MODEL_LEVEL_HH_
#define MODEL_LEVEL_HH_

#include "../../../Utils/GameParser.hh"
#include "../../../Utils/PlatformParser.hh"
#include "Platform.hh"
#include "Enemy.hh"
#include "CameraLogic.hh"

enum LevelNumber {LEVEL1, LEVEL2, LEVEL3};

class Level
{
	public:

		Level(GameParser* gameParser, CameraLogic* _cameraLogic, LogicToViewTransporter* _logicToViewTransporter, LevelNumber _level);
		virtual ~Level();

		void render();
		void destroy();
		void moveForward(int playerPosX, int playerPosY);

		int getSpawnPointX() { return playerSpawnX; }
		int getSpawnPointY() { return playerSpawnY; }

		list<Platform*>* getPlataformList(){ return &platforms; }

		void restart();

	private:

		CameraLogic* cameraLogic;
		LogicToViewTransporter* logicToViewTransporter;

		int background1PosX, background1PosY, background1Width, background1Height;
		int background2PosX, background2PosY, background2Width, background2Height; // no seria necesario si todas las capas fuesen del mismo tamaño
		int background3PosX, background3PosY, background3Width, background3Height;

		int playerSpawnX, playerSpawnY, border;

		enum ScrollingType {SCROLLING_VERTICAL, SCROLLING_HORIZONTAL};
		ScrollingType scrolling;

		std::list<PlataformParser> platformParser;
		std::list<PlataformParser>::iterator platformParserIterator;
		std::list<Platform*> platforms;
		std::list<Platform*>::iterator platformsIterator;

        Enemy* enemy;

};

#endif /* MODEL_LEVEL_HH_ */
