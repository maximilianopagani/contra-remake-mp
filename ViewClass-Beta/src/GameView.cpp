/*
 * SDLView.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: Giova
 */

#include "GameView.h"
#include "Headers.h"

GameView::GameView()
{
	window = NULL;
	renderer = NULL;
	windowHeight = 600;
	windowWidth = 800;
	camera_x_position = 0;
	camera_y_position = 0;
}

GameView::~GameView()
{
	destroy();
}

bool GameView::init()
{
	string error_desc;

	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_EVENTS) != 0)
	{
		error_desc = SDL_GetError();
		LOGGER_ERROR("No se ha podido inicializar SDL - SDL_Error: " + error_desc);
		return false;
	}
	else
	{
		LOGGER_INFO("SDL inicializado con éxito.");

		window = SDL_CreateWindow("Contra Remake - Taller de Programación I", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

		if(window == NULL)
		{
			error_desc = SDL_GetError();
			LOGGER_ERROR("Imposible crear la ventana - SDL_Error: " + error_desc);
			return false;
		}
		else
		{
			LOGGER_INFO("Ventana creada con éxito.");
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if(renderer == NULL)
		{
			error_desc = SDL_GetError();
			LOGGER_ERROR("Imposible crear el rendererer - SDL_Error: " + error_desc);
			return false;
		}
		else
		{
			LOGGER_INFO("Renderer creado con éxito.");
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		//Initialize PNG loading

		int imgFlags = IMG_INIT_PNG;

		if(!(IMG_Init(imgFlags) & imgFlags))
		{
			error_desc = IMG_GetError();
			LOGGER_ERROR("Imposible inicializar SDL_Image - SDL_Image_Error: " + error_desc);
			return false;
		}
		else
		{
			LOGGER_INFO("SDL_Image inicializado con éxito.");
		}
	}

	return true;
}

bool GameView::outOfWindow(int x, int y)
{
	// Esto chequea para la posicion absoluta pasada por parametro, si luego del ajuste del offset queda dentro o fuera de la ventana
	if((x - camera_x_position) > (windowWidth - 20) || (x - camera_x_position) < 10 || (y - camera_y_position) < 20 || (y - camera_y_position) > (windowHeight - 20))
		return true;
	else
		return false;
}

void GameView::clear()
{
	SDL_RenderClear(renderer);
}

void GameView::draw(SDL_Texture* texture, SDL_Rect* src, int posX, int posY, int width, int height, bool applyOffset)
{
	if(applyOffset)
	{
		rectToDraw.x = posX - camera_x_position;
		rectToDraw.y = posY - camera_y_position;
	}
	else
	{
		rectToDraw.x = posX;
		rectToDraw.y = posY;
	}

	rectToDraw.w = width;
	rectToDraw.h = height;

	SDL_RenderCopy(renderer, texture, src, &rectToDraw);
}

void GameView::show()
{
	SDL_RenderPresent(renderer);
}

void GameView::queryTexture(SDL_Texture* texture, int* width, int* height)
{
	SDL_QueryTexture(texture, NULL, NULL, width, height);
}

void GameView::delay(int milisecs)
{
	SDL_Delay(milisecs);
}

SDL_Texture* GameView::textureGenerator(std::string path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());

	if(surface == NULL)
	{
		LOGGER_ERROR("Imposible cargar " + path + " - SDL_Image_Error: " + IMG_GetError());
		//ACA PONER UNA IMAGEN POR DEFECTO CUANDO NOS QUITAN UNA IMAGEN PARA LAS PRUEBAS
	}
	else
	{
		LOGGER_INFO("Imagen " + path + " cargada con éxito.");

		texture = SDL_CreateTextureFromSurface(renderer, surface);

		if(texture == NULL)
		{
			LOGGER_ERROR("Imposible crear textura de " + path + " - SDL_Error: " + SDL_GetError());
		}
		else
		{
			LOGGER_INFO("Textura de imagen " + path + " creada con éxito.");
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

void GameView::destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	renderer = NULL;
	window = NULL;

	SDL_Quit();
}

