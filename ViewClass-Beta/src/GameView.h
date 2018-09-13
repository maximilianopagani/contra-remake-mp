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

class GameView {
public:
	GameView();
	virtual ~GameView();

	bool init();
	void clear();
	void delay(int miliseconds);
	void draw(SDL_Texture* texturee, SDL_Rect* src, int posX, int posY ,int width ,int height);
	void show();
	SDL_Texture* textureGenerator(std::string path);
	void destroy();
	void queryTexture(SDL_Texture* texture,int* width, int* height);

	void setCameraPosition(int posX, int posY){
		camera_x_position = posX;
		camera_y_position = posY;
	}

	Uint32 getTricks() { return SDL_GetTicks();}
	int getWidth(){	return windowWidth;}
	int getHeight(){ return windowHeight;}

private:
	SDL_Window* window;
	SDL_Renderer* render;
	int windowWidth, windowHeight, camera_x_position, camera_y_position;
};

#endif /* GAMEVIEW_H_ */
