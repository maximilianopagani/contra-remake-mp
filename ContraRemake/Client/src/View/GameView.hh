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

#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

class GameView
{
	public:

		GameView();
		virtual ~GameView();

		bool init();
		void clear();
		void delay(int milisecs);
		void draw(SDL_Texture* texture, SDL_Rect* src, int posXinCamera, int posYinCamera , int width, int height);
		void show();

		SDL_Texture* textureGenerator(std::string path);

		void destroy();
		void queryTexture(SDL_Texture* texture, int* widthResponse, int* heightResponse);

		Uint32 getTicks() { return SDL_GetTicks(); }

	private:

		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* invalidTexture;
};

#endif /* GAMEVIEW_H_ */
