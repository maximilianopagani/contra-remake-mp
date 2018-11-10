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
	std::vector<int> level1Score;
	std::vector<int> level2Score;
	std::vector<int> level3Score;
	std::vector<int> totalScore;
};

#endif /* CLIENT_VIEW_LEVELTRANSITIONVIEW_HH_ */
