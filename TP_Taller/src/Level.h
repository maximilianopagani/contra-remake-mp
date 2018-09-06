/*
 * Level.h
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#ifndef SRC_LEVEL_H_
#define SRC_LEVEL_H_

#include "Grapher.h"

enum ScrollingType {VERTICAL, HORIZONTAL};

class Level
{
	public:

		Level(ScrollingType _scrolling);

		void render();
		void clean();
		void updateCamera(int playerPosX, int playerPosY);
		int getCameraPos() { return renderRect.x; }
		int getMapWidth() { return mapWidth; }
		int getMapHeight() { return mapHeight; }

		virtual ~Level();

	private:

		int mapWidth, mapHeight, border;

		SDL_Rect renderRect;

		ScrollingType scrolling;

		SDL_Texture* background1;
		//SDL_Texture* background2;
		//SDL_Texture* background3;

};

#endif /* SRC_LEVEL_H_ */
