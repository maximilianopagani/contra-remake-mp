/*
 * Boss.cpp
 *
 *  Created on: Nov 17, 2018
 *      Author: giova
 */

#include "Boss.hh"

Boss::Boss(CameraLogic* _cameraLogic, ServerMessageHandler* _serverMessageHandler, int _type, int pos_x, int pos_y) {
	serverMessageHandler = _serverMessageHandler;
	cameraLogic = _cameraLogic;

	//Boss stats
	posX = pos_x;
	posY = pos_y;
	vida=150;
	type = _type;
	state = 0;
	distanceToTravel = 800;

	//Configuro para el colisioner
	if(type == 0) {
		widht = 258;
		hight = 194 ;
	}
	if(type == 1) {
		widht = 504;
		hight = 208;
	}
	if(type == 2){
		widht = 99;
		hight = 112 ;
	}

	//Utiles
	fase= 0;
	contador=0;
	timeAtIterationStart = 0;
	proxFase = 0;
	amountToWait = 30 ;
	proxState=0;
	caer = 50;
	direccionY1 = 1;
	direccionY2 = 1 ;
	oneTime = true  ;
	dead = false;
	finishLevel = false ;
}

void Boss::render(){

	if(!dead && this->isOnScreen())
	{
	serverMessageHandler->sendToAllClients(new MessageServer(BOSS, RENDER,type,state, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY()));
	}

	for(bulletsIterator = bullets.begin(); bulletsIterator != bullets.end(); ++bulletsIterator)
	{
		(*bulletsIterator)->render(2);
	}
}
void Boss::update(){

	// Actualizacion de posicion de balas
	for(bulletsIterator = bullets.begin(); bulletsIterator != bullets.end();)
	{
	    (*bulletsIterator)->updatePos();

	    if((*bulletsIterator)->outOfLimits())
	    {
	        delete (*bulletsIterator);
	        bullets.erase(bulletsIterator++);
	    }
	    else
	    {
	        ++bulletsIterator;
	    }
	}

	// Movimiento del Boss.
	if(this->isOnScreen()){
		if(type == 0) updateBoss1();
		if(type == 1) updateBoss2();
	}

	if(type == 2) updateBoss3();
}

