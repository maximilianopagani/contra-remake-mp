/*
 * CollisionHelper.hh
 *
 *  Created on: Sep 19, 2018
 *      Author: pola17
 */

#ifndef COLLISIONHELPER_HH_
#define COLLISIONHELPER_HH_

#include "ICollisional.hh"
#include  "../Model/Platform.hh"

class CollisionHelper
{
public:

	static bool collides(ICollisional* aCollisional, ICollisional* otherCollisional);
	static bool stands(ICollisional* stand, ICollisional* floor);

};

#endif /* COLLISIONHELPER_HH_ */
