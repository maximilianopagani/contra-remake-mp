/*
 * SDLView.h
 *      Author: giova
 */
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../Utils/Logger.hh"

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
		SDL_Texture* textTextureGenerator(std::string text, SDL_Color textColor);

		void showWindow() { SDL_ShowWindow(window); }

		void destroy();
		void queryTexture(SDL_Texture* texture, int* widthResponse, int* heightResponse);

		Uint32 getTicks() { return SDL_GetTicks(); }

		void showDisconnectedScreen();
		void showAlreadyConnectedScreen();
		void showGameFullScreen();
		void showInvalidLoginScreen();
		void showWaitingPlayersScreen();
		void showServerClosedScreen();
		void showGameOverScreen();
		void showVictoryScreen();

	private:

		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* invalidTexture;
		SDL_Texture* waitingPlayersTexture;
		SDL_Texture* disconnectedTexture;
		SDL_Texture* invalidLoginTexture;
		SDL_Texture* gameFullTexture;
		SDL_Texture* alreadyConnectedTexture;
		SDL_Texture* serverClosedTexture;
		SDL_Texture* gameOverTexture;
		SDL_Texture* victoryTexture;
};

#endif /* GAMEVIEW_H_ */
