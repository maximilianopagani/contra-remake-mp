/*
 * SDLView.h
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

#ifndef SDLVIEW_H_
#define SDLVIEW_H_

class SDL_View {
public:
	SDL_View();
	virtual ~SDL_View();

	bool initLoader();
	void clear();
	void delay(int milisegundos);
	void rendering(SDL_Texture* texturee, int x, int y ,int w ,int h, SDL_Rect* src);
	void show();
	SDL_Texture* textureGenerator(std::string path);
	void clean();

private:
	SDL_Window* window = NULL;
	SDL_Renderer* render = NULL;
};

#endif /* SDLVIEW_H_ */
