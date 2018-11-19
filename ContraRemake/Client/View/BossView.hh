/*
 * BossView.hh
 *
 *  Created on: Nov 17, 2018
 *      Author: giova
 */

#include "../../Utils/EnemyTypesAndStates.hh"
#include "GameView.hh"
#include "Sprite.hh"

enum boss1States{
		BOSS1_STANDING,
		BOSS1_RUNNING,
		BOSS1_CLOSE_EYE,
		BOSS1_SHOOT,
		BOSS1_UNDERGROUND1,
		BOSS1_UNDERGROUND2,
		BOSS1_GETTING_DMG,
		BOSS1_RUNNING_END,
		BOSS1_DEAD
};
enum boss2States{
		BOSS2_STANDING,
		BOSS2_ATTACKING,
		BOSS2_ATTACKING_END,
		BOSS2_GETTING_DMG,
		BOSS2_SHOOT,
		BOSS2_DEAD,
		BOSS2_BODY
};
enum boss3States{
		BOSS3_STANDING,
		BOSS3_ATTACKING,
		BOSS3_GETTING_DMG,
		BOSS3_SHOOT,
		BOSS3_DEAD
};

#ifndef CLIENT_VIEW_BOSSVIEW_HH_
#define CLIENT_VIEW_BOSSVIEW_HH_

class BossView {
public:
	BossView(GameView* _gameView);
	virtual ~BossView();

	void update(int player_id, int state);
	void render(int type, int state, int pos_x, int pos_y);
	void destroy();

private:

	GameView* gameView;

	Sprite* bosslevel1[9];
	Sprite* bosslevel2[7];
	Sprite* bosslevel3[5];

	Sprite** sprites[3];

};

#endif /* CLIENT_VIEW_BOSSVIEW_HH_ */
