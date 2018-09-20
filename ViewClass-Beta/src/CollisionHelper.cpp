/*
 * CollisionHelper.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: pola17
 */

#include "CollisionHelper.hh"

bool CollisionHelper::collides(Sprite* aSprite, Sprite* otherSprite)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = aSprite->getSourceRectX();
    rightA = aSprite->getSourceRectX() + aSprite->getTextureWidth();
    topA = aSprite->getSourceRectY();
    bottomA = aSprite->getSourceRectY() + aSprite->getTextureHeight();

    //Calculate the sides of rect B
    leftB = otherSprite->getSourceRectX();
    rightB = otherSprite->getSourceRectX() + otherSprite->getTextureWidth();
    topB = otherSprite->getSourceRectY();
    bottomB = otherSprite->getSourceRectY() + otherSprite->getTextureHeight();

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

bool CollisionHelper:: CharacterCollision(Player* player , Platform* plataform){

	//En posicion (0,0) el personaje tiene centro en (32,32)
	//Sumo 32 a las posiciones para actualizar el centro si es imagen de 64x64
	float playerCenter_x = player->getPosX() + 64 ;
	float playerCenter_y = player->getPosY() + 64;
	//Para hacerlo mas generico cada objeto deberia darme su Ancho y alto y asi
	//Reemplazar la constante de 32
	float enemyCenter_x = plataform->getPosX() + 48 ;
	float enemyCenter_y = plataform->getPosY() + 16 ;
	float distance;

	//Calculo la distancia
	distance=sqrt(pow(playerCenter_x-
			enemyCenter_x,2)+pow(playerCenter_y -enemyCenter_y,2));

	//std::cout<<"valor de la distancia :"<<distance<<std::endl;

	//Distancia minima entre objetos deliveradamente 32
	if (distance < 16 ) return true ;

	return false;

}
