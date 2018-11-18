/*
 * BulletView.hh
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#ifndef VISTA_BULLETVIEW_HH_
#define VISTA_BULLETVIEW_HH_

#include "GameView.hh"
#include "Sprite.hh"

class BulletView
{
	public:

		BulletView(GameView* _gameView);
		virtual ~BulletView();

		void render(int player_id, int posX, int posY);
		void renderLaser(int player_id, int posX, int posY, int direction);
		void destroy();

	private:

		GameView* gameView;
		Sprite* sprites[4];
		Sprite* laserSprites[4][6];
};

#endif /* VISTA_BULLETVIEW_HH_ */
