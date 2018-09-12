/*
 * Sprite.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "Sprite.h"

Sprite::Sprite(SDL_View* _view, std::string imagen, int w, int h, int wCLip, int hClip, int _maxWidth) {
	view =_view ;
	width = w ;
	height = h ;
	maxWidth= _maxWidth;
	imagenName = imagen;

	src.x = 0;
	src.y = 0;
	src.w = wCLip;
	src.h = hClip;
}

Sprite::~Sprite() {}

void Sprite::render(int x, int y){
	texture = view->textureGenerator(imagenName.c_str());
	view->rendering(texture,x,y,width,height,&src);

	this->update();
}
void Sprite::update(){
	src.x = src.x + src.w;
	if (src.x == maxWidth) src.x = 0;
}

