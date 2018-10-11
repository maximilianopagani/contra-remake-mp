/*
 * LevelView.hh
 *
 *  Created on: Oct 6, 2018
 *      Author: ldea
 */

#ifndef VISTA_LEVELVIEW_HH_
#define VISTA_LEVELVIEW_HH_

#include "GameView.hh"
#include "Sprite.hh"

class LevelView
{
	public:

		LevelView(GameView* _gameView);
		virtual ~LevelView();

		void loadSprite(string path, int background);
		void render(int pos_x, int pos_y, int background);

		void destroy();

	private:

		GameView* gameView;

		Sprite* background1Sprite;
		Sprite* background2Sprite;
		Sprite* background3Sprite;
};
#endif /* VISTA_LEVELVIEW_HH_ */
