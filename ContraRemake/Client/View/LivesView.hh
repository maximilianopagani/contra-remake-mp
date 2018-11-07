/*
 * LivesView.hh
 *
 *  Created on: Nov 6, 2018
 *      Author: maximiliano
 */

#ifndef CLIENT_VIEW_LIVESVIEW_HH_
#define CLIENT_VIEW_LIVESVIEW_HH_

#include "GameView.hh"
#include "Sprite.hh"

class LivesView
{
	public:

		LivesView(GameView* _gameView);
		virtual ~LivesView();

		void render(int player_id, int amount);
		void destroy();

	private:

		GameView* gameView;
		Sprite* sprites[4];
		int sprites_pos_x[4] = {10, 160, 310, 460};
		int sprites_pos_y = 10;
};

#endif /* CLIENT_VIEW_LIVESVIEW_HH_ */
