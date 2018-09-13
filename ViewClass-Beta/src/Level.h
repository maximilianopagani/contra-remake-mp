/*
 * Level.h
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#ifndef SRC_LEVEL_H_
#define SRC_LEVEL_H_

#include "GameView.h"
#include "Sprite.h"

enum LevelNumber {LEVEL1, LEVEL2, LEVEL3};

class Level
{
	public:

		Level(GameView* gameView, LevelNumber _level);

		void render();
		void destroy();
		void updateCamera(int playerPosX, int playerPosY);

		virtual ~Level();

	private:

		GameView* gameView;
		Sprite* sprite;

//		int border;

		int posX, posY;
		int playerSpawnX, playerSpawnY;

		enum ScrollingType {SCROLLING_VERTICAL, SCROLLING_HORIZONTAL};
		ScrollingType scrolling;

		//TODO crear lista de plataformas y mostros

};

#endif /* SRC_LEVEL_H_ */
