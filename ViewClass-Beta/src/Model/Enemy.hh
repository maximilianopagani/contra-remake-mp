/*
 * Enemy.hh
 *
 *  Created on: 24 sep. 2018
 *      Author: nacho
 */

#ifndef ENEMY_HH_
#define ENEMY_HH_

#include "../Vista/GameView.hh"
#include "../Vista/Sprite.hh"
#include "../Utils/Logger.hh"

class Enemy {

	public:

		Enemy(GameView* view, string spritePath, int posX, int posY, int width, int height);
		virtual ~Enemy();

		//Gameloop
		void update();
		void render();
		void destroy();

		int getPosX() {return posX;}
		int getPosY() {return posY;}

	private:

		int posX, posY;
		static const int MAX_ANIMATIONS = 1;

		GameView* gameView;
		Sprite* animations[MAX_ANIMATIONS];
};

#endif /* ENEMY_HH_ */
