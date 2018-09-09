/*
 * CollisionObject.h
 *
 *  Created on: Sep 8, 2018
 *      Author: giova
 */
#include "ObjectGame.h"
#include "Personaje.h"
#include "Bullet.h"

#ifndef SRC_COLLISIONOBJECT_H_
#define SRC_COLLISIONOBJECT_H_

class CollisionObject {
public:
	CollisionObject();
	virtual ~CollisionObject();
	static bool CharacterCollision(Personaje* player , ObjectGame* enemy);
	static bool BulletCollision(Bullet* bullet , ObjectGame* enemy);

};

#endif /* SRC_COLLISIONOBJECT_H_ */
