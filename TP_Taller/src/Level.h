/*
 * Level.h
 *
 *  Created on: Sep 6, 2018
 *      Author: maximiliano
 */

#ifndef SRC_LEVEL_H_
#define SRC_LEVEL_H_

#include "Grapher.h"

enum ScrollingType {SCROLLING_VERTICAL, SCROLLING_HORIZONTAL};

class Level
{
	public:

		Level(ScrollingType _scrolling);

		void render();
		void clean();
		void updateCamera(int playerPosX, int playerPosY);

		int getMapWidth() { return mapWidth; }
		int getMapHeight() { return mapHeight; }

		int getCameraPosX() { return renderRect.x; }
		int getCameraPosY() { return renderRect.y; }

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
