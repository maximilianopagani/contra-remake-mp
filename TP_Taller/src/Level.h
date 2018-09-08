/*
 * Level.h
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#ifndef SRC_LEVEL_H_
#define SRC_LEVEL_H_

#include "Grapher.h"

enum LevelNumber {LEVEL1, LEVEL2, LEVEL3};

class Level
{
	public:

		Level(LevelNumber _level);

		void render();
		void clean();
		void updateCamera(int playerPosX, int playerPosY);

		int getMapWidth() { return mapWidth; }
		int getMapHeight() { return mapHeight; }

		int getCameraPosX() { return renderRect.x; }
		int getCameraPosY() { return renderRect.y; }

		int getPlayerSpawnX() { return playerSpawnX; }
		int getPlayerSpawnY() { return playerSpawnY; }

		virtual ~Level();

	private:

		int mapWidth, mapHeight, border;

		int playerSpawnX, playerSpawnY;

		SDL_Rect renderRect;

		enum ScrollingType {SCROLLING_VERTICAL, SCROLLING_HORIZONTAL};
		ScrollingType scrolling;

		SDL_Texture* background1;
		//SDL_Texture* background2;
		//SDL_Texture* background3;

};

#endif /* SRC_LEVEL_H_ */
