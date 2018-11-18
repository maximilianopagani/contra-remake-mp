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
	Text *player1NameTexture;
	Text *player1Level1Texture;
	Text *player1Level2Texture;
	Text *player1Level3Texture;
	Text *player1TotalTexture;
	Text *player2NameTexture;
	Text *player2Level1Texture;
	Text *player2Level2Texture;
	Text *player2Level3Texture;
	Text *player2TotalTexture;
	Text *player3NameTexture;
	Text *player3Level1Texture;
	Text *player3Level2Texture;
	Text *player3Level3Texture;
	Text *player3TotalTexture;
	Text *player4NameTexture;
	Text *player4Level1Texture;
	Text *player4Level2Texture;
	Text *player4Level3Texture;
	Text *player4TotalTexture;
	std::vector<int> level1Score;
	std::vector<int> level2Score;
	std::vector<int> level3Score;
	std::vector<int> totalScore;
};

#endif /* CLIENT_VIEW_LEVELTRANSITIONVIEW_HH_ */
