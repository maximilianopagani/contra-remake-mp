/*
 * CollisionObject.cpp
 *
 *  Created on: Sep 8, 2018
 *      Author: giova
 */

#include "CollisionObject.h"
#include <iostream>
#include <math.h>
/*
 * Calculo de la distancia critica,cuál es la distancia límite a la que pueden estar
 * Por ejemplo:
 *
    Jugador: 59×42
    Enemigo: 50×40

	El centro de cada uno de ellos debe estar desplazado de la posición en la que están
	dibujados (teniendo en cuenta que SDL dibuja desde la posición superior izquierda del
 	objeto):

    Jugador: (30,21)
    Enemigo: (25,20)
 *
 *
 * */

CollisionObject::CollisionObject() {}

CollisionObject::~CollisionObject() {}

bool CollisionObject:: CharacterCollision(Personaje* player , ObjectGame* enemy){

	//En posicion (0,0) el personaje tiene centro en (32,32)
	//Sumo 32 a las posiciones para actualizar el centro si es imagen de 64x64
	float playerCenter_x = player->getPositionX() + 32 ;
	float playerCenter_y = player->getPositionY() + 32;
	//Para hacerlo mas generico cada objeto deberia darme su Ancho y alto y asi
	//Reemplazar la constante de 32
	float enemyCenter_x = enemy->getPosX() + 32 ;
	float enemyCenter_y = enemy->getPosY() + 32 ;
	float distance;

	//Calculo la distancia
	distance=sqrt(pow(playerCenter_x-
			enemyCenter_x,2)+pow(playerCenter_y -enemyCenter_y,2));

	//std::cout<<"valor de la distancia :"<<distance<<std::endl;

	//Distancia minima entre objetos deliveradamente 32
	if (distance < 32 ) return true ;

	return false;

}

bool CollisionObject:: BulletCollision(Bullet* bullet , ObjectGame* enemy){

	//En posicion (0,0) el personaje tiene centro en (32,32)
	//Sumo 32 a las posiciones para actualizar el centro si es imagen de 64x64
	float playerCenter_x = bullet->getPosX() + 32 ;
	float playerCenter_y = bullet->getPosY() + 32;
	//Para hacerlo mas generico cada objeto deberia darme su Ancho y alto y asi
	//Reemplazar la constante de 32
	float enemyCenter_x = enemy->getPosX() + 32 ;
	float enemyCenter_y = enemy->getPosY() + 32 ;
	float distance;

	//Calculo la distancia
	distance=sqrt(pow(playerCenter_x-
			enemyCenter_x,2)+pow(playerCenter_y -enemyCenter_y,2));

	//std::cout<<"valor de la distancia :"<<distance<<std::endl;

	//Distancia minima entre objetos deliveradamente 32
	if (distance < 15 ) return true ;

	return false;

}

