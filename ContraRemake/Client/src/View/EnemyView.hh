/*
 * EnemyView.hh
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#ifndef VISTA_ENEMYVIEW_HH_
#define VISTA_ENEMYVIEW_HH_

#include "GameView.hh"
#include "Sprite.hh"

class EnemyView
{
	public:

		EnemyView(GameView* _gameView);
		virtual ~EnemyView();

		void loadSprite(string spritePath, int width, int height);
		void render(int posX, int posY);
		void destroy();

	private:

		GameView* gameView;

		static const int MAX_ANIMATIONS = 1;
		Sprite* animations[MAX_ANIMATIONS];
};

#endif /* VISTA_ENEMYVIEW_HH_ */
