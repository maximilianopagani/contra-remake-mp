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
		case RIFLE:
			return 500;
		case MACHINEGUN:
			return 125;
		case SPREAD:
			return 250;
		case LASER:
			return 750;
	}
	return 0;
}

int BulletTypeHandler::getDistance(BulletType type)
{
	switch(type)
	{
		case RIFLE:
			return 375;
		case MACHINEGUN:
			return 425;
		case SPREAD:
			return 400;
		case LASER:
			return 525;
	}
	return 0;
}
