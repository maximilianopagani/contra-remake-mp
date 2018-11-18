/*
 * Text.hh
 *
 *  Created on: 18 nov. 2018
 *      Author: nacho
 */

#ifndef CLIENT_VIEW_TEXT_HH_
#define CLIENT_VIEW_TEXT_HH_

#include "GameView.hh"

class Text {

public:
	Text(GameView* _gameView, std::string text);
	virtual ~Text();

	void render(int x , int y);
	void destroy();

private:
	GameView* gameView;
	SDL_Texture* texture;
	int width;
	int height;
};

#endif /* CLIENT_VIEW_TEXT_HH_ */
