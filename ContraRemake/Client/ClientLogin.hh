/*
 * ClientLogin.hh
 *
 *  Created on: 14 oct. 2018
 *      Author: nacho
 */

#ifndef CLIENT_SRC_CLIENTLOGIN_HH_
#define CLIENT_SRC_CLIENTLOGIN_HH_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "ClientHandler.hh"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Texture {
public:
	Texture();
	~Texture();

	bool loadFromFile(std::string path);
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor,
			bool isPassword);

	void free();
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
			SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	SDL_Texture* texture;

	int width;
	int height;
};

bool clientLogin(ClientHandler* client, Sound* sound);

bool init();

bool loadMedia();

void close();

SDL_Texture* loadTexture(std::string path);

extern SDL_Window* window;

extern SDL_Renderer* renderer;

extern TTF_Font *font;
extern TTF_Font *passwordFont;

extern Texture splashTexture;
extern Texture userTexture;
extern Texture passwordTexture;
extern Texture serverTexture;
extern Texture portTexture;
extern Texture buttonTexture;
extern Texture promptTexture;

#endif /* CLIENT_SRC_CLIENTLOGIN_HH_ */
