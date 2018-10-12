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

		void render(int posX, int posY);
		void destroy();

	private:
		GameView* gameView;
		Sprite* sprite;
};

#endif /* VISTA_BULLETVIEW_HH_ */
