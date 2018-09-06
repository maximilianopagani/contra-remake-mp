/*
 * Grapher.h
 *
 *  Created on: Sep 3, 2018
 *      Author: maximiliano
 */

#ifndef SRC_GRAPHER_H_
#define SRC_GRAPHER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Bullet.h" // Para aislar mejor este modulo, al iniciar el juego deberia cargarse el grapher, y si no hay errores
// proseguir con la carga de los recursos graficos de los distintos modulos/clases, y no realizar la carga dentro del grapher como ahora

class Grapher
{
	public:

		static int windowWidth, windowHeight;
		static SDL_Window* gameWindow;
		static SDL_Renderer* gameRenderer;
		static void setGameWindow(SDL_Window* windowToUse);
		static void setGameRenderer(SDL_Renderer* rendererToUse);
		static SDL_Texture* loadTexture(std::string path);

	private:

		Grapher() {};
};

#endif /* SRC_GRAPHER_H_ */
