/*
 * LevelTransitionView.cpp
 *
 *  Created on: 10 nov. 2018
 *      Author: nacho
 */

#include "LevelTransitionView.hh"

LevelTransitionView::LevelTransitionView(GameView* _gameView) {

	gameView = _gameView;
}

LevelTransitionView::~LevelTransitionView() {

	this->destroy();
}

void LevelTransitionView::loadScore(int level_id, int player_id, int score) {

}

void LevelTransitionView::render() {

}

void LevelTransitionView::destroy() {

}
