/*
 * LevelTransitionView.hh
 *
 *  Created on: 10 nov. 2018
 *      Author: nacho
 */

#ifndef CLIENT_VIEW_LEVELTRANSITIONVIEW_HH_
#define CLIENT_VIEW_LEVELTRANSITIONVIEW_HH_

#include "GameView.hh"
#include "Sprite.hh"
#include "Text.hh"
#include <SDL2/SDL_ttf.h>
#include <vector>

class LevelTransitionView {

public:

	LevelTransitionView(GameView* _gameView);
	virtual ~LevelTransitionView();

	void loadPlayerNames(const char* player_name);
	void loadScore(int level_id, int player_id, int score);
	void render();
	void destroy();

private:

	GameView* gameView;
	Sprite* backgroundSprite;
	Text *level1Texture;
	Text *level2Texture;
	Text *level3Texture;
	Text *totalTexture;
	std::vector<Text*> playerNames;
	std::vector<Text*> playersLevel1Scores;
	std::vector<Text*> playersLevel2Scores;
	std::vector<Text*> playersLevel3Scores;
	std::vector<Text*> playersTotalScores;
	std::vector<int> level1Score;
	std::vector<int> level2Score;
	std::vector<int> level3Score;
	std::vector<int> totalScore;
};

#endif /* CLIENT_VIEW_LEVELTRANSITIONVIEW_HH_ */
