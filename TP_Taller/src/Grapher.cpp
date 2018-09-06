/*
 * Grapher.cpp
 *
 *  Created on: Sep 3, 2018
 *      Author: maximiliano
 */

#include "Grapher.h"

bool loadGrapher();

bool loadGrapher()
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_EVENTS) != 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		printf("SDL initialized successfully.\n");

		window = SDL_CreateWindow("Contra Remake - Taller de Programación I", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, Grapher::windowWidth, Grapher::windowHeight, SDL_WINDOW_SHOWN);

		if(window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else
			printf("Window created successfully.\n");

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if(renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else
			printf("Renderer created successfully.\n");

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;

		if(!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_Image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			return false;
		}
		else
			printf("SDL_Image initialized successfully.\n");
	}

	Grapher::setGameWindow(window);
	Grapher::setGameRenderer(renderer);

	Bullet::loadBulletsGraphicsResources();

	return true;
}

SDL_Window* Grapher::gameWindow = NULL;
SDL_Renderer* Grapher::gameRenderer = NULL;

int Grapher::windowWidth = 800;
int Grapher::windowHeight = 600;

void Grapher::setGameWindow(SDL_Window* windowToUse)
{
	gameWindow = windowToUse;
}

void Grapher::setGameRenderer(SDL_Renderer* rendererToUse)
{
	gameRenderer = rendererToUse;
}

SDL_Texture* Grapher::loadTexture(std::string path)
{
	SDL_Texture* texture = NULL;

	SDL_Surface* surface = IMG_Load(path.c_str());

	if(surface == NULL)
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	else
	{
		//printf("Image %s loaded successfully.\n", path.c_str());

		texture = SDL_CreateTextureFromSurface(gameRenderer, surface);

		if(texture == NULL)
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		else
			printf("Texture from image %s loaded successfully.\n", path.c_str());

		SDL_FreeSurface(surface);
	}

	return texture;
}