void Boss::updateBoss1(){

	if(oneTime){
		serverMessageHandler->sendToAllClients(new MessageServer(SOUND, LOAD, 1, 3));
		oneTime = false;
	}

	switch(fase){
		//Avanza
		case 0 :{
			state=1;

			timeAtIterationStart++;
			if(timeAtIterationStart > 2){
				serverMessageHandler->sendToAllClients(new MessageServer(BOSS, LOAD,type,state, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY()));
				timeAtIterationStart=0;
			}

			posX = moverPos(posX,7350,8);
			if( posX <= 7350 ){
				posX = 7350;

				proxFase = 1;

				state = 7;
				amountToWait=15;

				fase = 2;
			}
			break;
		}
		//Retrocede
		case 1 :{
			state=1;

			timeAtIterationStart++;
			if(timeAtIterationStart > 2){
				serverMessageHandler->sendToAllClients(new MessageServer(BOSS, LOAD,type,state, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY()));
				timeAtIterationStart=0;
			}

			posX = moverPos(posX,7750,8);
			if( posX >= 7750 ){
				posX = 7750;

				proxFase = 3;
				proxState = 2;
				direccionY1 = rand() % 10 + 1;
				direccionY2 = rand() % 10 + 1;

				state = 0;
				amountToWait=60;
				fase = 2;
			}
			break;
				}
		//Espera
		case 2 :{

			if( waiting(amountToWait) ){
				fase = proxFase;
				state = proxState;
				contador=0;
			}
			break;
		}
		//Ataca por el ojo
		case 3 :{
			if(waiting(15)) {
				state=3;

				bullets.push_back(new Bullet(cameraLogic, posX+111 , posY+34 ,-10, direccionY1, distanceToTravel,true, serverMessageHandler));
				bullets.push_back(new Bullet(cameraLogic, posX+111 , posY+34 ,-10, 0, distanceToTravel,true,serverMessageHandler));
				bullets.push_back(new Bullet(cameraLogic, posX+111 , posY+34 ,-10, -direccionY2, distanceToTravel,true,serverMessageHandler));

				if(waiting(35)) {
					proxFase = 0;

					amountToWait=60;
					fase = 2;
					contador = 0;
				}
			}
			break;
		}
		//Muerto
		case 4 :{
			state = 8 ;
			if(waiting(250)) finishLevel= true;
			break;
		}
	}

}
void Boss::updateBoss2(){

	if(oneTime){
		serverMessageHandler->sendToAllClients(new MessageServer(SOUND, LOAD, 1, 3));
		oneTime = false;
	}
	switch(fase){
		case 0:{
			state=1;

			timeAtIterationStart++;
			if(timeAtIterationStart > 2){
				serverMessageHandler->sendToAllClients(new MessageServer(BOSS, LOAD,type,state, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY()));
				timeAtIterationStart=0;
			}

			posY = moverPos(posY,100,4);
			if( posY >= 100 ){
				posY = 100;

				proxFase = 1;

				state = 2;
				amountToWait=15;

				fase = 2;
			}
			break;
		}
		case 1:{
			state=1;

			timeAtIterationStart++;
			if(timeAtIterationStart > 2){
				serverMessageHandler->sendToAllClients(new MessageServer(BOSS, LOAD,type,state, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY()));
				timeAtIterationStart=0;
			}

			posY = moverPos(posY,10,4);
			if( posY <= 10 ){
				posY = 10;

				proxFase = 3; // estado con el q estara despues de esperar
				proxState = 0; // estado con el q estara para disparar 0 no es deberia ser otro

				//numeros ramdon q haran disparar para algun lado
				direccionY1 = rand() % 10 + 1;
				direccionY2 = rand() % 10 + 1;

				state =0; // estado con el q va a  esperar
				amountToWait=60; //tiempo q va a esperar
				fase = 2; // mando a esperar
			}
			break;
		}
		//Espera
		case 2 :{

			if( waiting(amountToWait) ){
				fase = proxFase;
				state = proxState;
				contador=0;
			}
			break;
		}

		case 3 :{

			if(waiting(15)) {
				state=4;

				//dispara las pequeñas
				bullets.push_back(new Bullet(cameraLogic, posX+45 , posY+90 , direccionY1,10, distanceToTravel,true, serverMessageHandler));
				bullets.push_back(new Bullet(cameraLogic, posX+45 , posY+90 , -direccionY1 ,10, -distanceToTravel,true, serverMessageHandler));
				bullets.push_back(new Bullet(cameraLogic, posX+420 , posY+110 , direccionY2,10, distanceToTravel, true,serverMessageHandler));
				bullets.push_back(new Bullet(cameraLogic, posX+420 , posY+110 , -direccionY2,10, distanceToTravel, true,serverMessageHandler));

				if(waiting(35)) {
					//Dispara la grande
					bullets.push_back(new Bullet(cameraLogic, posX+240 , posY+90 ,direccionY1, 10, distanceToTravel,true, serverMessageHandler));
					bullets.push_back(new Bullet(cameraLogic, posX+240 , posY+90 ,-direccionY1, 10, distanceToTravel,true,serverMessageHandler));

					proxFase = 0;

					amountToWait=60;
					fase = 2;
					contador = 0;
				}
			}
			break;
		}

		//Muerto
		case 4 :{
			state = 5 ;
			if(waiting(250)) finishLevel= true;
			break;
		}
	}
}

