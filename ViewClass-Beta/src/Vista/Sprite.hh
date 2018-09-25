/*
 * Sprite.h
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>

#include "GameView.hh"

using namespace std;

#ifndef SPRITE_HH_
#define SPRITE_HH_

class Sprite
{
	public:

		Sprite(GameView* view, std::string imagen, int _source_rect_width, int _source_rect_height, int _dest_rect_width, int _dest_rect_height);
		virtual ~Sprite();

		void render(int x , int y);
		void update();
		void destroy();

		int getSourceRectX() { return src.x; }
		int getSourceRectY() { return src.y; }

		void setSourceRectX(int x) { src.x = x; }
		void setSourceRectY(int y) { src.y = y; }
		void setSourceRectXY(int x, int y) { src.x = x; src.y = y; }

		int getTextureWidth() { return textureWidth; }
		int getTextureHeight() { return textureHeight; }
		int getDestinationWidth() { return destinationWidth; }
		int getDestinationHeight() { return destinationHeight; }

	private:

		int destinationHeight, destinationWidth;
		int textureWidth, textureHeight;

		GameView* gameView = NULL;
		SDL_Texture* texture = NULL;
		SDL_Rect src;
};

#endif /* SPRITE_HH_ */
