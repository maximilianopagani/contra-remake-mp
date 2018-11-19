/*
 * BossView.cpp
 *
 *  Created on: Nov 17, 2018
 *      Author: giova
 */

#include "BossView.hh"

BossView::BossView(GameView* _gameView) {
	gameView = _gameView;

	bosslevel1[BOSS1_STANDING] = new Sprite(gameView, "../.images/bosses/1/standing.png",129, 97, 258, 194);
	bosslevel1[BOSS1_RUNNING] = new Sprite(gameView, "../.images/bosses/1/running.png",  129, 97, 258, 194);
	bosslevel1[BOSS1_RUNNING_END] = new Sprite(gameView, "../.images/bosses/1/runningEnd.png",129, 97, 258, 194);
	bosslevel1[BOSS1_CLOSE_EYE] = new Sprite(gameView, "../.images/bosses/1/closeEye.png",  129, 97, 258, 194);
	bosslevel1[BOSS1_SHOOT] = new Sprite(gameView, "../.images/bosses/1/shoot.png",  129, 97, 258, 194);
	bosslevel1[BOSS1_UNDERGROUND1] = new Sprite(gameView, "../.images/bosses/1/underground1.png", 129, 97, 258, 194);
	bosslevel1[BOSS1_UNDERGROUND2] = new Sprite(gameView, "../.images/bosses/1/undergroumd2.png",  129, 97, 258, 194);
	bosslevel1[BOSS1_GETTING_DMG] = new Sprite(gameView, "../.images/bosses/1/gettingDmg.png",129, 97, 258, 194);
	bosslevel1[BOSS1_DEAD] = new Sprite(gameView, "../.images/bosses/1/dead.png",  129, 97,  258, 194);

	bosslevel2[BOSS2_STANDING] = new Sprite(gameView, "../.images/bosses/2/standing.png",254,104,504,208);
	bosslevel2[BOSS2_ATTACKING] = new Sprite(gameView, "../.images/bosses/2/attacking2.png",254,140,504,280);
	bosslevel2[BOSS2_ATTACKING_END] = new Sprite(gameView, "../.images/bosses/2/attackingEnd.png",254,140,504,280);
	bosslevel2[BOSS2_GETTING_DMG] = new Sprite(gameView, "../.images/bosses/2/gettingDmg.png",254,140,504,208);
	bosslevel2[BOSS2_SHOOT] = new Sprite(gameView, "../.images/bosses/2/shoot.png",254,140,504,208);
	bosslevel2[BOSS2_DEAD] = new Sprite(gameView, "../.images/bosses/2/dead.png",254,64,504,128);
	bosslevel2[BOSS2_BODY] = new Sprite(gameView, "../.images/bosses/2/body.png",129,180,258,360);

	bosslevel3[BOSS3_STANDING] = new Sprite(gameView, "../.images/bosses/3/standing.png",99,112,99,112);
	bosslevel3[BOSS3_ATTACKING] = new Sprite(gameView, "../.images/bosses/3/attacking.png",99,112,99,112);
	bosslevel3[BOSS3_SHOOT] = new Sprite(gameView, "../.images/bosses/3/shoot.png",143,114,99,112);
	bosslevel3[BOSS3_GETTING_DMG] = new Sprite(gameView, "../.images/bosses/3/gettingDmg.png",99,112,99,112);
	bosslevel3[BOSS3_DEAD] = new Sprite(gameView, "../.images/bosses/3/dead.png",99,112,99,112);

	sprites[0] = bosslevel1;
	sprites[1] = bosslevel2;
	sprites[2] = bosslevel3;
}

void BossView::render(int _id, int state, int pos_x, int pos_y)
{
	if( _id == 1 ) sprites[1][BOSS2_BODY]->render(271,0);

	sprites[_id][state]->render(pos_x, pos_y);
}

void BossView::update(int _id, int state)
{
	sprites[_id][state]->update();

	if( _id == 1 && state== 1) sprites[1][BOSS2_BODY]->update();

}

void BossView::destroy()
{
	bosslevel1[BOSS1_STANDING]->destroy();
	bosslevel1[BOSS1_RUNNING]->destroy();
	bosslevel1[BOSS1_CLOSE_EYE]->destroy();
	bosslevel1[BOSS1_SHOOT]->destroy();
	bosslevel1[BOSS1_UNDERGROUND1]->destroy();
	bosslevel1[BOSS1_UNDERGROUND2]->destroy();
	bosslevel1[BOSS1_GETTING_DMG]->destroy();

	bosslevel1[BOSS1_STANDING]= NULL;
	bosslevel1[BOSS1_RUNNING]= NULL;
	bosslevel1[BOSS1_CLOSE_EYE]= NULL;
	bosslevel1[BOSS1_SHOOT]= NULL;
	bosslevel1[BOSS1_UNDERGROUND1]= NULL;
	bosslevel1[BOSS1_UNDERGROUND2]= NULL;
	bosslevel1[BOSS1_GETTING_DMG]= NULL;

}

BossView::~BossView() {
	this->destroy();
}

