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
#include "Item.hh"
#include "Enemy.hh"
#include "Boss.hh"
#include "CameraLogic.hh"
#include "ServerMessageHandler.hh"

enum LevelNumber {LEVEL1, LEVEL2, LEVEL3};
enum ScrollingType {SCROLLING_VERTICAL, SCROLLING_HORIZONTAL};

class Level
{
	public:

		Level(CameraLogic* _cameraLogic, int _level, ServerMessageHandler* _serverMessageHandler, GameParser* _gameParser);
		virtual ~Level();

		void render();
		void destroy();
		void moveForward(int pixels_to_move);
		void update();
		void deleteEnemy(Enemy* _enemy);
		void deleteBoss();

		int getSpawnPointX() { return playerSpawnX; }
		int getSpawnPointY() { return playerSpawnY; }

		int getRespawnPointX() { return playerRespawnX; }
		int getRespawnPointY() { return playerRespawnY; }

		std::string getBackground1Path() { return background1Path; }
		std::string getBackground2Path() { return background2Path; }
		std::string getBackground3Path() { return background3Path; }

		int getBorder() { return border; }
		int getScrollingType() { return scrolling; }

		void loadPlatforms(std::list<PlataformParser>* platformParser);
		void loadItems(std::list<ItemParser>* itemParser);
		void loadEnemies(int runner_amount = 10, int rifleman_amount = 10);

		list<Platform*>* getPlatformsList() { return &platforms; }
		list<Enemy*>* getEnemiesList() { return &enemies; }
		list<Item*>* getItemsList() { return &items; }
		Boss* getBoss(){return boss;}

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

		std::list<Platform*> platforms;
		std::list<Platform*>::iterator platformsIterator;

		std::list<Item*> items;
		std::list<Item*>::iterator itemsIterator;

		std::list<Enemy*> enemies;
		std::list<Enemy*>::iterator enemiesIterator;

		Boss* boss;
};

#endif /* MODEL_LEVEL_HH_ */
