/*
 * Sprite.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "Sprite.h"

Sprite::Sprite(GameView* _view, std::string imagen, int wCLip, int hClip, int _destinationWidth, int _destinationHeight) {
	view =_view ;
	manualMode = false;

	destinationWidth = _destinationWidth ;
	destinationHeight = _destinationHeight ;

	texture = view->textureGenerator(imagen.c_str());
	view->queryTexture(texture,&maxWidth,&maxHeight);

	src.x = 0;
	src.y = 0;
	src.w = wCLip;
	src.h = hClip;
}

Sprite::~Sprite() {}

void Sprite::render(int x, int y){
	view->draw(texture,&src,x,y,destinationWidth,destinationHeight);

	if(!manualMode ) this->update();
}
void Sprite::update(){
	src.x = src.x + src.w;
	if (src.x >= maxWidth) src.x = 0;
}

void Sprite::manualMod(){
	manualMode = true ;
}

void Sprite::setPostion(int x , int y){
	src.x = x ;
	src.y = y ;
}

void Sprite::destroy() {
	SDL_DestroyTexture(texture);
	this->view = nullptr;
}

