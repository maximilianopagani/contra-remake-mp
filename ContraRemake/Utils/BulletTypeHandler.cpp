/*
 * BulletTypeHandler.cpp
 *
 *      Author: ldea
 */
#include "BulletTypeHandler.hh"

int BulletTypeHandler::getCooldown(BulletType type)
{
	switch(type)
	{
		case NORMAL:
			return 250;
		case MACHINEGUN:
			return 125;
		case TRIPLE:
			return 250;
	}
	return 0;
}

int BulletTypeHandler::getDistance(BulletType type)
{
	switch(type)
	{
		case NORMAL:
			return 375;
		case MACHINEGUN:
			return 425;
		case TRIPLE:
			return 400;
	}
	return 0;
}
