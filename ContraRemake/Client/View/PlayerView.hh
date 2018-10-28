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
#include "../../Utils/PlayerStateHandler.hh"

class PlayerView
{
	public:

		PlayerView(GameView* _gameView);
		virtual ~PlayerView();

		void loadSprite(string type);
		void render(int player_id, int state, int pos_x, int pos_y);
		void update(int player_id, int state);
		void destroy();

	private:

		GameView* gameView;

		Sprite* sprites_p1[PlayerStateHandler::MAX_ANIMATIONS];
		Sprite* sprites_p2[PlayerStateHandler::MAX_ANIMATIONS];
		Sprite* sprites_p3[PlayerStateHandler::MAX_ANIMATIONS];
		Sprite* sprites_p4[PlayerStateHandler::MAX_ANIMATIONS];

		Sprite** sprites[4];

		//int lastState = STATE_STANDING, hasToUpdateCount = 0;
};

#endif /* VISTA_PLAYERVIEW_HH_ */
