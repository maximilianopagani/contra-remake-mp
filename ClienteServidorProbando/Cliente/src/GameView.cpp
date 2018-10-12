/*
 * SDLView.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: Giova
 */

#include "GameView.hh"
//#include "Utils/Utils.hh"
//#include "../Utils/Logger.hh"
//#include "../Utils/GameParser.hh"

GameView::GameView()
{
	window = NULL;
	renderer = NULL;
	invalidTexture = NULL;
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
		//LOGGER_ERROR("No se ha podido inicializar SDL - SDL_Error: " + error_desc);
		return false;
	}
	else
	{
		//LOGGER_INFO("SDL inicializado con éxito.");

		window = SDL_CreateWindow("Contra Remake - Taller de Programación I", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

		if(window == NULL)
		{
			error_desc = SDL_GetError();
			//LOGGER_ERROR("Imposible crear la ventana - SDL_Error: " + error_desc);
			return false;
		}
		else
		{
			//LOGGER_INFO("Ventana creada con éxito.");
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if(renderer == NULL)
		{
			error_desc = SDL_GetError();
			//LOGGER_ERROR("Imposible crear el rendererer - SDL_Error: " + error_desc);
			return false;
		}
		else
		{
			//LOGGER_INFO("Renderer creado con éxito.");
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		//Initialize PNG loading

		int imgFlags = IMG_INIT_PNG;

		if(!(IMG_Init(imgFlags) & imgFlags))
		{
			error_desc = IMG_GetError();
			//LOGGER_ERROR("Imposible inicializar SDL_Image - SDL_Image_Error: " + error_desc);
			return false;
		}
		else
		{
			//LOGGER_INFO("SDL_Image inicializado con éxito.");
		}
	}

	invalidTexture = textureGenerator(".images/ImageNotFound.png");
	if(invalidTexture == NULL)
	{
		//LOGGER_ERROR("Imposible cargar imágen invalida para usar ante eventuales fallas en el generador de textura");
		// return false; ??? ANULAR EJECUCION DEL JUEGO??
	}
	return true;
}

void GameView::clear()
{
	SDL_RenderClear(renderer);
}

void GameView::draw(SDL_Texture* texture, SDL_Rect* src, int posXinCamera, int posYinCamera, int width, int height)
{
	SDL_Rect rectToDraw;

	rectToDraw.x = posXinCamera;
	rectToDraw.y = posYinCamera;
	rectToDraw.w = width;
	rectToDraw.h = height;

	SDL_RenderCopy(renderer, texture, src, &rectToDraw);
}

void GameView::show()
{
	SDL_RenderPresent(renderer);
}

void GameView::queryTexture(SDL_Texture* texture, int* widthResponse, int* heightResponse)
{
	SDL_QueryTexture(texture, NULL, NULL, widthResponse, heightResponse);
}

void GameView::delay(int milisecs)
{
	SDL_Delay(milisecs);
}

SDL_Texture* GameView::textureGenerator(std::string path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());

	//LOGGER_INFO("Cargando imágen... " + path);

	if(surface == NULL)
	{
		//LOGGER_ERROR("Imposible cargar " + path + " - SDL_Image_Error: " + IMG_GetError() + " - ACCION: Se carga textura invalida en su lugar.");
		return invalidTexture;
	}
	else
	{
		//LOGGER_INFO("Imagen " + path + " cargada con éxito. Creando textura a partir de ésta...");

		texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_FreeSurface(surface);

		if(texture == NULL)
		{
			//LOGGER_ERROR("Imposible crear textura de " + path + " - SDL_Error: " + SDL_GetError() + " - ACCION: Se carga textura invalida en su lugar.");
			return invalidTexture;
		}
		else
		{
			//LOGGER_INFO("Textura de imagen " + path + " creada con éxito.");
		}
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