void Boss::updateBoss3(){

	if(oneTime){
			serverMessageHandler->sendToAllClients(new MessageServer(SOUND, LOAD, 1, 3));
			oneTime = false;
		}

		switch(fase){
			//Avanza
			case 0 :{
				state=1;
				timeAtIterationStart++;
				if(timeAtIterationStart > 2){
					serverMessageHandler->sendToAllClients(new MessageServer(BOSS, LOAD,type,state, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY()));
					timeAtIterationStart=0;
				}

				posX = moverPos(posX,caer+7410,8);
				if( posX <= caer+7410 ){
					posX = caer+7410;

					fase = 2;
				}
				break;
			}
			//Retrocede
			case 1 :{
				state=1;

				timeAtIterationStart++;
				if(timeAtIterationStart > 2){
					serverMessageHandler->sendToAllClients(new MessageServer(BOSS, LOAD,type,state, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY()));
					timeAtIterationStart=0;
				}

				//Recordatorio: DesHarcodear las posiciones
				posX = moverPos(posX,7750,8);
				if( posX >= 7750 ){
					posX = 7750;

					direccionY1 = rand() % 10 + 1;
					direccionY2 = rand() % 10 + 1;

					fase = 3;
				}
				break;
					}
			//Abajo
			case 2 :{

				state=0;

				posY = moverPos(posY,400,16);
				if( posY >= 400 ){
					posY = 400;

					fase = 1;
				}
				break;

			}
			//Arriba
			case 3 :{

				state=1;
				timeAtIterationStart++;
				if(timeAtIterationStart > 2){
					serverMessageHandler->sendToAllClients(new MessageServer(BOSS, LOAD,type,state, posX - cameraLogic->getCameraPosX(), posY - cameraLogic->getCameraPosY()));
					timeAtIterationStart=0;
				}

				posY = moverPos(posY,40,8);
				if( posY <= 40 ){
					posY = 40;

					proxFase = 5;
					proxState = 0 ;

					state = 0;
					amountToWait=15;
					caer = 10+rand()%(701-10);

					fase = 6;
				}
				break;
			}
			//Muerto
			case 4 :{
				state = 4 ;
				if(waiting(250)) finishLevel= true;
				break;
			}
			//shoot
			case 5 :{

				if(waiting(15)) {
					state=3;

					bullets.push_back(new Bullet(cameraLogic, posX+49 , posY+56 , -direccionY1 ,10, distanceToTravel,true, serverMessageHandler));
					bullets.push_back(new Bullet(cameraLogic, posX+49 , posY+56 , -direccionY2 ,10, distanceToTravel,true, serverMessageHandler));

					if(waiting(40)) {
						fase = 0;
						contador = 0;
					}
				}
				break;
			}
			//Espera
			case 6 :{

				if( waiting(amountToWait) ){
					fase = proxFase;
					state = proxState;
					contador=0;
				}
				break;
			}
		}

}

bool Boss::waiting(int amount){
	if(contador > amount) 	return true;
	contador ++;
	return false;
}

int Boss::moverPos(int origin , int destiny , int paso){
	if(origin < destiny){
		origin += paso ;
	    if( origin >= destiny ) origin = destiny;

	}else if(origin > destiny){
		origin-= paso ;
	    if( origin <= destiny ) origin = destiny;
	}
	return origin;
}

void Boss::wasHit(){

	//Logica de cuando recibe danio el primer boss
	if(type == 0) {

		if(fase!=4 && fase!=0 && fase != 1 ) {
			serverMessageHandler->sendToAllClients(new MessageServer(SOUND,LOAD,2,0));
			vida--;
			state= 6 ;
			if(vida<=0) {
				vida=0;
				contador = 0;
			}
		}

	}
	//Logica de cuando recibe danio el segundo boss
	if(type == 1) {
		if(fase!=4) {
			serverMessageHandler->sendToAllClients(new MessageServer(SOUND,LOAD,2,0));
			vida--;
			state= 3;
			if(vida<=0) {
				vida=0;
				contador = 0;
			}
		}
	}
	//Logica de cuando recibe danio el tercer boss
	if(type == 2){
		if(fase!=4) {
			serverMessageHandler->sendToAllClients(new MessageServer(SOUND,LOAD,2,0));
			vida--;
			state= 2;
			if(vida<=0) {
				vida=0;
				contador = 0;
			}
		}
	}

}
bool Boss::bossIsDead(){
	fase = 4;
	return finishLevel;
}

int Boss::getLeftLimit()
{
	return posX + 15 ;
}

int Boss::getRightLimit()
{
	return (posX + widht - 15);
}

int Boss::getTopLimit()
{
	return posY;
}

int Boss::getBottomLimit()
{
	return posY + hight;
}

bool Boss::isDead() {
	return dead;
}

Boss::~Boss() {
	// TODO Auto-generated destructor stub
}

