/*
 * CollisionHelper.hh
 *
 *  Created on: Sep 19, 2018
 *      Author: pola17
 */
#include "Player.hh"
#include "Platform.hh"

#ifndef COLLISIONHELPER_HH_
#define COLLISIONHELPER_HH_

#include "Sprite.hh"

class CollisionHelper
{
public:
	static bool collides(Sprite* aSprite, Sprite* otherSprite);
	static bool CharacterCollision(Player* player , Platform* plataform);
};

#endif /* COLLISIONHELPER_HH_ */
