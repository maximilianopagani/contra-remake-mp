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
		void destroy();

	private:
		GameView* gameView;
//		Sprite* sprite;
//
//		Sprite* sprites_p1;
//		Sprite* sprites_p2;
//		Sprite* sprites_p3;
//		Sprite* sprites_p4;

		Sprite* sprites[4];

};

#endif /* VISTA_BULLETVIEW_HH_ */
