/*
 * PlayerView.hh
 *
 *  Created on: Oct 6, 2018
 *      Author: ldea
 */

#ifndef VISTA_PLAYERVIEW_HH_
#define VISTA_PLAYERVIEW_HH_

#include "GameView.hh"
#include "Sprite.hh"

class PlayerView
{
	public:
		PlayerView(GameView* _gameView);
		virtual ~PlayerView();

	private:
		static const int MAX_ANIMATIONS = 18;
		enum PlayerState {
			STATE_WALKINGRIGHT,
			STATE_WALKINGRIGHTPOINTUP,
			STATE_WALKINGRIGHTPOITNDOWN,
			STATE_WALKINGLEFT,
			STATE_WALKINGLEFTPOINTUP,
			STATE_WALKINGLEFTPOINTDOWN,
			STATE_STANDING,
			STATE_STANDING_BACK,
			STATE_JUMPINGUP,
			STATE_JUMPINGDOWN,
			STATE_POINTUP,
			STATE_POINTFRONT,
			STATE_POINTBACK,
			STATE_POINTDOWN,
			STATE_POINTBODYTOGROUND,
			STATE_POINTUP_BACK,
			STATE_POINTDOWN_BACK,
			STATE_POINTBODYTOGROUND_BACK,
			};
		PlayerState state;
		GameView* gameView;
		Sprite* animations[MAX_ANIMATIONS];
};

#endif /* VISTA_PLAYERVIEW_HH_ */
