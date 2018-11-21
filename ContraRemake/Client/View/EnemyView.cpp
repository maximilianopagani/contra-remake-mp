/*
 * EnemyView.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: maximiliano
 */

#include "EnemyView.hh"

EnemyView::EnemyView(GameView* _gameView){

	gameView = _gameView;

	bloodSprite =  new Sprite(gameView, "../.images/background/blood.png", 30, 30, 80, 80);

	sprites_runner[EnemyRunnerStates::RUNNER_STATE_RUNNING_LEFT] = new Sprite(gameView, "../.images/enemies/runner/runner_left.png", 18, 32, 42, 84);
	sprites_runner[EnemyRunnerStates::RUNNER_STATE_RUNNING_RIGHT] = new Sprite(gameView, "../.images/enemies/runner/runner_right.png", 18, 32, 42, 84);

	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_UP] = new Sprite(gameView, "../.images/enemies/rifleman/rifleman_left_up.png", 24, 38, 59, 93);
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_FRONT] = new Sprite(gameView, "../.images/enemies/rifleman/rifleman_left_front.png", 24, 38, 59, 93);
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_DOWN] = new Sprite(gameView, "../.images/enemies/rifleman/rifleman_left_down.png", 24, 38, 59, 93);
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_RIGHT_UP] = new Sprite(gameView, "../.images/enemies/rifleman/rifleman_right_up.png", 24, 38, 59, 93);
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_RIGHT_FRONT] = new Sprite(gameView, "../.images/enemies/rifleman/rifleman_right_front.png", 24, 38, 59, 93);
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_RIGHT_DOWN] = new Sprite(gameView, "../.images/enemies/rifleman/rifleman_right_down.png", 24, 38, 59, 93);

	sprites[EnemyType::ENEMY_TYPE_RUNNER] = sprites_runner;
	sprites[EnemyType::ENEMY_TYPE_RIFLEMAN] = sprites_rifleman;
}

EnemyView::~EnemyView()
{
	this->destroy();
}

void EnemyView::update(int enemy_type, int state, int animation)
{
	if(enemy_type == -1) bloodSprite->update();
	else sprites[enemy_type][state]->moveToPos(animation);
}

void EnemyView::render(int enemy_type, int state, int pos_x, int pos_y)
{
	if(enemy_type == -1) bloodSprite->render(pos_x, pos_y);
	else sprites[enemy_type][state]->render(pos_x, pos_y);
}

void EnemyView::destroy()
{
	sprites_runner[EnemyRunnerStates::RUNNER_STATE_RUNNING_LEFT]->destroy();
	sprites_runner[EnemyRunnerStates::RUNNER_STATE_RUNNING_RIGHT]->destroy();

	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_UP]->destroy();
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_FRONT]->destroy();
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_DOWN]->destroy();
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_RIGHT_UP]->destroy();
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_RIGHT_FRONT]->destroy();
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_RIGHT_DOWN]->destroy();

	sprites_runner[EnemyRunnerStates::RUNNER_STATE_RUNNING_LEFT] = NULL;
	sprites_runner[EnemyRunnerStates::RUNNER_STATE_RUNNING_RIGHT] = NULL;

	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_UP] = NULL;
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_FRONT] = NULL;
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_LEFT_DOWN] = NULL;
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_RIGHT_UP] = NULL;
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_RIGHT_FRONT] = NULL;
	sprites_rifleman[EnemyRiflemanStates::RIFLEMAN_STATE_RIGHT_DOWN] = NULL;

	bloodSprite = NULL;
}
