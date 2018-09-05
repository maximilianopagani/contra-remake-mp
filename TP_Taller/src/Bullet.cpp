/*
 * Bullet.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: maximiliano
 */

#include "Bullet.h"

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

Bullet::Bullet(int posx, int posy, int speedx, int speedy, int distanceToTravel /* default = 0 (without limit)*/)
{
	pos_rect.h = 8;
	pos_rect.w = 8;
	pos_rect.x = posx;
	pos_rect.y = posy;
	speed_x = speedx;
	speed_y = speedy;
	traveled_distance = 0;
	max_travel_distance = distanceToTravel;
}

Bullet::~Bullet() {
}

void Bullet::move()
{
	pos_rect.x += speed_x;
	pos_rect.y += speed_y;
	traveled_distance += sqrt(pow(speed_x,2)+pow(speed_y,2));
}

bool Bullet::outOfLimits()
{
	if(pos_rect.x < 0 || pos_rect.x > Grapher::screenWidth || pos_rect.y < 0 || pos_rect.y > Grapher::screenHeight || (max_travel_distance > 0 && traveled_distance > max_travel_distance))
		return true;
	else
		return false;
}

void Bullet::checkCollision() {}

bool Bullet::render()
{
	if(!SDL_RenderCopy(Grapher::gameRenderer, source_texture, source_rect, &pos_rect))
		return true;
	else
	{
		printf("Unable to render bullet texture. SDL Error: %s\n", SDL_GetError());
		return false;
	}
}
