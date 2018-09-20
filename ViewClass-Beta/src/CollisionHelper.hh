/*
 * CollisionHelper.hh
 *
 *  Created on: Sep 19, 2018
 *      Author: pola17
 */

#ifndef COLLISIONHELPER_HH_
#define COLLISIONHELPER_HH_

#include "Sprite.hh"

class CollisionHelper
{
public:
	static bool collides(Sprite* aSprite, Sprite* otherSprite);
};

#endif /* COLLISIONHELPER_HH_ */
