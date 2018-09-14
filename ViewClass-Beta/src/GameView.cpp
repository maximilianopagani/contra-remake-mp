/*
 * SDLView.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: Giova
 */

#include "GameView.h"
#include "Headers.h"

GameView::GameView() {
	window = NULL;
	render = NULL;
	windowHeight = 600;
	windowWidth = 800;
	camera_x_position = 0;
	camera_y_position = 0;
}

GameView::~GameView() {
	destroy();
}

bool GameView::init(){
	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		string error = SDL_GetError();
		LOGGER_ERROR("SDL could not initialize! SDL_Error: " + error);
		return false;
	}
	else {
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			string error = SDL_GetError();
			LOGGER_ERROR("Window could not be created! SDL_Error: " + error);
			return false;
		}
	}
	//Create Renderer
	render = SDL_CreateRenderer(window, -1, 2);
	SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;

	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		string error = IMG_GetError();
		LOGGER_ERROR("SDL_Image could not initialize! SDL_image Error: " + error);
		return false;
	}
	return true;
}

void GameView::clear(){
	SDL_RenderClear(render);
}

void GameView::draw(SDL_Texture* texture, SDL_Rect* src, int posX, int posY, int width ,int height){
	SDL_Rect dest;
	dest.x = posX - camera_x_position;
	dest.y = posY;
	dest.w = width;
	dest.h = height;

	SDL_RenderCopy(render,texture,src,&dest);
}

void GameView::show(){
	SDL_RenderPresent(render);
}

void GameView::queryTexture(SDL_Texture* texture,int* width ,int* height){
	SDL_QueryTexture(texture, NULL, NULL, width, height);
}

void GameView::delay(int milisegundos){
	SDL_Delay(milisegundos);
}

SDL_Texture* GameView::textureGenerator(std::string path){
		SDL_Texture* texture = NULL;
		SDL_Surface* surface = IMG_Load(path.c_str());

		if(surface == NULL)
		{
			string error = IMG_GetError();
			LOGGER_ERROR("Unable to load image " + path + " SDL_image Error: " + error);
			//ACA PONER UNA IMAGEN POR DEFECTO CUANDO NOS QUITAN UNA IMAGEN PARA LAS PRUEBAS
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(render, surface);

			if(texture == NULL) {
				LOGGER_ERROR("Unable to create texture from " + path + " SDL Error: " + SDL_GetError());
			}
			else {
				LOGGER_INFO("Texture from image " + path + " loaded successfully.");
			}

			SDL_FreeSurface(surface);
		}

		return texture;
}

void GameView::destroy(){
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

