/*
 * Sprite.h
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDLView.h"
#include <list>

using namespace std;

#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite {
public:
	Sprite(SDL_View* view, std::string imagen, int w, int h, int wCLip, int hClip, int maxWidth);
	virtual ~Sprite();
	void render(int x , int y);
	void update();
private:
	int width, height, maxWidth;
	SDL_View* view = NULL;
	SDL_Texture* texture=NULL;
	SDL_Rect src;
	std::string imagenName;
};

#endif /* SPRITE_H_ */
