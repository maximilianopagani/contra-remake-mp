/*
 * CollisionHelper.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: pola17
 */

#include "CollisionHelper.hh"

bool CollisionHelper::collides(ICollisional* aCollisional, ICollisional* otherCollisional)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = aCollisional->getLeftLimit();
    rightA = aCollisional->getRightLimit();
    topA = aCollisional->getTopLimit();
    bottomA = aCollisional->getBottomLimit();

    //Calculate the sides of rect B
    leftB = otherCollisional->getLeftLimit();
    rightB = otherCollisional->getRightLimit();
    topB = otherCollisional->getTopLimit();
    bottomB = otherCollisional->getBottomLimit();

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

bool CollisionHelper::stands(ICollisional* stand, ICollisional* floor)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = stand->getLeftLimit();
    rightA = stand->getRightLimit();
    topA = stand->getTopLimit();
    bottomA = stand->getBottomLimit();

    //Calculate the sides of rect B
    leftB = floor->getLeftLimit();
    rightB = floor->getRightLimit();
    topB = floor->getTopLimit();
    bottomB = floor->getBottomLimit();

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
        return false;
    if( topA >= bottomB )
        return false;
    if( rightA <= leftB )
        return false;
    if( leftA >= rightB )
        return false;
    if( bottomA > bottomB )
        return false;

    //If none of the sides from A are outside B
    return true;
}
