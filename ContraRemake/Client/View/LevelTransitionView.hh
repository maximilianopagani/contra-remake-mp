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

class LevelTransitionView {

public:

	LevelTransitionView(GameView* _gameView);
	virtual ~LevelTransitionView();

	void render();
	void destroy();

private:

	GameView* gameView;
};

#endif /* CLIENT_VIEW_LEVELTRANSITIONVIEW_HH_ */
