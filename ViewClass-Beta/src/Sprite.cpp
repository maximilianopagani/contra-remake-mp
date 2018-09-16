/*
 * Sprite.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "Sprite.hh"

Sprite::Sprite(GameView* _gameView, std::string path, int _source_rect_width, int _source_rect_height, int _dest_rect_width, int _dest_rect_height)
{
	gameView = _gameView;

	destinationWidth = _dest_rect_width;
	destinationHeight = _dest_rect_height;

	texture = gameView->textureGenerator(path.c_str());

	gameView->queryTexture(texture, &textureWidth, &textureHeight);

	src.x = 0;
	src.y = 0;
	src.w = _source_rect_width;
	src.h = _source_rect_height;
}

Sprite::~Sprite()
{
	this->destroy();
}

void Sprite::render(int x, int y, bool applyOffset)
{
	if(!applyOffset || !gameView->outOfWindow(x, y)) // Si es el mapa (viene con applyOffset false) o si es otro objecto dentro de la ventana
	{
		gameView->draw(texture, &src, x, y, destinationWidth, destinationHeight, applyOffset);
	}
}

void Sprite::update()
{
	src.x = src.x + src.w;

	if(src.x >= textureWidth)
		src.x = 0;
}

void Sprite::destroy()
{
	SDL_DestroyTexture(texture);

	texture = NULL;
	gameView = NULL;
}

bool Sprite::collideWith(Sprite* other)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = src.x;
    rightA = src.x + src.w;
    topA = src.y;
    bottomA = src.y + src.h;

    //Calculate the sides of rect B
    leftB = other->getSourceRectX();
    rightB = other->getSourceRectX() + other->getTextureWidth();
    topB = other->getSourceRectY();
    bottomB = other->getSourceRectY() + other->getTextureHeight();

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
        return false;
    if( topA >= bottomB )
        return false;
    if( rightA <= leftB )
        return false;
    if( leftA >= rightB )
        return false;

    //If none of the sides from A are outside B
    return true;
}





