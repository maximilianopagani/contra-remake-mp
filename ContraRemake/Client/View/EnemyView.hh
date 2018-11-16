/*
 * EnemyView.hh
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#ifndef VISTA_ENEMYVIEW_HH_
#define VISTA_ENEMYVIEW_HH_

#include "../../Utils/EnemyTypesAndStates.hh"
#include "GameView.hh"
#include "Sprite.hh"

class EnemyView
{
	public:

		EnemyView(GameView* _gameView);
		virtual ~EnemyView();

		void update(int enemy_type, int state, int animation);
		void render(int enemy_type, int state, int pos_x, int pos_y);
		void destroy();

	private:

		GameView* gameView;

		Sprite* sprites_runner[MAX_RUNNER_STATES];
		Sprite* sprites_rifleman[MAX_RIFLEMAN_STATES];

		Sprite** sprites[MAX_ENEMY_TYPES];
};

#endif /* VISTA_ENEMYVIEW_HH_ */
