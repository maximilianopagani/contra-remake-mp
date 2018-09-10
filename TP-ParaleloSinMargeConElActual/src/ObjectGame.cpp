/*
 * ObjectGame.cpp
 *
 *  Created on: Sep 8, 2018
 *      Author: giova
 */

#include "ObjectGame.h"
#include "Grapher.h"
#include "Level.h"

ObjectGame::ObjectGame() {

	renderTexture = Grapher::loadTexture("imagenes/mob.png");
	pos_x = 600 ;
	pos_y = 225 ;

	renderRect.x = pos_x;
	renderRect.y = pos_y;
	renderRect.h = 64;
	renderRect.w = 64 ;
}

ObjectGame::~ObjectGame() {}


void ObjectGame::update(int posCam){

	renderRect.x = pos_x - posCam ;
	//renderTexture = Grapher::loadTexture("imagenes/mob.png");

}
void ObjectGame::render(){
	SDL_RenderCopy(Grapher::gameRenderer, renderTexture, NULL, &renderRect);
}
void ObjectGame::clean(){
	SDL_DestroyTexture(renderTexture);
}

void recorrido(){

}
void ObjectGame::gotCollision(){
	renderTexture = Grapher::loadTexture("imagenes/mobdown.png");
}

