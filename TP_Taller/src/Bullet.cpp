/*
 * Bullet.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: maximiliano
 */

#include "Bullet.h"

extern Level* gameLevel;

SDL_Rect* Bullet::source_rect = NULL;
SDL_Texture* Bullet::source_texture = NULL;

void Bullet::loadBulletsGraphicsResources()
{
	Bullet::setSourceRect();
	Bullet::setSourceTexture();
}

void Bullet::setSourceRect()
{
	source_rect = new SDL_Rect();
	source_rect->x = 104;
	source_rect->y = 8;
	source_rect->w = 8;
	source_rect->h = 8;
}

void Bullet::setSourceTexture()
{
	source_texture = Grapher::loadTexture("imagenes/CharacterSprites.png");
}

Bullet::Bullet(int _pos_x, int _pos_y, int _speed_x, int _speed_y, int distanceToTravel /* default = 0 (without limit)*/)
{
	pos_x = _pos_x;
	pos_y = _pos_y;

	speed_x = _speed_x;
	speed_y = _speed_y;

	traveled_distance = 0;
	max_travel_distance = distanceToTravel;

	render_rect.h = 8;
	render_rect.w = 8;
	render_rect.x = 0;
	render_rect.y = 0;
}

Bullet::~Bullet() {
}

void Bullet::move()
{
	pos_x += speed_x;
	pos_y += speed_y;

	traveled_distance += sqrt(pow(speed_x,2)+pow(speed_y,2));
}

bool Bullet::outOfLimits()
{
	if((max_travel_distance > 0 && traveled_distance > max_travel_distance) || pos_x < 0 || pos_x > gameLevel->getMapWidth() || render_rect.x > Grapher::windowWidth || pos_y < 0 || pos_y > gameLevel->getMapHeight() || render_rect.y > Grapher::windowHeight)
		return true;
	else
		return false;
}

void Bullet::checkCollision() {}

void Bullet::render()
{
	render_rect.x = pos_x - gameLevel->getCameraPosX(); // Ajuste de offset. Muevo la posicion absoluta global de la bala en el mapa a la relativa a la ventana
	render_rect.y = pos_y - gameLevel->getCameraPosY();

	SDL_RenderCopy(Grapher::gameRenderer, source_texture, source_rect, &render_rect);
}
