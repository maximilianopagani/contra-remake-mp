/*
 * CollisionHelper.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: pola17
 */

#include "CollisionHelper.hh"

bool CollisionHelper::collides(Sprite* aSprite, Sprite* otherSprite)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = aSprite->getSourceRectX();
    rightA = aSprite->getSourceRectX() + aSprite->getTextureWidth();
    topA = aSprite->getSourceRectY();
    bottomA = aSprite->getSourceRectY() + aSprite->getTextureHeight();

    //Calculate the sides of rect B
    leftB = otherSprite->getSourceRectX();
    rightB = otherSprite->getSourceRectX() + otherSprite->getTextureWidth();
    topB = otherSprite->getSourceRectY();
    bottomB = otherSprite->getSourceRectY() + otherSprite->getTextureHeight();

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
