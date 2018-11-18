/*
 * LevelTransitionView.cpp
 *
 *  Created on: 10 nov. 2018
 *      Author: nacho
 */

#include "LevelTransitionView.hh"

const int CAPTIONS_POSITION_X = 50;
const int PLAYER1_POSITION_X = 100;
const int PLAYER2_POSITION_X = 250;
const int PLAYER3_POSITION_X = 400;
const int PLAYER4_POSITION_X = 550;
const int LEVEL1_POSITION_Y = 275;
const int LEVEL2_POSITION_Y = 375;
const int LEVEL3_POSITION_Y = 475;
const int TOTAL_POSITION_Y = 575;

LevelTransitionView::LevelTransitionView(GameView* _gameView) {

	gameView = _gameView;
	backgroundSprite = new Sprite(gameView, "../.images/screens/levelTransition.png", 800, 600, 800, 600);
	level1Texture = new Text(gameView, "LEVEL 1");
	level2Texture = NULL;
	level3Texture = NULL;
	totalTexture = NULL;
	player1NameTexture = NULL;
	player1Level1Texture = NULL;
	player1Level2Texture = NULL;
	player1Level3Texture = NULL;
	player1TotalTexture = NULL;
	player2NameTexture = NULL;
	player2Level1Texture = NULL;
	player2Level2Texture = NULL;
	player2Level3Texture = NULL;
	player2TotalTexture = NULL;
	player3NameTexture = NULL;
	player3Level1Texture = NULL;
	player3Level2Texture = NULL;
	player3Level3Texture = NULL;
	player3TotalTexture = NULL;
	player4NameTexture = NULL;
	player4Level1Texture = NULL;
	player4Level2Texture = NULL;
	player4Level3Texture = NULL;
	player4TotalTexture = NULL;
	for (unsigned int i = 0; i < 4; i++) {
		level1Score.push_back(i);
		level1Score[i] = 0;
		level2Score.push_back(i);
		level2Score[i] = 0;
		level3Score.push_back(i);
		level3Score[i] = 0;
		totalScore.push_back(i);
		totalScore[i] = 0;
	}
}

LevelTransitionView::~LevelTransitionView() {

	this->destroy();
}

void LevelTransitionView::loadScore(int level_id, int player_id, int score) {

	switch(level_id) {
		case 1:
		{
			level1Score[player_id] = score;
			break;
		}
		case 2:
		{
			level2Score[player_id] = score;
			break;
		}
		case 3:
		{
			level3Score[player_id] = score;
			break;
		}
		case 4:
		{
			totalScore[player_id] = score;
			break;
		}
	}
}

void LevelTransitionView::render() {
	backgroundSprite->render(0, 0);
	level1Texture->render(CAPTIONS_POSITION_X, LEVEL1_POSITION_Y);
	/*
	level1Texture->loadFromRenderedText("Level 1", textColor);
	level2Texture->loadFromRenderedText("Level 2", textColor);
	level3Texture->loadFromRenderedText("Level 3", textColor);
	totalTexture->loadFromRenderedText("TOTAL", textColor);
	level1Texture->render(CAPTIONS_POSITION_X, LEVEL1_POSITION_Y);
	level2Texture->render(CAPTIONS_POSITION_X, LEVEL2_POSITION_Y);
	level3Texture->render(CAPTIONS_POSITION_X, LEVEL3_POSITION_Y);
	totalTexture->render(CAPTIONS_POSITION_X, TOTAL_POSITION_Y);
	*/
}

void LevelTransitionView::destroy() {
	backgroundSprite->destroy();
	level1Texture->destroy();
}
