/*
 * PlayerView.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: ldea
 */
#include "PlayerView.hh"

PlayerView::PlayerView(GameView* _gameView)
{
	gameView = _gameView;
	animations[STATE_WALKINGRIGHT] = new Sprite(gameView,"../.images/player/walkingRight.png", 25, 38, 58, 87);
	animations[STATE_WALKINGRIGHTPOINTUP] = new Sprite(gameView,"../.images/player/walkingRightPointingUp.png", 19, 38, 44, 87);
	animations[STATE_WALKINGRIGHTPOITNDOWN] = new Sprite(gameView,"../.images/player/walkingRightPointingDown.png", 21, 38, 48, 87);
	animations[STATE_WALKINGLEFT] = new Sprite(gameView,"../.images/player/walkingLeft.png", 25, 38, 58, 87);
	animations[STATE_WALKINGLEFTPOINTUP] = new Sprite(gameView,"../.images/player/walkingLeftPointingUp.png", 19, 38, 44, 87);
	animations[STATE_WALKINGLEFTPOINTDOWN] = new Sprite(gameView,"../.images/player/walkingLeftPointingDown.png", 21, 38, 48, 87);
	animations[STATE_STANDING] = new Sprite(gameView,"../.images/player/standing.png", 16, 38, 39, 87);
	animations[STATE_STANDING_BACK] = new Sprite(gameView,"../.images/player/standingBack.png", 16, 38, 39, 87);
	animations[STATE_JUMPINGUP] = new Sprite(gameView,"../.images/player/jumping.png", 20, 38, 46, 114);
	animations[STATE_JUMPINGDOWN] = new Sprite(gameView,"../.images/player/jumping.png", 20, 38, 46, 87);
	animations[STATE_POINTUP] = new Sprite(gameView,"../.images/player/pointUp.png", 18, 36, 41, 82);
	animations[STATE_POINTFRONT] = new Sprite(gameView,"../.images/player/pointFront.png", 25, 36, 58, 84);
	animations[STATE_POINTBACK] = new Sprite(gameView,"../.images/player/pointBack.png", 25, 36, 58, 82);
	animations[STATE_POINTDOWN] = new Sprite(gameView,"../.images/player/pointDown.png", 22, 37, 51, 85);
	animations[STATE_POINTBODYTOGROUND] = new Sprite(gameView,"../.images/player/bodyToGround.png", 32, 38, 74, 87);
	animations[STATE_POINTDOWN_BACK] = new Sprite(gameView,"../.images/player/pointDownBack.png", 22, 37, 51, 85);
	animations[STATE_POINTBODYTOGROUND_BACK] = new Sprite(gameView,"../.images/player/bodyToGroundBack.png", 32, 38, 74, 87);
	animations[STATE_POINTUP_BACK] = new Sprite(gameView,"../.images/player/pointUpBack.png", 18, 36, 41, 82);

}

PlayerView::~PlayerView()
{
	destroy();
}

void PlayerView::destroy()
{
	for(int i = 0 ; i < PlayerStateHandler::MAX_ANIMATIONS ; i++)
	{
		if (animations[i]) {animations[i]->destroy();}
	}
}

void PlayerView::render(int aState, int pos_x, int pos_y)
{
	animations[aState]->render(pos_x, pos_y);

}

void PlayerView::update(int aState)
{
	animations[aState]->update();
}


