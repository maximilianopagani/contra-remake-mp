/*
 * Text.cpp
 *
 *  Created on: 18 nov. 2018
 *      Author: nacho
 */

#include "Text.hh"

Text::Text(GameView* _gameView, std::string text, SDL_Color _textColor) {
	gameView = _gameView;
	texture = gameView->textTextureGenerator(text.c_str(), _textColor);
	gameView->queryTexture(texture, &width, &height);
}

Text::~Text() {
	this->destroy();
}

void Text::render(int x, int y) {
	gameView->draw(texture, NULL, x, y, width, height);
}

void Text::destroy() {
	SDL_DestroyTexture(texture);
	texture = NULL;
	gameView = NULL;
}
