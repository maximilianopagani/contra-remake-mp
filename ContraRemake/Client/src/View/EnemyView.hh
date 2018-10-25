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

		void update(int enemy_id, int state);
		void render(int enemy_id, int state, int pos_x, int pos_y);
		void destroy();

	private:

		GameView* gameView;

		static const int MAX_ANIMATIONS = 2;
		static const int MAX_ENEMYS = 1;

		Sprite* sprites_e1[MAX_ANIMATIONS];

		Sprite** sprites[MAX_ENEMYS];
};

#endif /* VISTA_ENEMYVIEW_HH_ */
