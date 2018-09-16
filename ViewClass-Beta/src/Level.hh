/*
 * Level.h
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#ifndef SRC_LEVEL_HH_
#define SRC_LEVEL_HH_

#include "GameView.hh"
#include "Parallax.hh"
#include "Platform.hh"
#include "Sprite.hh"

class Level
{
	public:

		Level(GameView* gameView, LevelNumber _level);

		void render();
		void destroy();
		void moveForward(int playerPosX, int playerPosY);

		//int getLevelWidth() { return sprite->getTextureWidth(); }
		//int getLevelHeight() { return sprite->getTextureHeight(); }

		int getSpawnPointX() { return playerSpawnX; }
		int getSpawnPointY() { return playerSpawnY; }

		void restart();

		virtual ~Level();

	private:

		GameView* gameView;
		Sprite* sprite;
		Parallax* parallax;

		int playerSpawnX, playerSpawnY, border;

		enum ScrollingType {SCROLLING_VERTICAL, SCROLLING_HORIZONTAL};
		ScrollingType scrolling;

		std::list<Platform*> platforms;
		std::list<Platform*>::iterator platformsIterator;

		//std::list<Enemy*> enemies;
		//std::list<Enemy*>::iterator enemiesIterator;

		//TODO crear lista de plataformas y mostros

};

#endif /* SRC_LEVEL_HH_ */
