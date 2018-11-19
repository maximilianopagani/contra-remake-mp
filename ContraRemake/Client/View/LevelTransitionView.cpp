/*
 * LevelTransitionView.cpp
 *
 *  Created on: 10 nov. 2018
 *      Author: nacho
 */

#include "LevelTransitionView.hh"

const int CAPTIONS_POSITION_X = 50;
const int PLAYER1_POSITION_X = 250;
const int PLAYERNAMES_POSITION_Y = 150;
const int PADDING = 75;
const int LEVEL1_POSITION_Y = PLAYERNAMES_POSITION_Y + PADDING;
const int LEVEL2_POSITION_Y = LEVEL1_POSITION_Y + PADDING;
const int LEVEL3_POSITION_Y = LEVEL2_POSITION_Y + PADDING;
const int TOTAL_POSITION_Y = LEVEL3_POSITION_Y + PADDING;
const int PRESSKEYTOCONTINUE_POSITION_Y = TOTAL_POSITION_Y + PADDING;

LevelTransitionView::LevelTransitionView(GameView* _gameView) {

	gameView = _gameView;
	backgroundSprite = new Sprite(gameView, "../.images/screens/levelTransition.png", 800, 600, 800, 600);
	SDL_Color textColor = { 214, 239, 239, 0xFF };
	level1Texture = new Text(gameView, "LEVEL 1", textColor);
	level2Texture = new Text(gameView, "LEVEL 2", textColor);
	level3Texture = new Text(gameView, "LEVEL 3", textColor);
	totalTexture = new Text(gameView, "TOTAL", textColor);
	pressKeyToContinueTexture = new Text(gameView, "Presione la tecla N para continuar", textColor);
	/*
	/////////////////////////////////
	// CARGA DE NOMBRES DE EJEMPLO //
	/////////////////////////////////

	this->loadPlayerNames(std::string("ignacio").c_str());
	this->loadPlayerNames(std::string("maxi").c_str());
	this->loadPlayerNames(std::string("lucas").c_str());
	this->loadPlayerNames(std::string("gio").c_str());

	/////////////////////////////////////
	// FIN CARGA DE NOMBRES DE EJEMPLO //
	/////////////////////////////////////

	////////////////////////////////
	// CARGA DE SCORES DE EJEMPLO //
	////////////////////////////////
	this->loadScore(1, 1, 100);
	this->loadScore(1, 2, 150);
	this->loadScore(1, 3, 200);
	this->loadScore(1, 4, 250);

	this->loadScore(2, 1, 400);
	this->loadScore(2, 2, 200);
	this->loadScore(2, 3, 100);
	this->loadScore(2, 4, 800);

	this->loadScore(3, 1, 500);
	this->loadScore(3, 2, 200);
	this->loadScore(3, 3, 350);
	this->loadScore(3, 4, 100);
	////////////////////////////////////
	// FIN CARGA DE SCORES DE EJEMPLO //
	////////////////////////////////////
	*/
}

LevelTransitionView::~LevelTransitionView() {

	this->destroy();
}

void LevelTransitionView::loadPlayerNames(const char* player_name) {

	SDL_Color textColor = { 255, 255, 255, 0xFF };
	playerNames.push_back(new Text(gameView, player_name, textColor));
	playersTotalScores.push_back(new Text(gameView, std::string("0").c_str(), textColor));
}

void LevelTransitionView::loadScore(int level_id, int player_id, int score) {

	SDL_Color textColor = { 255, 255, 0, 0xFF };

	switch(level_id) {
		case 0:
		{
			level1Score.push_back(score);
			playersLevel1Scores.push_back(new Text(gameView, std::to_string(score).c_str(), textColor));
			break;
		}
		case 1:
		{
			level2Score.push_back(score);
			playersLevel2Scores.push_back(new Text(gameView, std::to_string(score).c_str(), textColor));
			break;
		}
		case 2:
		{
			level3Score.push_back(score);
			playersLevel3Scores.push_back(new Text(gameView, std::to_string(score).c_str(), textColor));
			break;
		}
		case 3:
		{
			playersTotalScores[player_id]->destroy();
			playersTotalScores[player_id] = new Text(gameView, std::to_string(score).c_str(), textColor);
			break;
		}
	}
}

void LevelTransitionView::render() {
	backgroundSprite->render(0, 0);
	level1Texture->render(CAPTIONS_POSITION_X, LEVEL1_POSITION_Y);
	level2Texture->render(CAPTIONS_POSITION_X, LEVEL2_POSITION_Y);
	level3Texture->render(CAPTIONS_POSITION_X, LEVEL3_POSITION_Y);
	totalTexture->render(CAPTIONS_POSITION_X, TOTAL_POSITION_Y);
	pressKeyToContinueTexture->render(CAPTIONS_POSITION_X, PRESSKEYTOCONTINUE_POSITION_Y);
	int i = PLAYER1_POSITION_X;
	for (vector<Text*>::iterator it = playerNames.begin(); it != playerNames.end(); it++) {
		(*it)->render(i, PLAYERNAMES_POSITION_Y);
		i += 150;
	}
	i = PLAYER1_POSITION_X;
	for (vector<Text*>::iterator it = playersLevel1Scores.begin(); it != playersLevel1Scores.end(); it++) {
		(*it)->render(i, LEVEL1_POSITION_Y);
		i += 150;
	}
	i = PLAYER1_POSITION_X;
	for (vector<Text*>::iterator it = playersLevel2Scores.begin(); it != playersLevel2Scores.end(); it++) {
		(*it)->render(i, LEVEL2_POSITION_Y);
		i += 150;
	}
	i = PLAYER1_POSITION_X;
	for (vector<Text*>::iterator it = playersLevel3Scores.begin(); it != playersLevel3Scores.end(); it++) {
		(*it)->render(i, LEVEL3_POSITION_Y);
		i += 150;
	}
	i = PLAYER1_POSITION_X;
	for (vector<Text*>::iterator it = playersTotalScores.begin(); it != playersTotalScores.end(); it++) {
		(*it)->render(i, TOTAL_POSITION_Y);
		i += 150;
	}
}

void LevelTransitionView::destroy() {
	backgroundSprite->destroy();
	level1Texture->destroy();
	level2Texture->destroy();
	level3Texture->destroy();
	totalTexture->destroy();
	for (vector<Text*>::iterator it = playerNames.begin(); it != playerNames.end(); it++) {
		(*it)->destroy();
	}
	for (vector<Text*>::iterator it = playersLevel1Scores.begin(); it != playersLevel1Scores.end(); it++) {
		(*it)->destroy();
	}
	for (vector<Text*>::iterator it = playersLevel2Scores.begin(); it != playersLevel2Scores.end(); it++) {
		(*it)->destroy();
	}
	for (vector<Text*>::iterator it = playersLevel3Scores.begin(); it != playersLevel3Scores.end(); it++) {
		(*it)->destroy();
	}
	for (vector<Text*>::iterator it = playersTotalScores.begin(); it != playersTotalScores.end(); it++) {
		(*it)->destroy();
	}
}
