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
#include "../Utils/PlayerStateHandler.hh"

class PlayerView
{
	public:
		PlayerView(GameView* _gameView);
		virtual ~PlayerView();

		void loadSprite(string type);
		void update(PlayerState aState);
		void render(PlayerState aState, int posX, int posY);
		void destroy();

	private:
//		const int MAX_ANIMATIONS = PlayerStateHandler::getMaxAnimations();
//		enum PlayerState {
//			STATE_WALKINGRIGHT,
//			STATE_WALKINGRIGHTPOINTUP,
//			STATE_WALKINGRIGHTPOITNDOWN,
//			STATE_WALKINGLEFT,
//			STATE_WALKINGLEFTPOINTUP,
//			STATE_WALKINGLEFTPOINTDOWN,
//			STATE_STANDING,
//			STATE_STANDING_BACK,
//			STATE_JUMPINGUP,
//			STATE_JUMPINGDOWN,
//			STATE_POINTUP,
//			STATE_POINTFRONT,
//			STATE_POINTBACK,
//			STATE_POINTDOWN,
//			STATE_POINTBODYTOGROUND,
//			STATE_POINTUP_BACK,
//			STATE_POINTDOWN_BACK,
//			STATE_POINTBODYTOGROUND_BACK,
//			};
//		PlayerState state;
		GameView* gameView;
//		Sprite* animations[18];
		Sprite* animations[PlayerStateHandler::MAX_ANIMATIONS];
};

#endif /* VISTA_PLAYERVIEW_HH_ */
