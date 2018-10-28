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
	enum PlatformType {
		TYPE_GRASS,
		TYPE_ICE,
		TYPE_WOOD,
		TYPE_ROCK,
		TYPE_ERROR
	};

	public:
		PlatformView(GameView* _gameView);
		virtual ~PlatformView();

		void render(int posX, int posY, int tileAmount, int typeCode);
		void destroy();

	private:

		GameView* gameView;
		Sprite* sprites[5];
};

#endif /* VISTA_PLATFORMVIEW_HH_ */
