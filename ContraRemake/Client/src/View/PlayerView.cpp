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

	sprites[0] = sprites_p1;
	sprites[1] = sprites_p2;
	sprites[2] = sprites_p3;
	sprites[3] = sprites_p4;

	for(int i = 0; i < 4; i++)
	{
		std::string player_i_path = "player/p" + std::to_string(i+1);

		sprites[i][STATE_WALKINGRIGHT] = new Sprite(gameView, "../.images/" + player_i_path + "/walkingRight.png", 25, 38, 58, 87);
		sprites[i][STATE_WALKINGRIGHTPOINTUP] = new Sprite(gameView, "../.images/" + player_i_path + "/walkingRightPointingUp.png", 19, 38, 44, 87);
		sprites[i][STATE_WALKINGRIGHTPOITNDOWN] = new Sprite(gameView, "../.images/" + player_i_path + "/walkingRightPointingDown.png", 21, 38, 48, 87);
		sprites[i][STATE_WALKINGLEFT] = new Sprite(gameView, "../.images/" + player_i_path + "/walkingLeft.png", 25, 38, 58, 87);
		sprites[i][STATE_WALKINGLEFTPOINTUP] = new Sprite(gameView, "../.images/" + player_i_path + "/walkingLeftPointingUp.png", 19, 38, 44, 87);
		sprites[i][STATE_WALKINGLEFTPOINTDOWN] = new Sprite(gameView, "../.images/" + player_i_path + "/walkingLeftPointingDown.png", 21, 38, 48, 87);
		sprites[i][STATE_STANDING] = new Sprite(gameView, "../.images/" + player_i_path + "/standing.png", 16, 38, 39, 87);
		sprites[i][STATE_STANDING_BACK] = new Sprite(gameView, "../.images/" + player_i_path + "/standingBack.png", 16, 38, 39, 87);
		sprites[i][STATE_JUMPINGUP] = new Sprite(gameView, "../.images/" + player_i_path + "/jumping.png", 20, 38, 46, 114);
		sprites[i][STATE_JUMPINGDOWN] = new Sprite(gameView, "../.images/" + player_i_path + "/jumping.png", 20, 38, 46, 87);
		sprites[i][STATE_POINTUP] = new Sprite(gameView, "../.images/" + player_i_path + "/pointUp.png", 18, 36, 41, 82);
		sprites[i][STATE_POINTFRONT] = new Sprite(gameView, "../.images/" + player_i_path + "/pointFront.png", 25, 36, 58, 84);
		sprites[i][STATE_POINTBACK] = new Sprite(gameView, "../.images/" + player_i_path + "/pointBack.png", 25, 36, 58, 82);
		sprites[i][STATE_POINTDOWN] = new Sprite(gameView, "../.images/" + player_i_path + "/pointDown.png", 22, 37, 51, 85);
		sprites[i][STATE_POINTBODYTOGROUND] = new Sprite(gameView, "../.images/" + player_i_path + "/bodyToGround.png", 32, 38, 74, 87);
		sprites[i][STATE_POINTDOWN_BACK] = new Sprite(gameView, "../.images/" + player_i_path + "/pointDownBack.png", 22, 37, 51, 85);
		sprites[i][STATE_POINTBODYTOGROUND_BACK] = new Sprite(gameView, "../.images/" + player_i_path + "/bodyToGroundBack.png", 32, 38, 74, 87);
		sprites[i][STATE_POINTUP_BACK] = new Sprite(gameView, "../.images/" + player_i_path + "/pointUpBack.png", 18, 36, 41, 82);
	}
}

PlayerView::~PlayerView()
{
	destroy();
}

void PlayerView::destroy()
{
	for(int player = 0; player < 4; player++)
	{
		for(int i = 0 ; i < PlayerStateHandler::MAX_ANIMATIONS ; i++)
		{
			if (sprites[player][i])
			{
				sprites[player][i]->destroy();
			}
		}
	}
}

void PlayerView::render(int player_id, int state, int pos_x, int pos_y)
{
	sprites[player_id][state]->render(pos_x, pos_y);

}

void PlayerView::update(int player_id, int state)
{
	sprites[player_id][state]->update();
}


