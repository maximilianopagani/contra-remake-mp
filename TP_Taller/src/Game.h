/*
 * Game.h
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */
#ifndef GAME_H
#define GAME_H

#include "Personaje.h"
#include "Bullet.h"
#include "Headers.h"

class Game
{
    public:

        Game();

        void init();
        void handleEvents();
        void update();
        void render();
        void clean();
        bool state() { return enEjecucion; }
        void catchFiredBullet(Bullet* firedBullet); // ver como puedo atrapar el disparo de una bala sin necesidad de que bala o personaje llamen a game

        virtual ~Game();

    private:

        bool enEjecucion;

        // A futuro a implementar esto en clase nivel o escenario
        SDL_Texture* level1Background = NULL;
        SDL_Rect level1Rect;

        // Manejo de balas
		std::list<Bullet*> gameBullets;
		std::list<Bullet*>::iterator gameBulletsIterator;
};

#endif /* SRC_GAME_H_ */
