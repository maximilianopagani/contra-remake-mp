/*
 * Game.h
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Level.h"
#include "Headers.h"

class Game
{
    public:

        Game(GameView* gameView);
        virtual ~Game();

        void init();
        void handleEvents();
        void update();
        void render();
        void destroy();

        void restartGame();
        void nextLevel();
        void endGame();

        bool state() { return enEjecucion; }

    private:

        bool enEjecucion;

        int currentLevel;

        GameView* gameView;
        Player* player;
        Level* level;
};

#endif /* SRC_GAME_H_ */
