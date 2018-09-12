/*
 * SDLView.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: Giova
 */

#include "SDLView.h"

SDL_View::SDL_View() {}

SDL_View::~SDL_View() {}

bool SDL_View::initLoader(){
	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}
	else {
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			return false;
		}
	}
	//Create Renderer
	render = SDL_CreateRenderer(window, -1, 2);
	SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;

	if(!(IMG_Init(imgFlags) & imgFlags)){
		printf("SDL_Image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}
	return true;
}

void SDL_View::clear(){
	SDL_RenderClear(render);
}

void SDL_View::rendering(SDL_Texture* textureew, int x, int y, int w ,int h, SDL_Rect* src){
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	SDL_RenderCopy(render,textureew,src,&dest);
}
void SDL_View::show(){
	SDL_RenderPresent(render);
}
void SDL_View::delay(int milisegundos){
	SDL_Delay(milisegundos);
}

SDL_Texture* SDL_View::textureGenerator(std::string path){
		SDL_Texture* texture = NULL;
		SDL_Surface* surface = IMG_Load(path.c_str());

		if(surface == NULL){
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());

			//ACA PONER UNA IMAGEN POR DEFECTO CUANDO NOS QUITAN UNA IMAGEN PARA LAS PRUEBAS
		}
		else{
			texture = SDL_CreateTextureFromSurface(render, surface);

			if(texture == NULL)
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			else
				printf("Texture from image %s loaded successfully.\n", path.c_str());

			SDL_FreeSurface(surface);
		}
		return texture;
}

void SDL_View::clean(){
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow( window );
	SDL_Quit();
}

