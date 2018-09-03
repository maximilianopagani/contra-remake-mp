/*
 * Personaje.h
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */

#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Juego.h"

class Personaje {
public:
	Personaje(const char* nombre,SDL_Renderer* ren);
	virtual ~Personaje();

	void actualizar();
	void renderizar();
	void eventos(SDL_Event evento);
	void limpiar();

	void saltando();
	void caminando();
	void setCondicion(bool _rebote){ rebote = _rebote;}


private:
	int posX;
	int posY;
	int pos;
	int posCaminando;
	bool rebote;
	char* spriteNames[4];
	char* spriteCaminando[4];

	SDL_Texture* personajeTextura;
	SDL_Rect srcRect ,desRect;
	SDL_Renderer* renderer;
};

#endif /* PERSONAJE_H_ */
