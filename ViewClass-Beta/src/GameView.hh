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
		void draw(SDL_Texture* texture, SDL_Rect* src, int posX, int posY , int width, int height, bool applyOffset = true);
		void show();
		SDL_Texture* textureGenerator(std::string path);
		void destroy();
		void queryTexture(SDL_Texture* texture, int* width, int* height);

		int getCameraPosX() { return camera_x_position; }
		int getCameraPosY() { return camera_y_position; }

		void setCameraPosX(int x) { camera_x_position = x; }
		void setCameraPosY(int y) { camera_y_position = y; }
		void setCameraPosXY(int x, int y) { camera_x_position = x; camera_y_position = y; }

		Uint32 getTicks() { return SDL_GetTicks(); }

		int getWindowWidth() { return windowWidth; }
		int getWindowHeight() { return windowHeight; }

		//void setLimitXY(int _limitX, int _limitY) { limitX = _limitX; limitY = _limitY; }

		bool outOfWindowHigherBorder(int y) { return ((y - camera_y_position) < 20) ? true : false; } // Chequea para la posicion absoluta del parametro, si luego del ajuste del offset se escapa del borde superior de la ventana
		bool outOfWindowLowerBorder(int y) { return ((y - camera_y_position) > (windowHeight - 20)) ? true : false; } // Idem pero para borde inferior
		bool outOfWindowRightBorder(int x) { return ((x - camera_x_position) > (windowWidth - 20)) ? true : false; } // Idem pero para borde derecho
		bool outOfWindowLeftBorder(int x) { return ((x - camera_x_position) < 10) ? true : false; } // Idem pero para borde izquierdo

		bool outOfWindow(int x, int y); // Chequea para todas lados (todas las condiciones anteriores juntas). Util para evitar renderizar algo que no salga en la ventana, o para controlar que el movimiento no exceda los limites

	private:

		SDL_Window* window;
		SDL_Renderer* renderer;

		SDL_Rect rectToDraw;

		int windowWidth, windowHeight;
		//int limitX, limitY;
		int camera_x_position, camera_y_position;
};

#endif /* GAMEVIEW_H_ */
