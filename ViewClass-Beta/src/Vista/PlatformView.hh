/*
 * PlatformView.hh
 *
 *  Created on: Oct 6, 2018
 *      Author: ldea
 */

#ifndef VISTA_PLATFORMVIEW_HH_
#define VISTA_PLATFORMVIEW_HH_

#include "GameView.hh"
#include "Sprite.hh"

class PlatformView
{
	public:
		PlatformView(GameView* _gameView);
		virtual ~PlatformView();

		void loadSprite(string spritePath, int width, int height);
		void render(int posX, int posY);
		void destroy();

	private:
		GameView* gameView;
		Sprite* sprite;
};

#endif /* VISTA_PLATFORMVIEW_HH_ */
