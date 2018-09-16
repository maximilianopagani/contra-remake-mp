/*
 * Parallax.hpp
 *
 *  Created on: 9 sep. 2018
 *      Author: nacho
 */

#ifndef SRC_PARALLAX_HPP_
#define SRC_PARALLAX_HPP_

#include "GameView.hh"
#include "Sprite.hh"

enum LevelNumber {LEVEL1, LEVEL2, LEVEL3};

class Parallax {
	public:
		Parallax(GameView* _view, std::string bgPath1, std::string bgPath2, LevelNumber _level);
        virtual ~Parallax();
		void render();
		void updatePlayerPos(int _playerPosX, int _playerPosY);

	private:
        GameView* view = NULL;
        Sprite* bgSprite1 = NULL;
        Sprite* bgSprite2 = NULL;
        LevelNumber level;
		int screenWidth, screenHeight;
        int screenPosX, screenPosY;
		int bgScrollingOffsetX1, bgScrollingOffsetY1, bgScrollingOffsetX2, bgScrollingOffsetY2;
		int playerPosX, playerPosY;
};

#endif /* SRC_PARALLAX_HPP_ */
