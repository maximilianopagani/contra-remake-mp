/*
 * Boss.hh
 *
 *  Created on: Nov 17, 2018
 *      Author: giova
 */
#include "../../Utils/ICollisional.hh"
#include "../../Utils/MessageServer.hh"
#include "CameraLogic.hh"
#include "../../Utils/Logger.hh"
#include "ServerMessageHandler.hh"
#include "Bullet.hh"
#include "../../Utils/EnemyTypesAndStates.hh"

#ifndef SERVER_MODEL_BOSS_HH_
#define SERVER_MODEL_BOSS_HH_

class Boss: public ICollisional {
public:
	Boss(CameraLogic* _cameraLogic, ServerMessageHandler* _serverMessageHandler, int _type, int pos_x, int pos_y);
	virtual ~Boss();

	void render();
	void update();
	void wasHit();
	void updateBoss1();
	void updateBoss2();
	void updateBoss3();

	bool isOnScreen() { return !cameraLogic->outOfCameraLimits(posX, posY); }
	bool waiting(int amount);
	bool bossIsDead();

	list<Bullet*>* getBulletList() { return &bullets; }

	int getLife(){ return vida;}
	int moverPos(int origin , int destiny , int paso);

	//Collisional
	int getLeftLimit();
	int getRightLimit();
	int getTopLimit();
	int getBottomLimit();

private:
	ServerMessageHandler* serverMessageHandler;
	CameraLogic* cameraLogic ;

	// Manejo de balas
	std::list<Bullet*> bullets;
	std::list<Bullet*>::iterator bulletsIterator;

	int vida,fase,contador,proxFase,proxState,amountToWait,direccionY1,direccionY2,caer;
	bool finishLevel ,oneTime ,dead;
	int distanceToTravel,timeAtIterationStart,type,posX, posY, state;
	int widht ,hight ;

};

#endif /* SERVER_MODEL_BOSS_HH_ */
