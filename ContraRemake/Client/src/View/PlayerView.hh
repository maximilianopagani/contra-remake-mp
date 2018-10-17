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
#include "../PlayerStateHandler.hh"
//#include "Server/src/Utils/PlayerStateHandler.hh"

class PlayerView
{
	public:

		PlayerView(GameView* _gameView);
		virtual ~PlayerView();

		void loadSprite(string type);
		void render(int aState, int posX, int posY);
		void destroy();

	private:

		GameView* gameView;
		Sprite* animations[PlayerStateHandler::MAX_ANIMATIONS];
		int lastState = STATE_STANDING, hasToUpdateCount = 0;
};

#endif /* VISTA_PLAYERVIEW_HH_ */
